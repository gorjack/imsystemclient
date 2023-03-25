/****************************************************************************
** Meta object code from reading C++ file 'loginwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/loginwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PC__LoginWindow_t {
    QByteArrayData data[21];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PC__LoginWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PC__LoginWindow_t qt_meta_stringdata_PC__LoginWindow = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PC::LoginWindow"
QT_MOC_LITERAL(1, 16, 12), // "rotateWindow"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11), // "closeWindow"
QT_MOC_LITERAL(4, 42, 10), // "hideWindow"
QT_MOC_LITERAL(5, 53, 19), // "onLoginStateClicked"
QT_MOC_LITERAL(6, 73, 13), // "onMenuClicked"
QT_MOC_LITERAL(7, 87, 8), // "QAction*"
QT_MOC_LITERAL(8, 96, 6), // "action"
QT_MOC_LITERAL(9, 103, 17), // "onShowAccountInfo"
QT_MOC_LITERAL(10, 121, 5), // "index"
QT_MOC_LITERAL(11, 127, 11), // "accountName"
QT_MOC_LITERAL(12, 139, 12), // "onNetWorkSet"
QT_MOC_LITERAL(13, 152, 15), // "onRemoveAccount"
QT_MOC_LITERAL(14, 168, 14), // "onLoginsStatus"
QT_MOC_LITERAL(15, 183, 15), // "UserLoginStatus"
QT_MOC_LITERAL(16, 199, 6), // "status"
QT_MOC_LITERAL(17, 206, 3), // "msg"
QT_MOC_LITERAL(18, 210, 7), // "onLogin"
QT_MOC_LITERAL(19, 218, 8), // "onRegist"
QT_MOC_LITERAL(20, 227, 12) // "slot_timeout"

    },
    "PC::LoginWindow\0rotateWindow\0\0closeWindow\0"
    "hideWindow\0onLoginStateClicked\0"
    "onMenuClicked\0QAction*\0action\0"
    "onShowAccountInfo\0index\0accountName\0"
    "onNetWorkSet\0onRemoveAccount\0"
    "onLoginsStatus\0UserLoginStatus\0status\0"
    "msg\0onLogin\0onRegist\0slot_timeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PC__LoginWindow[] = {

 // content:
       8,       // revision
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

void PC::LoginWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LoginWindow *>(_o);
        (void)_t;
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
        {
            using _t = void (LoginWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWindow::rotateWindow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LoginWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWindow::closeWindow)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LoginWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWindow::hideWindow)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PC::LoginWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWindow::staticMetaObject>(),
    qt_meta_stringdata_PC__LoginWindow.data,
    qt_meta_data_PC__LoginWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PC::LoginWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PC::LoginWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PC__LoginWindow.stringdata0))
        return static_cast<void*>(this);
    return BaseWindow::qt_metacast(_clname);
}

int PC::LoginWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void PC::LoginWindow::rotateWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PC::LoginWindow::closeWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PC::LoginWindow::hideWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
