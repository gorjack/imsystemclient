/****************************************************************************
** Meta object code from reading C++ file 'CSendMsgTextEdit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CSendMsgTextEdit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CSendMsgTextEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CSendMsgTextEdit_t {
    QByteArrayData data[9];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CSendMsgTextEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CSendMsgTextEdit_t qt_meta_stringdata_CSendMsgTextEdit = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CSendMsgTextEdit"
QT_MOC_LITERAL(1, 17, 10), // "sigSendMsg"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 18), // "sigShowRightWidget"
QT_MOC_LITERAL(4, 48, 11), // "sigSendFile"
QT_MOC_LITERAL(5, 60, 18), // "FileTransferStatus"
QT_MOC_LITERAL(6, 79, 15), // "slotSendMessage"
QT_MOC_LITERAL(7, 95, 20), // "slotOnHandleSendFile"
QT_MOC_LITERAL(8, 116, 19) // "onHandleErrorStatus"

    },
    "CSendMsgTextEdit\0sigSendMsg\0\0"
    "sigShowRightWidget\0sigSendFile\0"
    "FileTransferStatus\0slotSendMessage\0"
    "slotOnHandleSendFile\0onHandleErrorStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CSendMsgTextEdit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    0,   47,    2, 0x06 /* Public */,
       4,    2,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   53,    2, 0x09 /* Protected */,
       7,    0,   54,    2, 0x09 /* Protected */,
       8,    2,   55,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,

       0        // eod
};

void CSendMsgTextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CSendMsgTextEdit *_t = static_cast<CSendMsgTextEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigSendMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sigShowRightWidget(); break;
        case 2: _t->sigSendFile((*reinterpret_cast< const FileTransferStatus(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->slotSendMessage(); break;
        case 4: _t->slotOnHandleSendFile(); break;
        case 5: _t->onHandleErrorStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CSendMsgTextEdit::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CSendMsgTextEdit::sigSendMsg)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CSendMsgTextEdit::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CSendMsgTextEdit::sigShowRightWidget)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CSendMsgTextEdit::*_t)(const FileTransferStatus & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CSendMsgTextEdit::sigSendFile)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CSendMsgTextEdit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CSendMsgTextEdit.data,
      qt_meta_data_CSendMsgTextEdit,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CSendMsgTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CSendMsgTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CSendMsgTextEdit.stringdata0))
        return static_cast<void*>(const_cast< CSendMsgTextEdit*>(this));
    return QWidget::qt_metacast(_clname);
}

int CSendMsgTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CSendMsgTextEdit::sigSendMsg(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CSendMsgTextEdit::sigShowRightWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void CSendMsgTextEdit::sigSendFile(const FileTransferStatus & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
