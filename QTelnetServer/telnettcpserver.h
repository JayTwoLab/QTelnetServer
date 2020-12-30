// telnettcpserver.h

#ifndef TELNETTCPSERVER_H
#define TELNETTCPSERVER_H

#include <QtGlobal>
#include <QObject>
#include <QTcpServer>

class TelnetTCPServer : public QTcpServer
{
    Q_OBJECT

public:

    /*!
    * Constructor
    * @param parent The parent object
    */
    explicit TelnetTCPServer(QObject *parent = NULL);

    virtual ~TelnetTCPServer();

    /*!
    * Starts the TCP Server
    * @param port The port to start the server on
    */
    int StartServer(qint16 port);

    /*!
    * Stops the TCP Server
    */
    void StopServer();

    bool setPasswordHash(QString hashedpass);

signals:

    /*!
    * Signal indicates the TCP Server has stopped
    */
    void OnStarted();

    /*!
    * Signal indicates the TCP Server has stopped
    */
    void OnStopped();

public slots:

protected:

    /**
    * Processes incomming TCP connections
    * @param socketDescriptor The descriptor of the conection
    */
    virtual void incomingConnection(qintptr socketDescriptor);

    // virtual void incomingConnection(int socketDescriptor); // old Qt

};

#endif // TELNETTCPSERVER_H
