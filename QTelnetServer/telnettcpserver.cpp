// QTelnetServer
// https://github.com/j2doll/QTelnetServer

#include <iostream>

#include "qtelnetserver.h"
#include "telnettcpclient.h"
#include "telnettcpserver.h"

//-----------------------------------------------------------------------------
//
TelnetTCPServer::TelnetTCPServer(QObject *parent)
    : QTcpServer(parent)
{

}

//-----------------------------------------------------------------------------
//
TelnetTCPServer::~TelnetTCPServer()
{

}

//-----------------------------------------------------------------------------
//
int TelnetTCPServer::StartServer(qint16 port)
{

    if( ! this->listen( QHostAddress::Any, port ) )
    {
        std::cerr << " could not start server\n";
        return (-1);
    }

    std::cout << QTime::currentTime().toString().toStdString() << " "
              << "listening...\n";

    //notify connected objects
    emit OnStarted();

    return 0;
}

//-----------------------------------------------------------------------------
//
void TelnetTCPServer::StopServer()
{
    this->close();

    std::cout << QTime::currentTime().toString().toStdString() << " "
              << " server stopped\n";

    //notify connected objects
    emit OnStopped();

}

//-----------------------------------------------------------------------------
//
bool TelnetTCPServer::setPasswordHash(QString hashedpass)
{
    QString strOrganizationName = ORG_NAME;
    QString strApplicationName = APP_NAME;
    QSettings settings( strOrganizationName, strApplicationName );
    // AUTH: PASSWORD: TODO: encrypt saved password
    settings.setValue( QString(PASSWORD_KEY), QVariant(hashedpass) );

    return true;
}

//-----------------------------------------------------------------------------
//
void TelnetTCPServer::incomingConnection(int socketDescriptor)
{
    std::cout << QTime::currentTime().toString().toStdString() << " "
             << socketDescriptor << " Connecting..." << socketDescriptor << "\n";

    //Accept the incomming client

    TelnetTCPClient *cClient = new TelnetTCPClient( socketDescriptor, this );

    connect( this,SIGNAL(OnStopped()), cClient, SLOT(CloseSocket()) );

}

//-----------------------------------------------------------------------------
//

