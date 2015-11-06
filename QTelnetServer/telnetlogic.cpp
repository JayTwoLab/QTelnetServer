
#include <iostream>

#include "telnetlogic.h"

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
    QString cmd = command.trimmed().toLower(); // command string
    QString ret; // return string

    // ret = command; // string echo

    // TODO: process each command ...

    return ret;
}

//----------------------------------------------------------------------------
//


