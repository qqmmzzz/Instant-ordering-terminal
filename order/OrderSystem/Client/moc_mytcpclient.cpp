/****************************************************************************
** Meta object code from reading C++ file 'mytcpclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mytcpclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mytcpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyTcpClient_t {
    QByteArrayData data[15];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyTcpClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyTcpClient_t qt_meta_stringdata_MyTcpClient = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MyTcpClient"
QT_MOC_LITERAL(1, 12, 9), // "connected"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "connectFailed"
QT_MOC_LITERAL(4, 37, 5), // "error"
QT_MOC_LITERAL(5, 43, 12), // "disconnected"
QT_MOC_LITERAL(6, 56, 12), // "menuReceived"
QT_MOC_LITERAL(7, 69, 8), // "menuData"
QT_MOC_LITERAL(8, 78, 11), // "orderResult"
QT_MOC_LITERAL(9, 90, 7), // "success"
QT_MOC_LITERAL(10, 98, 7), // "orderId"
QT_MOC_LITERAL(11, 106, 3), // "msg"
QT_MOC_LITERAL(12, 110, 11), // "onConnected"
QT_MOC_LITERAL(13, 122, 11), // "onReadyRead"
QT_MOC_LITERAL(14, 134, 14) // "onDisconnected"

    },
    "MyTcpClient\0connected\0\0connectFailed\0"
    "error\0disconnected\0menuReceived\0"
    "menuData\0orderResult\0success\0orderId\0"
    "msg\0onConnected\0onReadyRead\0onDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyTcpClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    1,   55,    2, 0x06 /* Public */,
       5,    0,   58,    2, 0x06 /* Public */,
       6,    1,   59,    2, 0x06 /* Public */,
       8,    3,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   69,    2, 0x08 /* Private */,
      13,    0,   70,    2, 0x08 /* Private */,
      14,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonArray,    7,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::QString,    9,   10,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyTcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyTcpClient *_t = static_cast<MyTcpClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->connectFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->disconnected(); break;
        case 3: _t->menuReceived((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 4: _t->orderResult((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 5: _t->onConnected(); break;
        case 6: _t->onReadyRead(); break;
        case 7: _t->onDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyTcpClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::connected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MyTcpClient::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::connectFailed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MyTcpClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::disconnected)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MyTcpClient::*_t)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::menuReceived)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MyTcpClient::*_t)(bool , int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::orderResult)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject MyTcpClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MyTcpClient.data,
      qt_meta_data_MyTcpClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyTcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyTcpClient.stringdata0))
        return static_cast<void*>(const_cast< MyTcpClient*>(this));
    return QObject::qt_metacast(_clname);
}

int MyTcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MyTcpClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MyTcpClient::connectFailed(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyTcpClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void MyTcpClient::menuReceived(const QJsonArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyTcpClient::orderResult(bool _t1, int _t2, const QString & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
