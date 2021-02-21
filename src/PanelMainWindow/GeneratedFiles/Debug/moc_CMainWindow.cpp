/****************************************************************************
** Meta object code from reading C++ file 'CMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CMainWindow_t {
    QByteArrayData data[15];
    char stringdata0[265];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CMainWindow_t qt_meta_stringdata_CMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CMainWindow"
QT_MOC_LITERAL(1, 12, 16), // "sigOnAddFirendCB"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11), // "std::string"
QT_MOC_LITERAL(4, 42, 17), // "slotEmitAddFirend"
QT_MOC_LITERAL(5, 60, 21), // "slotRefreshFriendList"
QT_MOC_LITERAL(6, 82, 23), // "slotDoRefreshFriendList"
QT_MOC_LITERAL(7, 106, 22), // "slotHandleCacheChatMsg"
QT_MOC_LITERAL(8, 129, 21), // "net::CBuddyMessagePtr"
QT_MOC_LITERAL(9, 151, 17), // "slotOnAddFirendCB"
QT_MOC_LITERAL(10, 169, 17), // "slotIconActivated"
QT_MOC_LITERAL(11, 187, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(12, 221, 6), // "reason"
QT_MOC_LITERAL(13, 228, 15), // "slotAddChatUser"
QT_MOC_LITERAL(14, 244, 20) // "UC::CUserDataInfoPtr"

    },
    "CMainWindow\0sigOnAddFirendCB\0\0std::string\0"
    "slotEmitAddFirend\0slotRefreshFriendList\0"
    "slotDoRefreshFriendList\0slotHandleCacheChatMsg\0"
    "net::CBuddyMessagePtr\0slotOnAddFirendCB\0"
    "slotIconActivated\0QSystemTrayIcon::ActivationReason\0"
    "reason\0slotAddChatUser\0UC::CUserDataInfoPtr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CMainWindow[] = {

 // content:
       7,       // revision
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

void CMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CMainWindow *_t = static_cast<CMainWindow *>(_o);
        Q_UNUSED(_t)
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
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CMainWindow::*_t)(const std::string & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CMainWindow::sigOnAddFirendCB)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CMainWindow.data,
      qt_meta_data_CMainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CMainWindow.stringdata0))
        return static_cast<void*>(const_cast< CMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CMainWindow::sigOnAddFirendCB(const std::string & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
