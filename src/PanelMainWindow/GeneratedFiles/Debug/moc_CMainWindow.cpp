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
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CMainWindow_t qt_meta_stringdata_CMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CMainWindow"
QT_MOC_LITERAL(1, 12, 10), // "sigTestMsg"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 21), // "net::CBuddyMessagePtr"
QT_MOC_LITERAL(4, 46, 16), // "sigOnAddFirendCB"
QT_MOC_LITERAL(5, 63, 11), // "std::string"
QT_MOC_LITERAL(6, 75, 17), // "slotEmitAddFirend"
QT_MOC_LITERAL(7, 93, 21), // "slotRefreshFriendList"
QT_MOC_LITERAL(8, 115, 23), // "slotDoRefreshFriendList"
QT_MOC_LITERAL(9, 139, 22), // "slotHandleCacheChatMsg"
QT_MOC_LITERAL(10, 162, 17), // "slotOnAddFirendCB"
QT_MOC_LITERAL(11, 180, 17), // "slotIconActivated"
QT_MOC_LITERAL(12, 198, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(13, 232, 6), // "reason"
QT_MOC_LITERAL(14, 239, 11) // "slotTestMsg"

    },
    "CMainWindow\0sigTestMsg\0\0net::CBuddyMessagePtr\0"
    "sigOnAddFirendCB\0std::string\0"
    "slotEmitAddFirend\0slotRefreshFriendList\0"
    "slotDoRefreshFriendList\0slotHandleCacheChatMsg\0"
    "slotOnAddFirendCB\0slotIconActivated\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0slotTestMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   65,    2, 0x09 /* Protected */,
       7,    0,   66,    2, 0x09 /* Protected */,
       8,    0,   67,    2, 0x09 /* Protected */,
       9,    1,   68,    2, 0x09 /* Protected */,
      10,    1,   71,    2, 0x09 /* Protected */,
      11,    1,   74,    2, 0x09 /* Protected */,
      14,    1,   77,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void CMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CMainWindow *_t = static_cast<CMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigTestMsg((*reinterpret_cast< const net::CBuddyMessagePtr(*)>(_a[1]))); break;
        case 1: _t->sigOnAddFirendCB((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 2: _t->slotEmitAddFirend(); break;
        case 3: _t->slotRefreshFriendList(); break;
        case 4: _t->slotDoRefreshFriendList(); break;
        case 5: _t->slotHandleCacheChatMsg((*reinterpret_cast< const net::CBuddyMessagePtr(*)>(_a[1]))); break;
        case 6: _t->slotOnAddFirendCB((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 7: _t->slotIconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 8: _t->slotTestMsg((*reinterpret_cast< const net::CBuddyMessagePtr(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CMainWindow::*_t)(const net::CBuddyMessagePtr & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CMainWindow::sigTestMsg)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CMainWindow::*_t)(const std::string & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CMainWindow::sigOnAddFirendCB)) {
                *result = 1;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CMainWindow::sigTestMsg(const net::CBuddyMessagePtr & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CMainWindow::sigOnAddFirendCB(const std::string & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
