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
    * Slot for the QProcess ReadreadyReadStandardOutput()
    */
    void ProcessReadyRead();

    /*!
    * Closes the socket
    */
    void CloseSocket();

protected:

    int SessionID;          //! The Socket ID

    QTcpSocket *Socket;     //! The TCP Socket

    QProcess *Process;      //! The Command line process

    QString CommandBuffer;  //! The buffer holding the command

    bool Authenticated;     //! Determines if the client is authenticated

    QString Banner;         //! The welcome banner and password prompt

    /*!
    * Starts the process
    */
    void StartProcess();

    /*!
    * Sends the response to the client socket
    * @param Buffer The data buffer
    */
    bool Authenticate(QString Buffer);

    /*!
    * Processes the upload
    * @param Command The data buffer
    */
    void Upload(QString Command);

    /*!
    * Processes the download
    * @param Command The data buffer
    */
    void Download(QString Command);

    /*!
    * Returns the name of the file to transfer
    * @param Filename the file the client is requesting
    */
    QString GetFilename(QString Filename);

};

#endif // TELNETTCPCLIENT_H
