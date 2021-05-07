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

```cpp
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

:four: ProcessYourOwnCommand()를 설정한다 (telnetlogic.cpp)

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

## 테스트 환경

- Qt 5.12 (Do not use old Qt!)
- Qt 6

## 라이센스

- QTelnetServer는 MIT 라이센스입니다. 

## 링크
- https://github.com/JayTwoLab/QTelnetServer

