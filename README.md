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

## Tested Environment

- Qt 5

## License and links

- QTelnetServer is under MIT license. [https://github.com/j2doll/QTelnetServer](https://github.com/j2doll/QTelnetServer)
