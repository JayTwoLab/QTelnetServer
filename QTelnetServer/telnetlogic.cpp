// QTelnetServer
// https://github.com/j2doll/QTelnetServer

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

#include <QtGlobal>
#include <QString>
#include <QChar>
#include <QStringList>
#include <QLatin1Char>
#include <QVector>
#include <QDebug>

#include "qtelnetserver.h"
#include "telnetlogic.h"

//----------------------------------------------------------------------------
//
QString trimBackSpace(QString strIn)
{
    QChar chBackSpace = QChar(QLatin1Char('\010')); // backspace

    int indexBackSpace = strIn.indexOf( chBackSpace );
    if ( indexBackSpace == (-1) )
    {
        return strIn; // backspace is not found
    }

    // remove backspace and pre-backspace character
    strIn.remove( indexBackSpace, 1 );
    if ( (indexBackSpace - 1) >= 0 )
    {
         strIn.remove( (indexBackSpace - 1), 1 );
    }

    return trimBackSpace(strIn);
}

//----------------------------------------------------------------------------
//
TelnetLogic::TelnetLogic(QObject *parent)
    : QObject(parent)
{

}

//----------------------------------------------------------------------------
//
QString TelnetLogic::ProcessCommand(QString command)
{
    if ( command.isEmpty() )
    {
        return command;
    }

    QString ret;
    // ret = command; // echo string

    QString lowCMD = command.trimmed().toLower(); // lower case command string
    QString strRemoveBackSpace = trimBackSpace(lowCMD); // remove backspace and -re-backspace charater

    // qDebug() << QTime::currentTime().toString() << " " << strRemoveBackSpace;

    // parse command
    std::istringstream iss( strRemoveBackSpace.toStdString() );
    std::vector<std::string> parseResults((std::istream_iterator<std::string>(iss)),
                                     std::istream_iterator<std::string>());
    QStringList slArg;
    foreach (std::string ssArg, parseResults) {
        QString strArg = QString::fromStdString( ssArg );
        slArg.push_back( strArg );
    }

    // command 'setpassword'
    ret = ProcessSetPassword(slArg, ret);

    // TODO: command 'YourOwnCommand'
    //  QString ProcessYourOwnCommand(QStringList slArgs, QString inRet);

    return ret;
}


//----------------------------------------------------------------------------
//
QString TelnetLogic::ProcessSetPassword(QStringList slArgs, QString inRet)
{
    // command 'setpassword' [password]

    if ( slArgs.at(0) != QString("setpassword") )
    {
        return inRet;
    }

    if ( slArgs.size() <= 1 )
    {
        return inRet;
    }

    QByteArray hash = QCryptographicHash::hash( slArgs.at(1).toLatin1(), QCryptographicHash::Sha1);
    QString hashedpass = QString( hash.toBase64() );

    QString strOrganizationName = ORG_NAME;
    QString strApplicationName = APP_NAME;
    QSettings settings( strOrganizationName, strApplicationName );
    // AUTH: PASSWORD: TODO: encrypt saved password
    settings.setValue( QString(PASSWORD_KEY), QVariant(hashedpass) );

    return QString( "RESPONSE: success to change password" );
}

//----------------------------------------------------------------------------
//
/*
QString TelnetLogic::ProcessYourOwnCommand(QStringList slArgs, QString inRet)
{
    if ( slArgs.at(0) != QString("YourOwnCommand") )
    {
        return inRet;
    }
    return QString("RESPONSE: done");
}
// */
