/****************************************************************************
** Meta object code from reading C++ file 'Synchronizer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SOP-Converter/configuration/Synchronizer/Synchronizer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Synchronizer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_configuration__Synchronizer_t {
    QByteArrayData data[10];
    char stringdata[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_configuration__Synchronizer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_configuration__Synchronizer_t qt_meta_stringdata_configuration__Synchronizer = {
    {
QT_MOC_LITERAL(0, 0, 27),
QT_MOC_LITERAL(1, 28, 8),
QT_MOC_LITERAL(2, 37, 0),
QT_MOC_LITERAL(3, 38, 3),
QT_MOC_LITERAL(4, 42, 7),
QT_MOC_LITERAL(5, 50, 21),
QT_MOC_LITERAL(6, 72, 2),
QT_MOC_LITERAL(7, 75, 2),
QT_MOC_LITERAL(8, 78, 17),
QT_MOC_LITERAL(9, 96, 21)
    },
    "configuration::Synchronizer\0finished\0"
    "\0end\0execute\0executeFileSyncRunner\0"
    "ID\0id\0getFileSyncRunner\0std::function<void()>\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_configuration__Synchronizer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x05,
       3,    2,   40,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       4,    0,   45,    2, 0x0a,
       5,    1,   46,    2, 0x0a,
       8,    1,   49,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    0x80000000 | 9, 0x80000000 | 6,    7,

       0        // eod
};

void configuration::Synchronizer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Synchronizer *_t = static_cast<Synchronizer *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->end((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->execute(); break;
        case 3: _t->executeFileSyncRunner((*reinterpret_cast< ID(*)>(_a[1]))); break;
        case 4: { std::function<void()> _r = _t->getFileSyncRunner((*reinterpret_cast< ID(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::function<void()>*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Synchronizer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Synchronizer::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (Synchronizer::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Synchronizer::end)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject configuration::Synchronizer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_configuration__Synchronizer.data,
      qt_meta_data_configuration__Synchronizer,  qt_static_metacall, 0, 0}
};


const QMetaObject *configuration::Synchronizer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *configuration::Synchronizer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_configuration__Synchronizer.stringdata))
        return static_cast<void*>(const_cast< Synchronizer*>(this));
    return QObject::qt_metacast(_clname);
}

int configuration::Synchronizer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void configuration::Synchronizer::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void configuration::Synchronizer::end(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_configuration__SynchronizerThread_t {
    QByteArrayData data[3];
    char stringdata[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_configuration__SynchronizerThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_configuration__SynchronizerThread_t qt_meta_stringdata_configuration__SynchronizerThread = {
    {
QT_MOC_LITERAL(0, 0, 33),
QT_MOC_LITERAL(1, 34, 5),
QT_MOC_LITERAL(2, 40, 0)
    },
    "configuration::SynchronizerThread\0"
    "start\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_configuration__SynchronizerThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x05,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void configuration::SynchronizerThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SynchronizerThread *_t = static_cast<SynchronizerThread *>(_o);
        switch (_id) {
        case 0: _t->start(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SynchronizerThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SynchronizerThread::start)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject configuration::SynchronizerThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_configuration__SynchronizerThread.data,
      qt_meta_data_configuration__SynchronizerThread,  qt_static_metacall, 0, 0}
};


const QMetaObject *configuration::SynchronizerThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *configuration::SynchronizerThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_configuration__SynchronizerThread.stringdata))
        return static_cast<void*>(const_cast< SynchronizerThread*>(this));
    return QObject::qt_metacast(_clname);
}

int configuration::SynchronizerThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void configuration::SynchronizerThread::start()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
