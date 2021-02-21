/****************************************************************************
** Meta object code from reading C++ file 'CFlamingoClientCenter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CFlamingoClientCenter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CFlamingoClientCenter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CFlamingoClientCenter_t {
    QByteArrayData data[8];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CFlamingoClientCenter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CFlamingoClientCenter_t qt_meta_stringdata_CFlamingoClientCenter = {
    {
QT_MOC_LITERAL(0, 0, 21), // "CFlamingoClientCenter"
QT_MOC_LITERAL(1, 22, 15), // "sigLogindStatus"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 15), // "UserLoginStatus"
QT_MOC_LITERAL(4, 55, 13), // "sigFileStatus"
QT_MOC_LITERAL(5, 69, 9), // "sigStatus"
QT_MOC_LITERAL(6, 79, 21), // "sigChatMessageComming"
QT_MOC_LITERAL(7, 101, 21) // "net::CBuddyMessagePtr"

    },
    "CFlamingoClientCenter\0sigLogindStatus\0"
    "\0UserLoginStatus\0sigFileStatus\0sigStatus\0"
    "sigChatMessageComming\0net::CBuddyMessagePtr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CFlamingoClientCenter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       4,    2,   39,    2, 0x06 /* Public */,
       5,    2,   44,    2, 0x06 /* Public */,
       6,    1,   49,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 7,    2,

       0        // eod
};

void CFlamingoClientCenter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CFlamingoClientCenter *_t = static_cast<CFlamingoClientCenter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigLogindStatus((*reinterpret_cast< UserLoginStatus(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->sigFileStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->sigStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->sigChatMessageComming((*reinterpret_cast< net::CBuddyMessagePtr(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CFlamingoClientCenter::*_t)(UserLoginStatus , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CFlamingoClientCenter::sigLogindStatus)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CFlamingoClientCenter::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CFlamingoClientCenter::sigFileStatus)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CFlamingoClientCenter::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CFlamingoClientCenter::sigStatus)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CFlamingoClientCenter::*_t)(net::CBuddyMessagePtr );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CFlamingoClientCenter::sigChatMessageComming)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject CFlamingoClientCenter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CFlamingoClientCenter.data,
      qt_meta_data_CFlamingoClientCenter,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CFlamingoClientCenter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CFlamingoClientCenter::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CFlamingoClientCenter.stringdata0))
        return static_cast<void*>(const_cast< CFlamingoClientCenter*>(this));
    if (!strcmp(_clname, "utils::CSingletonT<CFlamingoClientCenter>"))
        return static_cast< utils::CSingletonT<CFlamingoClientCenter>*>(const_cast< CFlamingoClientCenter*>(this));
    return QObject::qt_metacast(_clname);
}

int CFlamingoClientCenter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CFlamingoClientCenter::sigLogindStatus(UserLoginStatus _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CFlamingoClientCenter::sigFileStatus(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CFlamingoClientCenter::sigStatus(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CFlamingoClientCenter::sigChatMessageComming(net::CBuddyMessagePtr _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
