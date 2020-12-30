# QTelnetServer

> *Read this in other languages: [English](README.md), :kr: [한국어](README.ko.md)*

- It's a telnet server fot Qt.

## How to use

:one: Create telnet server


```cpp
// main.cpp
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTelnetServer ts; // telnet server
    quint16 telnetport = 10023; // telnet port
    qDebug() << ts.Start(telnetport); // start server

    return a.exec(); // use main thread event dispatcher. you may use multi-thread.
}
```

:two: Define your own telnet command fucntion on header file (TelnetServer.h)

```h
class TelnetLogic : public QObject
{
    Q_OBJECT
public:
    explicit TelnetLogic(QObject *parent = 0);
public:
    QString ProcessCommand(QString command);
protected:
    QString  ProcessSetPassword(QStringList slArgs, QString inRet);

    // TODO: define your own command fucntion 
    QString  ProcessYourOwnCommand(QStringList slArgs, QString inRet);
};
```

:three: Define your own telnet command fucntion on source file (TelnetServer.cpp) 

```cpp
QString TelnetLogic::ProcessYourOwnCommand(QStringList slArgs, QString inRet)
{
    if ( slArgs.at(0) != QString("YourOwnCommand") )
    {
        return inRet;
    }

    // If you want an function example, 
    // see QString TelnetLogic::ProcessSetPassword(QStringList slArgs, QString inRet)

    return QString("RESPONSE: done");
}
```

:four: Set ProcessYourOwnCommand() (telnetlogic.cpp)

```cpp
QString TelnetLogic::ProcessCommand(QString command)
{
    if ( command.isEmpty() )
    {
        return command;
    }

    QString ret;
    // ret = command; // echo string

    // QString lowCMD = command.trimmed().toLower(); // lower case command string
    QString strRemoveBackSpace = trimBackSpace( command.trimmed() ); // remove backspace and pre-backspace character

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

    // TODO: define command 'YourOwnCommand'
    ret = ProcessYourOwnCommand(slArg, ret);

    return ret; // return string is telnet response tring
}
```

## Tested Environment

- Qt 5.12 (Do not use old Qt!)
- Qt 6

## License

- QTelnetServer is under MIT license.

## Links
- https://github.com/JayTwoLab/QTelnetServer
