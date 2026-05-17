/****************************************************************************
** Meta object code from reading C++ file 'serverwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Server/serverwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serverwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ServerWidget_t {
    QByteArrayData data[19];
    char stringdata0[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerWidget_t qt_meta_stringdata_ServerWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ServerWidget"
QT_MOC_LITERAL(1, 13, 16), // "onBtnStartServer"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 16), // "onBtnRefreshMenu"
QT_MOC_LITERAL(4, 48, 18), // "onBtnRefreshOrders"
QT_MOC_LITERAL(5, 67, 12), // "onBtnAddDish"
QT_MOC_LITERAL(6, 80, 15), // "onBtnDeleteDish"
QT_MOC_LITERAL(7, 96, 13), // "onBtnEditDish"
QT_MOC_LITERAL(8, 110, 11), // "onBtnSearch"
QT_MOC_LITERAL(9, 122, 16), // "onBtnSelectTheme"
QT_MOC_LITERAL(10, 139, 18), // "onBtnSetBackground"
QT_MOC_LITERAL(11, 158, 20), // "onBtnClearBackground"
QT_MOC_LITERAL(12, 179, 9), // "onTimeout"
QT_MOC_LITERAL(13, 189, 15), // "onMenuRequested"
QT_MOC_LITERAL(14, 205, 15), // "onOrderReceived"
QT_MOC_LITERAL(15, 221, 8), // "orderObj"
QT_MOC_LITERAL(16, 230, 17), // "onClientConnected"
QT_MOC_LITERAL(17, 248, 4), // "info"
QT_MOC_LITERAL(18, 253, 20) // "onClientDisconnected"

    },
    "ServerWidget\0onBtnStartServer\0\0"
    "onBtnRefreshMenu\0onBtnRefreshOrders\0"
    "onBtnAddDish\0onBtnDeleteDish\0onBtnEditDish\0"
    "onBtnSearch\0onBtnSelectTheme\0"
    "onBtnSetBackground\0onBtnClearBackground\0"
    "onTimeout\0onMenuRequested\0onOrderReceived\0"
    "orderObj\0onClientConnected\0info\0"
    "onClientDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    1,  101,    2, 0x08 /* Private */,
      16,    1,  104,    2, 0x08 /* Private */,
      18,    1,  107,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,   17,

       0        // eod
};

void ServerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ServerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onBtnStartServer(); break;
        case 1: _t->onBtnRefreshMenu(); break;
        case 2: _t->onBtnRefreshOrders(); break;
        case 3: _t->onBtnAddDish(); break;
        case 4: _t->onBtnDeleteDish(); break;
        case 5: _t->onBtnEditDish(); break;
        case 6: _t->onBtnSearch(); break;
        case 7: _t->onBtnSelectTheme(); break;
        case 8: _t->onBtnSetBackground(); break;
        case 9: _t->onBtnClearBackground(); break;
        case 10: _t->onTimeout(); break;
        case 11: _t->onMenuRequested(); break;
        case 12: _t->onOrderReceived((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 13: _t->onClientConnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->onClientDisconnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ServerWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ServerWidget.data,
    qt_meta_data_ServerWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ServerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ServerWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ServerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
