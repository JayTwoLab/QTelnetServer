/****************************************************************************
** Meta object code from reading C++ file 'telnettcpclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QTelnetServer/telnettcpclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'telnettcpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TelnetTCPClient_t {
    QByteArrayData data[8];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TelnetTCPClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TelnetTCPClient_t qt_meta_stringdata_TelnetTCPClient = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TelnetTCPClient"
QT_MOC_LITERAL(1, 16, 15), // "SocketReadyRead"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 18), // "SocketDisconnected"
QT_MOC_LITERAL(4, 52, 12), // "SendResponse"
QT_MOC_LITERAL(5, 65, 4), // "data"
QT_MOC_LITERAL(6, 70, 11), // "const char*"
QT_MOC_LITERAL(7, 82, 11) // "CloseSocket"

    },
    "TelnetTCPClient\0SocketReadyRead\0\0"
    "SocketDisconnected\0SendResponse\0data\0"
    "const char*\0CloseSocket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TelnetTCPClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    1,   46,    2, 0x0a /* Public */,
       4,    1,   49,    2, 0x0a /* Public */,
       4,    1,   52,    2, 0x0a /* Public */,
       7,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 6,    5,
    QMetaType::Void,

       0        // eod
};

void TelnetTCPClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TelnetTCPClient *_t = static_cast<TelnetTCPClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SocketReadyRead(); break;
        case 1: _t->SocketDisconnected(); break;
        case 2: _t->SendResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->SendResponse((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->SendResponse((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 5: _t->CloseSocket(); break;
        default: ;
        }
    }
}

const QMetaObject TelnetTCPClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TelnetTCPClient.data,
      qt_meta_data_TelnetTCPClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TelnetTCPClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TelnetTCPClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TelnetTCPClient.stringdata0))
        return static_cast<void*>(const_cast< TelnetTCPClient*>(this));
    return QObject::qt_metacast(_clname);
}

int TelnetTCPClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
