// QTelnetServer
// https://github.com/j2doll/QTelnetServer

#ifndef TELNETLOGIC_H
#define TELNETLOGIC_H

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QMap>
#include <QVector>
#include <QList>
#include <QStringList>
#include <QCryptographicHash>

class TelnetLogic : public QObject
{
    Q_OBJECT
public:

    // constructor
    explicit TelnetLogic(QObject *parent = 0);
\
    // process telnet command
    QString ProcessCommand(QString command);

protected:

    // command 'setpassword' [password]
    QString  ProcessSetPassword(QStringList slArgs, QString inRet);

    // TODO: append your own command

};

#endif // TELNETLOGIC_H
