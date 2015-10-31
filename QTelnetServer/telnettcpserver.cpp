
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
        qDebug() << "Could not start server";
        return (-1);
    }

    qDebug() << "Listening...";

    //notify connected objects
    emit OnStarted();

    return 0;
}

//-----------------------------------------------------------------------------
//
void TelnetTCPServer::StopServer()
{
    this->close();

    qDebug() << "Server stopped";

    //notify connected objects
    emit OnStopped();

}

//-----------------------------------------------------------------------------
//
void TelnetTCPServer::incomingConnection(int socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting..." << socketDescriptor;

    //Accept the incomming client

    TelnetTCPClient *cClient = new TelnetTCPClient( socketDescriptor, this );

    connect( this,SIGNAL(OnStopped()), cClient, SLOT(CloseSocket()) );

}

//-----------------------------------------------------------------------------
//

