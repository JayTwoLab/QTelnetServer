/****************************************************************************
** Meta object code from reading C++ file 'telnettcpserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QTelnetServer/telnettcpserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'telnettcpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TelnetTCPServer_t {
    QByteArrayData data[4];
    char stringdata0[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TelnetTCPServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TelnetTCPServer_t qt_meta_stringdata_TelnetTCPServer = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TelnetTCPServer"
QT_MOC_LITERAL(1, 16, 9), // "OnStarted"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 9) // "OnStopped"

    },
    "TelnetTCPServer\0OnStarted\0\0OnStopped"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TelnetTCPServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TelnetTCPServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TelnetTCPServer *_t = static_cast<TelnetTCPServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnStarted(); break;
        case 1: _t->OnStopped(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TelnetTCPServer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TelnetTCPServer::OnStarted)) {
                *result = 0;
            }
        }
        {
            typedef void (TelnetTCPServer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TelnetTCPServer::OnStopped)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TelnetTCPServer::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_TelnetTCPServer.data,
      qt_meta_data_TelnetTCPServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TelnetTCPServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TelnetTCPServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TelnetTCPServer.stringdata0))
        return static_cast<void*>(const_cast< TelnetTCPServer*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int TelnetTCPServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TelnetTCPServer::OnStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TelnetTCPServer::OnStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
