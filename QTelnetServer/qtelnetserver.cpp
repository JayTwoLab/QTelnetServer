
#include "qtelnetserver.h"
#include "telnettcpserver.h"

//-----------------------------------------------------------------------------
//
QTelnetServer::QTelnetServer(QObject* parent)
 : QObject(parent)
{
   Server = new TelnetTCPServer();
}

//-----------------------------------------------------------------------------
//
QTelnetServer::~QTelnetServer()
{
    delete Server;
}

//-----------------------------------------------------------------------------
//
int QTelnetServer::Start(quint16 telnetport)
{
    int ret = Server->StartServer( telnetport );

    return ret;
}

//-----------------------------------------------------------------------------
//
int QTelnetServer::Stop()
{
    Server->StopServer();

    return 0;
}

//-----------------------------------------------------------------------------
//
QStringList QTelnetServer::Commands() const
{
    QStringList List;
    List.append("setpassword (password) - Sets the password for the telnet server.");
    List.append("setport (port) - Sets the port to run the telnet server on.");

    return List;
}

//-----------------------------------------------------------------------------
//
QString QTelnetServer::Exec(QString command, QStringList args) const
{
    if(!args.count() > 1)
    {
        return "Please include the arquments to the command!";
    }

    QString ret = "Not a valid command.";
    // Settings->beginGroup(Name());

    //Set the password
    if(command == "setpassword")
    {
        //Hash the password and then base64 encode it
        QByteArray hash = QCryptographicHash::hash(args.at(0).toLatin1(), QCryptographicHash::Sha1);

        QString hashedpass = QString(hash.toBase64());

        ret = "Password has been set.";
    }

    return ret;
}

//-----------------------------------------------------------------------------
//
