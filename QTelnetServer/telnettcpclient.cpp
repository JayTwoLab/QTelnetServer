
#include "telnettcpclient.h"

//----------------------------------------------------------------------------
//
TelnetTCPClient::TelnetTCPClient(int SocketDescriptor, QObject *parent) :
    QObject(parent)
{

    Authenticated = false;
    SessionID = SocketDescriptor;

    Socket = new QTcpSocket(this);
    if(!Socket->setSocketDescriptor(SessionID))
    {
        qDebug() << SessionID << " Error binding socket";
        return;
    }

    //connect the signals
    connect(Socket,SIGNAL(readyRead()),this,SLOT(SocketReadyRead()),Qt::DirectConnection);
    connect(Socket,SIGNAL(disconnected()),this,SLOT(SocketDisconnected()),Qt::DirectConnection);

    qDebug() << SessionID << " session Connected";

    //Create a new process for them
    Process = new  QProcess(this);
    Process->setReadChannelMode(QProcess::MergedChannels);
    connect(Process,SIGNAL(readyReadStandardOutput()), this,SLOT(ProcessReadyRead()));
    connect(Process,SIGNAL(readyReadStandardError()), this,SLOT(ProcessReadyRead()));
    connect(Process,SIGNAL(readyRead()), this,SLOT(ProcessReadyRead()));

    Banner = "Enter a password: ";
    SendResponse(Banner.toLatin1());
}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::SocketReadyRead()
{

    //Keep adding to the command buffer
    QByteArray Data = Socket->readAll();

    CommandBuffer.append(Data);

    //Check to see if the CommandBuffer has a command
    if(CommandBuffer.endsWith('\n'))
    {
        //Process the command

        if(!Authenticated)
        {
            //Authenticate the client
            Authenticate(CommandBuffer);

        }
        else
        {

            //See if they are changing directories
            if(CommandBuffer.toUpper().startsWith("CD "))
            {
                QString NewDir = CommandBuffer.mid(3).trimmed();

                QDir dir(NewDir);
                if(dir.exists())
                {
                    Process->setWorkingDirectory(NewDir);
                    Process->close();
                    StartProcess();
                }
            }

            //See if they are uploading
            if(CommandBuffer.toUpper().startsWith("UPLOAD "))
            {
                Upload(CommandBuffer);
                CommandBuffer.clear();
                return;
            }

            //See if they are downloading
            if(CommandBuffer.toUpper().startsWith("DOWNLOAD "))
            {
                Download(CommandBuffer);
                CommandBuffer.clear();
                return;
            }

            Process->write(CommandBuffer.toLatin1());
            Process->waitForBytesWritten();

            qDebug() << SessionID << " Buffer: " << CommandBuffer.trimmed();

        }

        CommandBuffer.clear();
    }
}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::SocketDisconnected()
{
    qDebug() << SessionID << " session disconnected";

    Process->close();
    Process->deleteLater();

    //Cleanup
    Socket->deleteLater();
    this->deleteLater();
}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::SendResponse(const char* data)
{
    SendResponse(QString:: fromLatin1(data));
}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::SendResponse(QString data)
{
    SendResponse(data.toLatin1());
}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::SendResponse(QByteArray data)
{
    //Send the data to the client
    Socket->write(data);
}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::ProcessReadyRead()
{
    //Read from the process and write to the socket
    SendResponse(Process->readAll());
}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::StartProcess()
{
#ifdef Q_WS_WIN
    Process->start("cmd");
#endif

#ifdef Q_WS_X11
    Process->start("bash");
#endif

#ifdef Q_WS_MAC
    Process->start("bash");
#endif
}

//----------------------------------------------------------------------------
//
int TelnetTCPClient::ID()
{
   return SessionID;
}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::CloseSocket()
{
    Socket->close();
}

//----------------------------------------------------------------------------
//
bool TelnetTCPClient::Authenticate(QString Buffer)
{
    //check the password
    QString ClientPassword = Buffer.trimmed();

    QSettings Settings;
    Settings.beginGroup("Telnet Plugin");
    QVariant vServerPassword = Settings.value("password","");
    Settings.endGroup();

    QString ServerPassword = vServerPassword.toString();

    //Check to see if they configured a password
    if(ServerPassword == "")
    {
        //Some password is better then none
        ServerPassword = "password";
        QByteArray serverhash = QCryptographicHash::hash(ServerPassword.toLatin1(),QCryptographicHash::Sha1);
        ServerPassword = QString(serverhash.toBase64());
    }

    //see if the passwords match
    QByteArray hash = QCryptographicHash::hash(ClientPassword.toLatin1(),QCryptographicHash::Sha1);
    QString hashedpass = QString(hash.toBase64());

    if(hashedpass == ServerPassword)
    {
        Authenticated = true;
        StartProcess();
    }
    else
    {
        SendResponse(Banner.toLatin1());
    }

    return Authenticated;
}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::Upload(QString Command)
{
    //CLIENT = UPLOAD FILENAME SIZE
    //SERVER = UPLOAD FILENAME SIZE
    //CLIENT = DATA
    //SERVER = UPLOAD COMPLETE

    QStringList args = Command.split(" ");

}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::Download(QString Command)
{


    //CLIENT = DOWNLOAD FILENAME
    //SERVER = DOWNLOAD FILENAME SIZE \r\n DATA
    //SERVER = DATA
    //SERVER = DOWNLOAD COMLETE

    QStringList args = Command.split(" ");

    //Make sure they have enough arquments
    if(args.count() <2)
    {
        SendResponse("ERROR: usage is - DOWNLOAD FILENAME\r\n");
        return;
    }

    //Make sure the file exists
    QFileInfo fi(GetFilename(args.at(1).trimmed()));
    QFile file(fi.absoluteFilePath());


    if(!file.exists())
    {
        qDebug() << file.fileName();
        SendResponse("ERROR: File not found - " + file.fileName() + "\r\n");
        return;
    }

    //Tell the client what to expect
    QString FileSize = QString::number(fi.size());
    SendResponse("DOWNLOAD " + file.fileName() + " " + FileSize + "\r\n");

    //Send the file to the client
    if(file.open(QFile::ReadOnly))
    {
        //Send the contents
        while(!file.atEnd())
        {
            //read the file
            QByteArray data = file.read(1024 * 5);
            SendResponse(data);
            Socket->waitForBytesWritten();
        }
        file.close();

        //Tell the client we are done
        SendResponse("DOWNLOAD COMPLETE\r\n");
    }
    else
    {
        SendResponse("ERROR: Could not open file - " + file.fileName() + "\r\n");
        return;
    }

}

//----------------------------------------------------------------------------
//
QString TelnetTCPClient::GetFilename(QString Filename)
{
    QString ret = Filename;

    if(Filename.contains("\\") || Filename.contains("/"))
    {
        ret = Filename;
    }
    else
    {
        QFileInfo file(Process->workingDirectory(),Filename);
        ret = file.absoluteFilePath();
    }

    return ret;
}

//----------------------------------------------------------------------------
//

