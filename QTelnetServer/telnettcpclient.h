#ifndef TELNETTCPCLIENT_H
#define TELNETTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDir>
#include <QByteArray>
#include <QCryptographicHash>
#include <QProcess>
#include <QSettings>
#include <QFileInfo>

class TelnetLogic;

class TelnetTCPClient : public QObject
{
    Q_OBJECT

public:

    // constructor
    explicit TelnetTCPClient(int SocketDescriptor,QObject *parent = 0);

    /*!
    * Returns the socket ID
    */
    int ID();

signals:

public slots:

    /*!
    * Gets the request from the client
    */
    void SocketReadyRead();

    /*!
    * Slot for the TCP socket disconnected() signal
    */
    void SocketDisconnected();

    /*!
    * Sends the response to the client socket
    * @param data The QByteArray to send
    */
    void SendResponse(QByteArray data);

    /*!
    * Sends the response to the client socket
    * @param data The QString to send
    */
    void SendResponse(QString data);

    /*!
    * Sends the response to the client socket
    * @param data The char array to send
    */
    void SendResponse(const char* data);

    /*!
    * Closes the socket
    */
    void CloseSocket();

protected:

    int SessionID;          //! The Socket ID

    QTcpSocket *Socket;     //! The TCP Socket

    // QProcess *Process;      //! The Command line process

    QString CommandBuffer;  //! The buffer holding the command

    bool isAuthenticated;     //! Determines if the client is authenticated

    QString Banner;         //! The welcome banner and password prompt

    TelnetLogic *telnetLogic;

    QString strCR; // carriage return

    QString strShell; // shell character >

protected:

    /*!
    * Sends the response to the client socket
    * @param Buffer The data buffer
    */
    bool Authenticate(QString Buffer);

    //
    QString CleanQString(QString toClean);

    //
    void DispatchCommand(QString command);

    //
    bool isExit(QString cmd);

};

#endif // TELNETTCPCLIENT_H
