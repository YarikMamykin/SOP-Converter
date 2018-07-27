/****************************************************************************
** Meta object code from reading C++ file 'Logger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SOP-Converter/logging/Logger/Logger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Logger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_logging__Logger_t {
    QByteArrayData data[7];
    char stringdata[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_logging__Logger_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_logging__Logger_t qt_meta_stringdata_logging__Logger = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 12),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 3),
QT_MOC_LITERAL(4, 34, 9),
QT_MOC_LITERAL(5, 44, 9),
QT_MOC_LITERAL(6, 54, 14)
    },
    "logging::Logger\0logToConsole\0\0log\0"
    "logToFile\0formatLog\0writeLogToFile\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_logging__Logger[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x05,
       4,    1,   37,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    1,   40,    2, 0x08,
       6,    1,   43,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::QString, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void logging::Logger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Logger *_t = static_cast<Logger *>(_o);
        switch (_id) {
        case 0: _t->logToConsole((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->logToFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: { QString _r = _t->formatLog((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: _t->writeLogToFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Logger::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Logger::logToConsole)) {
                *result = 0;
            }
        }
        {
            typedef void (Logger::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Logger::logToFile)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject logging::Logger::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_logging__Logger.data,
      qt_meta_data_logging__Logger,  qt_static_metacall, 0, 0}
};


const QMetaObject *logging::Logger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *logging::Logger::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_logging__Logger.stringdata))
        return static_cast<void*>(const_cast< Logger*>(this));
    return QObject::qt_metacast(_clname);
}

int logging::Logger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void logging::Logger::logToConsole(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void logging::Logger::logToFile(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
