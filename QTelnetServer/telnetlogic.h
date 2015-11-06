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

class TelnetLogic : public QObject
{
    Q_OBJECT

public:

    explicit TelnetLogic(QObject *parent = 0);

    QString ProcessCommand(QString command);

protected:

    QString strCR;


};

#endif // TELNETLOGIC_H
