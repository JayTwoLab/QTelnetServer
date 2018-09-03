// QTelnetServer
// https://github.com/j2doll/QTelnetServer

#include <cstdio>
#include <iostream>

#include <QDebug>

#include "qtelnetserver.h"
#include "telnettcpserver.h"
#include "telnettcpclient.h"
#include "telnetlogic.h"

//----------------------------------------------------------------------------
//
TelnetTCPClient::TelnetTCPClient(
        int SocketDescriptor,
        TelnetTCPServer* parent )
    : QObject(parent)
{
    strCR = "\r\n";
    strShell = QString(">");

    CommandBuffer.clear();
    isAuthenticated = false;
    SessionID = SocketDescriptor;

    Socket = new QTcpSocket(this);
    if(!Socket->setSocketDescriptor(SessionID))
    {
        std::cerr << QTime::currentTime().toString().toStdString()
                  << " "
                  << SessionID << " Error binding socket\n";
        return;
    }

    telnetLogic = new TelnetLogic(this);

    //connect the signals
    connect( Socket, SIGNAL(readyRead()), this, SLOT(SocketReadyRead()), Qt::DirectConnection);
    connect( Socket, SIGNAL(disconnected()), this, SLOT(SocketDisconnected()), Qt::DirectConnection);

    std::cout << QTime::currentTime().toString().toStdString() << " "
              << SessionID << " Session Connected.\n";

    SendResponse(QString("[ Command Shell ]") + strCR);
    SendResponse(QString("Enter a password: "));

}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::SocketReadyRead()
{
    //Keep adding to the command buffer

    QByteArray Data = Socket->readAll();
    CommandBuffer.append(Data);

    if ( Data.size() >= 1 ) {

        if( Data.at(0) == 27 &&
            Data.at(1) == 91 )
        {
            if ( Data.at(2) == 65 )
            {
                // "UP ARROW RECIEVED";
                // QString strCache = slCacheString.back();
                // QString strTrim = strCache.trimmed().toLatin1();
                // qDebug() << strTrim;
                // Socket->write( strTrim.toLatin1() );
            }

            if ( Data.at(2) == 66 )
            {
                // "DOWN ARROW RECIEVED";

            }
        }

    }

    //Check to see if the CommandBuffer has a command
    if ( ! CommandBuffer.endsWith('\n') )
    {
        return;
    }

    // push back to cache strings
    if ( slCacheString.size() >= 100 ) {
        slCacheString.pop_front();
    }
    slCacheString.push_back( CommandBuffer.trimmed().toLatin1() );

    //Process the command

    if (!isAuthenticated)
    {
        //Authenticate the client
        if ( Authenticate(CommandBuffer) )
        {
            SendResponse(QString("success to login.") + strCR);
            SendResponse(strShell);
        }
        else
        {
            SendResponse("failed to login. enter password:");
        }

        CommandBuffer.clear();
        return;
    }

    DispatchCommand( CommandBuffer );
    CommandBuffer.clear();

    SendResponse( strShell );
}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::SocketDisconnected()
{
    std::cout << QTime::currentTime().toString().toStdString() << " "
              << SessionID << " session disconnected.\n";

    //Cleanup
    Socket->deleteLater();
    telnetLogic->deleteLater();
    this->deleteLater();
}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::SendResponse(const char* data)
{
    SendResponse(QString::fromLatin1(data));
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
    if ( Socket == NULL )
    {
        return;
    }

    if ( ! Socket->isValid() )
    {
        return;
    }

    if ( ! Socket->isOpen() )
    {
        return;
    }

    //Send the data to the client
    Socket->write(data);
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
    QString ClientPassword = CleanQString( Buffer.trimmed() );

    // convert password to hassed password
    QString strCmp = ClientPassword.toLatin1();


    if (strCmp.isEmpty())
    {
        return false;
    }

    QByteArray hash = QCryptographicHash::hash(strCmp.toLatin1(), QCryptographicHash::Sha1);
    QString hashedpass = QString(hash.toBase64());

    // read saved password
    QString strOrganizationName = ORG_NAME;
    QString strApplicationName = APP_NAME;
    QSettings settings( strOrganizationName, strApplicationName );
    QVariant varHashedPassword = settings.value( QString(PASSWORD_KEY) );
    // AUTH: PASSWORD: TODO: decrypt saved password
    QString strHashedPassword = varHashedPassword.toString();

    // saved password is not set
    if ( strHashedPassword.isEmpty() )
    {
        QString strOrganizationName = ORG_NAME;
        QString strApplicationName = APP_NAME;
        QSettings settings( strOrganizationName, strApplicationName );
        // AUTH: PASSWORD: TODO: encrypt hased password
        settings.setValue( QString(PASSWORD_KEY), QVariant(hashedpass) );

        isAuthenticated = true;
        return isAuthenticated;
    }

    if ( hashedpass != strHashedPassword ) // compare hased password
    {
        return false;
    }

    isAuthenticated = true;
    return isAuthenticated;
}

//----------------------------------------------------------------------------
//
QString TelnetTCPClient::CleanQString(QString toClean)
{
    QString ret;
    ret.clear();
    int count = toClean.size();
    for ( int ic = 0 ; ic < count ; ic ++ )
    {
        QChar ch = toClean.at( ic );
        if ( ch.isLetterOrNumber() )
        {
            ret = ret.append( ch );
        }
    }
    return ret;
}

//----------------------------------------------------------------------------
//
void TelnetTCPClient::DispatchCommand(QString command)
{
    QString cmd = command.trimmed();

    if (isExit(cmd))
    {
        SendResponse( "bye..." );
        Socket->close();
        return;
    }

    QString ret = telnetLogic->ProcessCommand( cmd );
    if ( ! ret.isEmpty() )
    {
        SendResponse( ret + strCR );
    }
}

//----------------------------------------------------------------------------
//
bool TelnetTCPClient::isExit(QString cmd)
{
    cmd = cmd.toLower(); // make lower

    if ( cmd == QString("exit") ||
        cmd == QString(".exit") ||
        cmd == QString("exit()") ||
        cmd == QString("exit;") ||
        cmd == QString("quit") ||
        cmd == QString(".quit") ||
        cmd == QString("quit()") ||
        cmd == QString("quit;") )
    {
        return true; // it is exit string
    }

    return false;
}

//----------------------------------------------------------------------------
//



