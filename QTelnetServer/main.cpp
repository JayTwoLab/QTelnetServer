// mmain.cpp
//

#include <QCoreApplication>
#include <QDebug>
#include <QFile>

#include "qtelnetserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTelnetServer ts;
    qDebug() << ts.Start();

    return a.exec();
}
