
#include <cstdio>
#include <iostream>

#include "telnettcpclient.h"
#include "telnetlogic.h"

//----------------------------------------------------------------------------
//
TelnetTCPClient::TelnetTCPClient(int SocketDescriptor, QObject *parent)
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
        std::cerr << SessionID << " Error binding socket\n";
        return;
    }

    telnetLogic = new TelnetLogic(this);

    //connect the signals
    connect( Socket, SIGNAL(readyRead()), this, SLOT(SocketReadyRead()), Qt::DirectConnection);
    connect( Socket, SIGNAL(disconnected()), this, SLOT(SocketDisconnected()), Qt::DirectConnection);

    std::cout << SessionID << " Session Connected.\n";

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

    //Check to see if the CommandBuffer has a command
    if( ! CommandBuffer.endsWith('\n') )
    {
        return;
    }

    //Process the command

    if(!isAuthenticated)
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
    std::cout << SessionID << " session disconnected.\n";

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

    QString passwd = "password"; // digit or number
    QString strCmp = ClientPassword.toLatin1();
    if ( strCmp != passwd )
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
    QString strExit = QString("exit");
    if ( cmd == strExit )
    {
        return true;
    }

    QString strQuit = QString("quit");
    if ( cmd == strQuit )
    {
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------
//



