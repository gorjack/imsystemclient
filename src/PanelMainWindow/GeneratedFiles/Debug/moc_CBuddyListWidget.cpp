/****************************************************************************
** Meta object code from reading C++ file 'CBuddyListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CBuddyListWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CBuddyListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CBuddyListWidget_t {
    QByteArrayData data[13];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CBuddyListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CBuddyListWidget_t qt_meta_stringdata_CBuddyListWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CBuddyListWidget"
QT_MOC_LITERAL(1, 17, 14), // "sigAddChatUser"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 20), // "UC::CUserDataInfoPtr"
QT_MOC_LITERAL(4, 54, 12), // "slotAddGroup"
QT_MOC_LITERAL(5, 67, 12), // "slotDelGroup"
QT_MOC_LITERAL(6, 80, 12), // "slotDelBuddy"
QT_MOC_LITERAL(7, 93, 10), // "slotRename"
QT_MOC_LITERAL(8, 104, 19), // "slotRenameEditFshed"
QT_MOC_LITERAL(9, 124, 20), // "slotRefreshBuddyList"
QT_MOC_LITERAL(10, 145, 18), // "slotShowTalkWindow"
QT_MOC_LITERAL(11, 164, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(12, 181, 4) // "item"

    },
    "CBuddyListWidget\0sigAddChatUser\0\0"
    "UC::CUserDataInfoPtr\0slotAddGroup\0"
    "slotDelGroup\0slotDelBuddy\0slotRename\0"
    "slotRenameEditFshed\0slotRefreshBuddyList\0"
    "slotShowTalkWindow\0QListWidgetItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CBuddyListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   57,    2, 0x0a /* Public */,
       5,    0,   58,    2, 0x0a /* Public */,
       6,    0,   59,    2, 0x0a /* Public */,
       7,    0,   60,    2, 0x0a /* Public */,
       8,    0,   61,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    1,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void CBuddyListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CBuddyListWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sigAddChatUser((*reinterpret_cast< const UC::CUserDataInfoPtr(*)>(_a[1]))); break;
        case 1: _t->slotAddGroup(); break;
        case 2: _t->slotDelGroup(); break;
        case 3: _t->slotDelBuddy(); break;
        case 4: _t->slotRename(); break;
        case 5: _t->slotRenameEditFshed(); break;
        case 6: _t->slotRefreshBuddyList(); break;
        case 7: _t->slotShowTalkWindow((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CBuddyListWidget::*)(const UC::CUserDataInfoPtr & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CBuddyListWidget::sigAddChatUser)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CBuddyListWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QListWidget::staticMetaObject>(),
    qt_meta_stringdata_CBuddyListWidget.data,
    qt_meta_data_CBuddyListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CBuddyListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CBuddyListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CBuddyListWidget.stringdata0))
        return static_cast<void*>(this);
    return QListWidget::qt_metacast(_clname);
}

int CBuddyListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
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
void CBuddyListWidget::sigAddChatUser(const UC::CUserDataInfoPtr & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
