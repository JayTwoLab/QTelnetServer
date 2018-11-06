# QTelnetServer

> *Read this in other languages: [English](README.md), :kr: [한국어](README.ko.md)*

- Qt 텔넷 서버

## 사용하는 방법

:one: 텔넷 서버 생성

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
:two: 자신만의 텔넷 명령 함수를 정의합니다. 헤더 파일(TelnetServer.h)

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
:three:자신만의 텔넷 명령 함수를 정의합니다. 소스 파일(TelnetServer.cpp) 

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

## 테스트 환경

- Qt 5

## 라이센스

- QTelnetServer는 MIT 라이센스입니다. [https://github.com/j2doll/QTelnetServer](https://github.com/j2doll/QTelnetServer)
