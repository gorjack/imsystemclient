/****************************************************************************
** Meta object code from reading C++ file 'CSoundPlayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CSoundPlayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CSoundPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_XP__CSoundPlayer_t {
    QByteArrayData data[5];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_XP__CSoundPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_XP__CSoundPlayer_t qt_meta_stringdata_XP__CSoundPlayer = {
    {
QT_MOC_LITERAL(0, 0, 16), // "XP::CSoundPlayer"
QT_MOC_LITERAL(1, 17, 14), // "sigSoundSwitch"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 15), // "slotSoundSwitch"
QT_MOC_LITERAL(4, 49, 4) // "bRun"

    },
    "XP::CSoundPlayer\0sigSoundSwitch\0\0"
    "slotSoundSwitch\0bRun"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_XP__CSoundPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   27,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    4,

       0        // eod
};

void XP::CSoundPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CSoundPlayer *_t = static_cast<CSoundPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigSoundSwitch((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slotSoundSwitch((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CSoundPlayer::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CSoundPlayer::sigSoundSwitch)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject XP::CSoundPlayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_XP__CSoundPlayer.data,
      qt_meta_data_XP__CSoundPlayer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *XP::CSoundPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *XP::CSoundPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_XP__CSoundPlayer.stringdata0))
        return static_cast<void*>(const_cast< CSoundPlayer*>(this));
    if (!strcmp(_clname, "utils::CSingletonT<CSoundPlayer>"))
        return static_cast< utils::CSingletonT<CSoundPlayer>*>(const_cast< CSoundPlayer*>(this));
    return QObject::qt_metacast(_clname);
}

int XP::CSoundPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void XP::CSoundPlayer::sigSoundSwitch(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
