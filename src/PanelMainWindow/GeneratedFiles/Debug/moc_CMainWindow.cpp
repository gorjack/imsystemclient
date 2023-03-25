/****************************************************************************
** Meta object code from reading C++ file 'CMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PC__CMainWindow_t {
    QByteArrayData data[15];
    char stringdata0[269];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PC__CMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PC__CMainWindow_t qt_meta_stringdata_PC__CMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PC::CMainWindow"
QT_MOC_LITERAL(1, 16, 16), // "sigOnAddFirendCB"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 11), // "std::string"
QT_MOC_LITERAL(4, 46, 17), // "slotEmitAddFirend"
QT_MOC_LITERAL(5, 64, 21), // "slotRefreshFriendList"
QT_MOC_LITERAL(6, 86, 23), // "slotDoRefreshFriendList"
QT_MOC_LITERAL(7, 110, 22), // "slotHandleCacheChatMsg"
QT_MOC_LITERAL(8, 133, 21), // "net::CBuddyMessagePtr"
QT_MOC_LITERAL(9, 155, 17), // "slotOnAddFirendCB"
QT_MOC_LITERAL(10, 173, 17), // "slotIconActivated"
QT_MOC_LITERAL(11, 191, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(12, 225, 6), // "reason"
QT_MOC_LITERAL(13, 232, 15), // "slotAddChatUser"
QT_MOC_LITERAL(14, 248, 20) // "UC::CUserDataInfoPtr"

    },
    "PC::CMainWindow\0sigOnAddFirendCB\0\0"
    "std::string\0slotEmitAddFirend\0"
    "slotRefreshFriendList\0slotDoRefreshFriendList\0"
    "slotHandleCacheChatMsg\0net::CBuddyMessagePtr\0"
    "slotOnAddFirendCB\0slotIconActivated\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0slotAddChatUser\0UC::CUserDataInfoPtr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PC__CMainWindow[] = {

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
       4,    0,   57,    2, 0x09 /* Protected */,
       5,    0,   58,    2, 0x09 /* Protected */,
       6,    0,   59,    2, 0x09 /* Protected */,
       7,    1,   60,    2, 0x09 /* Protected */,
       9,    1,   63,    2, 0x09 /* Protected */,
      10,    1,   66,    2, 0x09 /* Protected */,
      13,    1,   69,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,    2,

       0        // eod
};

void PC::CMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CMainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sigOnAddFirendCB((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 1: _t->slotEmitAddFirend(); break;
        case 2: _t->slotRefreshFriendList(); break;
        case 3: _t->slotDoRefreshFriendList(); break;
        case 4: _t->slotHandleCacheChatMsg((*reinterpret_cast< net::CBuddyMessagePtr(*)>(_a[1]))); break;
        case 5: _t->slotOnAddFirendCB((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 6: _t->slotIconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 7: _t->slotAddChatUser((*reinterpret_cast< const UC::CUserDataInfoPtr(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CMainWindow::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CMainWindow::sigOnAddFirendCB)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PC::CMainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_PC__CMainWindow.data,
    qt_meta_data_PC__CMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PC::CMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PC::CMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PC__CMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PC::CMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
void PC::CMainWindow::sigOnAddFirendCB(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
