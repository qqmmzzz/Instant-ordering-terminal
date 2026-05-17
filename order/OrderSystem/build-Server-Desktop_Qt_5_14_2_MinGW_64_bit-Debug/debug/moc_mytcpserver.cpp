/****************************************************************************
** Meta object code from reading C++ file 'mytcpserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Server/mytcpserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mytcpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyTcpServer_t {
    QByteArrayData data[19];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyTcpServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyTcpServer_t qt_meta_stringdata_MyTcpServer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MyTcpServer"
QT_MOC_LITERAL(1, 12, 13), // "menuRequested"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "orderReceived"
QT_MOC_LITERAL(4, 41, 8), // "orderObj"
QT_MOC_LITERAL(5, 50, 15), // "clientConnected"
QT_MOC_LITERAL(6, 66, 10), // "clientInfo"
QT_MOC_LITERAL(7, 77, 18), // "clientDisconnected"
QT_MOC_LITERAL(8, 96, 11), // "setMenuData"
QT_MOC_LITERAL(9, 108, 8), // "menuData"
QT_MOC_LITERAL(10, 117, 15), // "sendOrderResult"
QT_MOC_LITERAL(11, 133, 11), // "QTcpSocket*"
QT_MOC_LITERAL(12, 145, 6), // "socket"
QT_MOC_LITERAL(13, 152, 7), // "success"
QT_MOC_LITERAL(14, 160, 7), // "orderId"
QT_MOC_LITERAL(15, 168, 3), // "msg"
QT_MOC_LITERAL(16, 172, 15), // "onNewConnection"
QT_MOC_LITERAL(17, 188, 11), // "onReadyRead"
QT_MOC_LITERAL(18, 200, 20) // "onClientDisconnected"

    },
    "MyTcpServer\0menuRequested\0\0orderReceived\0"
    "orderObj\0clientConnected\0clientInfo\0"
    "clientDisconnected\0setMenuData\0menuData\0"
    "sendOrderResult\0QTcpSocket*\0socket\0"
    "success\0orderId\0msg\0onNewConnection\0"
    "onReadyRead\0onClientDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyTcpServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    1,   60,    2, 0x06 /* Public */,
       5,    1,   63,    2, 0x06 /* Public */,
       7,    1,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   69,    2, 0x0a /* Public */,
      10,    4,   72,    2, 0x0a /* Public */,
      16,    0,   81,    2, 0x08 /* Private */,
      17,    0,   82,    2, 0x08 /* Private */,
      18,    0,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QJsonArray,    9,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Bool, QMetaType::Int, QMetaType::QString,   12,   13,   14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyTcpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyTcpServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->menuRequested(); break;
        case 1: _t->orderReceived((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 2: _t->clientConnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->clientDisconnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setMenuData((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 5: _t->sendOrderResult((*reinterpret_cast< QTcpSocket*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 6: _t->onNewConnection(); break;
        case 7: _t->onReadyRead(); break;
        case 8: _t->onClientDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyTcpServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyTcpServer::menuRequested)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyTcpServer::*)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyTcpServer::orderReceived)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyTcpServer::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyTcpServer::clientConnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyTcpServer::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyTcpServer::clientDisconnected)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyTcpServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MyTcpServer.data,
    qt_meta_data_MyTcpServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyTcpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTcpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyTcpServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyTcpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MyTcpServer::menuRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MyTcpServer::orderReceived(const QJsonObject & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyTcpServer::clientConnected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyTcpServer::clientDisconnected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
