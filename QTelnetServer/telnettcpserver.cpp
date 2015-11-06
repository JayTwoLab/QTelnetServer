
#include <iostream>

#include "telnettcpclient.h"
#include "telnettcpserver.h"

//-----------------------------------------------------------------------------
//
TelnetTCPServer::TelnetTCPServer(QObject *parent) :
    QTcpServer(parent)
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

    std::cout << "listening...\n";

    //notify connected objects
    emit OnStarted();

    return 0;
}

//-----------------------------------------------------------------------------
//
void TelnetTCPServer::StopServer()
{
    this->close();

    std::cout << " server stopped\n";

    //notify connected objects
    emit OnStopped();

}

//-----------------------------------------------------------------------------
//
void TelnetTCPServer::incomingConnection(int socketDescriptor)
{
    std::cout << socketDescriptor << " Connecting..." << socketDescriptor << "\n";

    //Accept the incomming client

    TelnetTCPClient *cClient = new TelnetTCPClient( socketDescriptor, this );

    connect( this,SIGNAL(OnStopped()), cClient, SLOT(CloseSocket()) );

}

//-----------------------------------------------------------------------------
//

