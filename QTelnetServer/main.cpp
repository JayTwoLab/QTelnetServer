// QTelnetServer, MIT License
// https://github.com/j2doll/QTelnetServer

// main.cpp
//

#include <QCoreApplication>
#include <QDebug>
#include <QFile>

#include "qtelnetserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTelnetServer ts;
    quint16 telnetport = 10023; // telnet port
    qDebug() << ts.Start(telnetport);

    int ret = a.exec(); // use main thread event dispatcher

    return ret;
}
