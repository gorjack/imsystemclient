/****************************************************************************
** Meta object code from reading C++ file 'CQueryForAddDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CQueryForAddDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQueryForAddDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CQueryForAddDialog_t {
    QByteArrayData data[7];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQueryForAddDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQueryForAddDialog_t qt_meta_stringdata_CQueryForAddDialog = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CQueryForAddDialog"
QT_MOC_LITERAL(1, 19, 23), // "sigOnFindFirendCallBack"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 16), // "sigOnAddFirendCB"
QT_MOC_LITERAL(4, 61, 14), // "slotFindFriend"
QT_MOC_LITERAL(5, 76, 24), // "slotOnFindFirendCallBack"
QT_MOC_LITERAL(6, 101, 17) // "slotOnAddFirendCB"

    },
    "CQueryForAddDialog\0sigOnFindFirendCallBack\0"
    "\0sigOnAddFirendCB\0slotFindFriend\0"
    "slotOnFindFirendCallBack\0slotOnAddFirendCB"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQueryForAddDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   41,    2, 0x09 /* Protected */,
       5,    0,   42,    2, 0x09 /* Protected */,
       6,    0,   43,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CQueryForAddDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CQueryForAddDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sigOnFindFirendCallBack(); break;
        case 1: _t->sigOnAddFirendCB(); break;
        case 2: _t->slotFindFriend(); break;
        case 3: _t->slotOnFindFirendCallBack(); break;
        case 4: _t->slotOnAddFirendCB(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CQueryForAddDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQueryForAddDialog::sigOnFindFirendCallBack)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CQueryForAddDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQueryForAddDialog::sigOnAddFirendCB)) {
                *result = 1;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject CQueryForAddDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CQueryForAddDialog.data,
    qt_meta_data_CQueryForAddDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CQueryForAddDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQueryForAddDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CQueryForAddDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CQueryForAddDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CQueryForAddDialog::sigOnFindFirendCallBack()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CQueryForAddDialog::sigOnAddFirendCB()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
