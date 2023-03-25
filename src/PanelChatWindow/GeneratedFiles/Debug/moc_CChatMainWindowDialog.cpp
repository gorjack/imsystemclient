/****************************************************************************
** Meta object code from reading C++ file 'CChatMainWindowDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CChatMainWindowDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CChatMainWindowDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CChatMainWindowDialog_t {
    QByteArrayData data[9];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CChatMainWindowDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CChatMainWindowDialog_t qt_meta_stringdata_CChatMainWindowDialog = {
    {
QT_MOC_LITERAL(0, 0, 21), // "CChatMainWindowDialog"
QT_MOC_LITERAL(1, 22, 9), // "slotClose"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 21), // "slotShowCurrentWindow"
QT_MOC_LITERAL(4, 55, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(5, 72, 6), // "nIndex"
QT_MOC_LITERAL(6, 79, 20), // "handleAllTypeMessage"
QT_MOC_LITERAL(7, 100, 21), // "net::CBuddyMessagePtr"
QT_MOC_LITERAL(8, 122, 5) // "pData"

    },
    "CChatMainWindowDialog\0slotClose\0\0"
    "slotShowCurrentWindow\0QListWidgetItem*\0"
    "nIndex\0handleAllTypeMessage\0"
    "net::CBuddyMessagePtr\0pData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CChatMainWindowDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    1,   30,    2, 0x0a /* Public */,
       6,    1,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void CChatMainWindowDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CChatMainWindowDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slotClose(); break;
        case 1: _t->slotShowCurrentWindow((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->handleAllTypeMessage((*reinterpret_cast< const net::CBuddyMessagePtr(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CChatMainWindowDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CChatMainWindowDialog.data,
    qt_meta_data_CChatMainWindowDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CChatMainWindowDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CChatMainWindowDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CChatMainWindowDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "utils::CSingletonT<CChatMainWindowDialog>"))
        return static_cast< utils::CSingletonT<CChatMainWindowDialog>*>(this);
    return QDialog::qt_metacast(_clname);
}

int CChatMainWindowDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
