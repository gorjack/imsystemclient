/****************************************************************************
** Meta object code from reading C++ file 'loginnetsetwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/loginnetsetwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginnetsetwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PC__LoginNetSetWindow_t {
    QByteArrayData data[9];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PC__LoginNetSetWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PC__LoginNetSetWindow_t qt_meta_stringdata_PC__LoginNetSetWindow = {
    {
QT_MOC_LITERAL(0, 0, 21), // "PC::LoginNetSetWindow"
QT_MOC_LITERAL(1, 22, 12), // "rotateWindow"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 11), // "closeWindow"
QT_MOC_LITERAL(4, 48, 10), // "hideWindow"
QT_MOC_LITERAL(5, 59, 8), // "slotOnOk"
QT_MOC_LITERAL(6, 68, 22), // "on_chatTestBtn_clicked"
QT_MOC_LITERAL(7, 91, 23), // "on_imageTestBtn_clicked"
QT_MOC_LITERAL(8, 115, 22) // "on_fileTestBtn_clicked"

    },
    "PC::LoginNetSetWindow\0rotateWindow\0\0"
    "closeWindow\0hideWindow\0slotOnOk\0"
    "on_chatTestBtn_clicked\0on_imageTestBtn_clicked\0"
    "on_fileTestBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PC__LoginNetSetWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x09 /* Protected */,
       6,    0,   53,    2, 0x09 /* Protected */,
       7,    0,   54,    2, 0x09 /* Protected */,
       8,    0,   55,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PC::LoginNetSetWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LoginNetSetWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->rotateWindow(); break;
        case 1: _t->closeWindow(); break;
        case 2: _t->hideWindow(); break;
        case 3: _t->slotOnOk(); break;
        case 4: _t->on_chatTestBtn_clicked(); break;
        case 5: _t->on_imageTestBtn_clicked(); break;
        case 6: _t->on_fileTestBtn_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LoginNetSetWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginNetSetWindow::rotateWindow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LoginNetSetWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginNetSetWindow::closeWindow)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LoginNetSetWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginNetSetWindow::hideWindow)) {
                *result = 2;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject PC::LoginNetSetWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWindow::staticMetaObject>(),
    qt_meta_stringdata_PC__LoginNetSetWindow.data,
    qt_meta_data_PC__LoginNetSetWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PC::LoginNetSetWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PC::LoginNetSetWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PC__LoginNetSetWindow.stringdata0))
        return static_cast<void*>(this);
    return BaseWindow::qt_metacast(_clname);
}

int PC::LoginNetSetWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void PC::LoginNetSetWindow::rotateWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PC::LoginNetSetWindow::closeWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PC::LoginNetSetWindow::hideWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
