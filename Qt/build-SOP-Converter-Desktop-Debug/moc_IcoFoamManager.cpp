/****************************************************************************
** Meta object code from reading C++ file 'IcoFoamManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SOP-Converter/management/IcoFoamManager/IcoFoamManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IcoFoamManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_management__IcoFoamManager_t {
    QByteArrayData data[9];
    char stringdata[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_management__IcoFoamManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_management__IcoFoamManager_t qt_meta_stringdata_management__IcoFoamManager = {
    {
QT_MOC_LITERAL(0, 0, 26),
QT_MOC_LITERAL(1, 27, 14),
QT_MOC_LITERAL(2, 42, 0),
QT_MOC_LITERAL(3, 43, 13),
QT_MOC_LITERAL(4, 57, 12),
QT_MOC_LITERAL(5, 70, 10),
QT_MOC_LITERAL(6, 81, 13),
QT_MOC_LITERAL(7, 95, 10),
QT_MOC_LITERAL(8, 106, 14)
    },
    "management::IcoFoamManager\0startExecution\0"
    "\0stopExecution\0clearConsole\0startTimer\0"
    "addSyncResult\0clearFlags\0handleSyncFail\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_management__IcoFoamManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x05,
       3,    0,   50,    2, 0x05,
       4,    0,   51,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x0a,
       6,    2,   53,    2, 0x0a,
       7,    0,   58,    2, 0x0a,
       8,    0,   59,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void management::IcoFoamManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IcoFoamManager *_t = static_cast<IcoFoamManager *>(_o);
        switch (_id) {
        case 0: _t->startExecution(); break;
        case 1: _t->stopExecution(); break;
        case 2: _t->clearConsole(); break;
        case 3: _t->startTimer(); break;
        case 4: _t->addSyncResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->clearFlags(); break;
        case 6: _t->handleSyncFail(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (IcoFoamManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IcoFoamManager::startExecution)) {
                *result = 0;
            }
        }
        {
            typedef void (IcoFoamManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IcoFoamManager::stopExecution)) {
                *result = 1;
            }
        }
        {
            typedef void (IcoFoamManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IcoFoamManager::clearConsole)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject management::IcoFoamManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_management__IcoFoamManager.data,
      qt_meta_data_management__IcoFoamManager,  qt_static_metacall, 0, 0}
};


const QMetaObject *management::IcoFoamManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *management::IcoFoamManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_management__IcoFoamManager.stringdata))
        return static_cast<void*>(const_cast< IcoFoamManager*>(this));
    return QObject::qt_metacast(_clname);
}

int management::IcoFoamManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void management::IcoFoamManager::startExecution()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void management::IcoFoamManager::stopExecution()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void management::IcoFoamManager::clearConsole()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
