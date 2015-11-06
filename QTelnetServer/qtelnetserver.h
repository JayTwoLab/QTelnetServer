#ifndef QTELNETSERVER_H
#define QTELNETSERVER_H

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QPointer>
#include <QSettings>
#include <QByteArray>
#include <QStringList>
#include <QCryptographicHash>
#include <QSettings>

class TelnetTCPServer;

class QTelnetServer : public QObject
{
    Q_OBJECT

public:

    // constructor
    explicit QTelnetServer(QObject* parent = 0);

    // destructor
    ~QTelnetServer();

    // start telnet server
    int Start(quint16 telnetport = 23);

    // stop telnet server
    int Stop();

    /**
    * Returns a QStringList of available commands
    */
    QStringList Commands() const;

    /**
    * Askes the plugin to execute a command and returns the results
    * @param command The command to execute
    * @param args A list of arguments for the command
    */
    QString Exec(QString command, QStringList args) const;

protected:

    // telnet tcp server
    TelnetTCPServer *Server;

};

#endif // QTELNETSERVER_H
