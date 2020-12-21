/****************************************************************************
** Meta object code from reading C++ file 'loginwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/loginwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LoginWindow_t {
    QByteArrayData data[21];
    char stringdata0[236];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoginWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoginWindow_t qt_meta_stringdata_LoginWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "LoginWindow"
QT_MOC_LITERAL(1, 12, 12), // "rotateWindow"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "closeWindow"
QT_MOC_LITERAL(4, 38, 10), // "hideWindow"
QT_MOC_LITERAL(5, 49, 19), // "onLoginStateClicked"
QT_MOC_LITERAL(6, 69, 13), // "onMenuClicked"
QT_MOC_LITERAL(7, 83, 8), // "QAction*"
QT_MOC_LITERAL(8, 92, 6), // "action"
QT_MOC_LITERAL(9, 99, 17), // "onShowAccountInfo"
QT_MOC_LITERAL(10, 117, 5), // "index"
QT_MOC_LITERAL(11, 123, 11), // "accountName"
QT_MOC_LITERAL(12, 135, 12), // "onNetWorkSet"
QT_MOC_LITERAL(13, 148, 15), // "onRemoveAccount"
QT_MOC_LITERAL(14, 164, 14), // "onLoginsStatus"
QT_MOC_LITERAL(15, 179, 15), // "UserLoginStatus"
QT_MOC_LITERAL(16, 195, 6), // "status"
QT_MOC_LITERAL(17, 202, 3), // "msg"
QT_MOC_LITERAL(18, 206, 7), // "onLogin"
QT_MOC_LITERAL(19, 214, 8), // "onRegist"
QT_MOC_LITERAL(20, 223, 12) // "slot_timeout"

    },
    "LoginWindow\0rotateWindow\0\0closeWindow\0"
    "hideWindow\0onLoginStateClicked\0"
    "onMenuClicked\0QAction*\0action\0"
    "onShowAccountInfo\0index\0accountName\0"
    "onNetWorkSet\0onRemoveAccount\0"
    "onLoginsStatus\0UserLoginStatus\0status\0"
    "msg\0onLogin\0onRegist\0slot_timeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   77,    2, 0x08 /* Private */,
       6,    1,   78,    2, 0x08 /* Private */,
       9,    2,   81,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    1,   87,    2, 0x08 /* Private */,
      14,    2,   90,    2, 0x08 /* Private */,
      18,    0,   95,    2, 0x08 /* Private */,
      19,    0,   96,    2, 0x08 /* Private */,
      20,    0,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, 0x80000000 | 15, QMetaType::QString,   16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LoginWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoginWindow *_t = static_cast<LoginWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rotateWindow(); break;
        case 1: _t->closeWindow(); break;
        case 2: _t->hideWindow(); break;
        case 3: _t->onLoginStateClicked(); break;
        case 4: _t->onMenuClicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 5: _t->onShowAccountInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->onNetWorkSet(); break;
        case 7: _t->onRemoveAccount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onLoginsStatus((*reinterpret_cast< UserLoginStatus(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->onLogin(); break;
        case 10: _t->onRegist(); break;
        case 11: _t->slot_timeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LoginWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoginWindow::rotateWindow)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LoginWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoginWindow::closeWindow)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (LoginWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoginWindow::hideWindow)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject LoginWindow::staticMetaObject = {
    { &BaseWindow::staticMetaObject, qt_meta_stringdata_LoginWindow.data,
      qt_meta_data_LoginWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LoginWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LoginWindow.stringdata0))
        return static_cast<void*>(const_cast< LoginWindow*>(this));
    return BaseWindow::qt_metacast(_clname);
}

int LoginWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void LoginWindow::rotateWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void LoginWindow::closeWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void LoginWindow::hideWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
