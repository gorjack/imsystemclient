/****************************************************************************
** Meta object code from reading C++ file 'CChatMessageWindowWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CChatMessageWindowWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CChatMessageWindowWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CChatMessageWindowWidget_t {
    QByteArrayData data[7];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CChatMessageWindowWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CChatMessageWindowWidget_t qt_meta_stringdata_CChatMessageWindowWidget = {
    {
QT_MOC_LITERAL(0, 0, 24), // "CChatMessageWindowWidget"
QT_MOC_LITERAL(1, 25, 16), // "sigHandleChatMsg"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 21), // "net::CBuddyMessagePtr"
QT_MOC_LITERAL(4, 65, 11), // "slotSendMsg"
QT_MOC_LITERAL(5, 77, 17), // "slotHandleChatMsg"
QT_MOC_LITERAL(6, 95, 5) // "pData"

    },
    "CChatMessageWindowWidget\0sigHandleChatMsg\0"
    "\0net::CBuddyMessagePtr\0slotSendMsg\0"
    "slotHandleChatMsg\0pData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CChatMessageWindowWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   32,    2, 0x09 /* Protected */,
       5,    1,   35,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 3,    6,

       0        // eod
};

void CChatMessageWindowWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CChatMessageWindowWidget *_t = static_cast<CChatMessageWindowWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigHandleChatMsg((*reinterpret_cast< const net::CBuddyMessagePtr(*)>(_a[1]))); break;
        case 1: _t->slotSendMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->slotHandleChatMsg((*reinterpret_cast< const net::CBuddyMessagePtr(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CChatMessageWindowWidget::*_t)(const net::CBuddyMessagePtr & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CChatMessageWindowWidget::sigHandleChatMsg)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CChatMessageWindowWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CChatMessageWindowWidget.data,
      qt_meta_data_CChatMessageWindowWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CChatMessageWindowWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CChatMessageWindowWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CChatMessageWindowWidget.stringdata0))
        return static_cast<void*>(const_cast< CChatMessageWindowWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CChatMessageWindowWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CChatMessageWindowWidget::sigHandleChatMsg(const net::CBuddyMessagePtr & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE