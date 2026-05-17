/****************************************************************************
** Meta object code from reading C++ file 'clientwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Client/clientwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientWidget_t {
    QByteArrayData data[28];
    char stringdata0[337];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientWidget_t qt_meta_stringdata_ClientWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ClientWidget"
QT_MOC_LITERAL(1, 13, 12), // "onBtnConnect"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "onBtnGetMenu"
QT_MOC_LITERAL(4, 40, 16), // "onBtnSubmitOrder"
QT_MOC_LITERAL(5, 57, 14), // "onBtnClearCart"
QT_MOC_LITERAL(6, 72, 16), // "onBtnSelectTheme"
QT_MOC_LITERAL(7, 89, 18), // "onBtnSetBackground"
QT_MOC_LITERAL(8, 108, 20), // "onBtnClearBackground"
QT_MOC_LITERAL(9, 129, 9), // "onBtnExit"
QT_MOC_LITERAL(10, 139, 9), // "onTimeout"
QT_MOC_LITERAL(11, 149, 14), // "onMenuReceived"
QT_MOC_LITERAL(12, 164, 8), // "menuData"
QT_MOC_LITERAL(13, 173, 13), // "onOrderResult"
QT_MOC_LITERAL(14, 187, 7), // "success"
QT_MOC_LITERAL(15, 195, 7), // "orderId"
QT_MOC_LITERAL(16, 203, 3), // "msg"
QT_MOC_LITERAL(17, 207, 13), // "onCartChanged"
QT_MOC_LITERAL(18, 221, 19), // "onTotalPriceChanged"
QT_MOC_LITERAL(19, 241, 5), // "total"
QT_MOC_LITERAL(20, 247, 11), // "onAddToCart"
QT_MOC_LITERAL(21, 259, 6), // "dishId"
QT_MOC_LITERAL(22, 266, 8), // "dishName"
QT_MOC_LITERAL(23, 275, 5), // "price"
QT_MOC_LITERAL(24, 281, 5), // "count"
QT_MOC_LITERAL(25, 287, 18), // "onCartCountChanged"
QT_MOC_LITERAL(26, 306, 8), // "newCount"
QT_MOC_LITERAL(27, 315, 21) // "onCartRemoveRequested"

    },
    "ClientWidget\0onBtnConnect\0\0onBtnGetMenu\0"
    "onBtnSubmitOrder\0onBtnClearCart\0"
    "onBtnSelectTheme\0onBtnSetBackground\0"
    "onBtnClearBackground\0onBtnExit\0onTimeout\0"
    "onMenuReceived\0menuData\0onOrderResult\0"
    "success\0orderId\0msg\0onCartChanged\0"
    "onTotalPriceChanged\0total\0onAddToCart\0"
    "dishId\0dishName\0price\0count\0"
    "onCartCountChanged\0newCount\0"
    "onCartRemoveRequested"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    1,  103,    2, 0x08 /* Private */,
      13,    3,  106,    2, 0x08 /* Private */,
      17,    0,  113,    2, 0x08 /* Private */,
      18,    1,  114,    2, 0x08 /* Private */,
      20,    4,  117,    2, 0x08 /* Private */,
      25,    2,  126,    2, 0x08 /* Private */,
      27,    1,  131,    2, 0x08 /* Private */,

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
    QMetaType::Void, QMetaType::QJsonArray,   12,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::QString,   14,   15,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Double, QMetaType::Int,   21,   22,   23,   24,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   21,   26,
    QMetaType::Void, QMetaType::Int,   21,

       0        // eod
};

void ClientWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClientWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onBtnConnect(); break;
        case 1: _t->onBtnGetMenu(); break;
        case 2: _t->onBtnSubmitOrder(); break;
        case 3: _t->onBtnClearCart(); break;
        case 4: _t->onBtnSelectTheme(); break;
        case 5: _t->onBtnSetBackground(); break;
        case 6: _t->onBtnClearBackground(); break;
        case 7: _t->onBtnExit(); break;
        case 8: _t->onTimeout(); break;
        case 9: _t->onMenuReceived((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 10: _t->onOrderResult((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 11: _t->onCartChanged(); break;
        case 12: _t->onTotalPriceChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->onAddToCart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 14: _t->onCartCountChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->onCartRemoveRequested((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ClientWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ClientWidget.data,
    qt_meta_data_ClientWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ClientWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ClientWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
