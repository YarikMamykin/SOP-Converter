/****************************************************************************
** Meta object code from reading C++ file 'ClientManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SOP-Converter/configuration/ClientManager/ClientManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_configuration__ClientManager_t {
    QByteArrayData data[12];
    char stringdata[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_configuration__ClientManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_configuration__ClientManager_t qt_meta_stringdata_configuration__ClientManager = {
    {
QT_MOC_LITERAL(0, 0, 28),
QT_MOC_LITERAL(1, 29, 12),
QT_MOC_LITERAL(2, 42, 0),
QT_MOC_LITERAL(3, 43, 10),
QT_MOC_LITERAL(4, 54, 11),
QT_MOC_LITERAL(5, 66, 9),
QT_MOC_LITERAL(6, 76, 9),
QT_MOC_LITERAL(7, 86, 8),
QT_MOC_LITERAL(8, 95, 9),
QT_MOC_LITERAL(9, 105, 8),
QT_MOC_LITERAL(10, 114, 13),
QT_MOC_LITERAL(11, 128, 18)
    },
    "configuration::ClientManager\0clearConsole\0"
    "\0clearTable\0clearTpSets\0notifyAll\0"
    "syncFiles\0syncMaps\0disableUi\0enableUi\0"
    "startSyncMaps\0collectSyncResults\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_configuration__ClientManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x05,
       3,    0,   65,    2, 0x05,
       4,    0,   66,    2, 0x05,
       5,    0,   67,    2, 0x05,
       6,    0,   68,    2, 0x05,
       7,    0,   69,    2, 0x05,
       8,    0,   70,    2, 0x05,
       9,    0,   71,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      10,    0,   72,    2, 0x0a,
      11,    2,   73,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,

       0        // eod
};

void configuration::ClientManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientManager *_t = static_cast<ClientManager *>(_o);
        switch (_id) {
        case 0: _t->clearConsole(); break;
        case 1: _t->clearTable(); break;
        case 2: _t->clearTpSets(); break;
        case 3: _t->notifyAll(); break;
        case 4: _t->syncFiles(); break;
        case 5: _t->syncMaps(); break;
        case 6: _t->disableUi(); break;
        case 7: _t->enableUi(); break;
        case 8: _t->startSyncMaps(); break;
        case 9: _t->collectSyncResults((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ClientManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientManager::clearConsole)) {
                *result = 0;
            }
        }
        {
            typedef void (ClientManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientManager::clearTable)) {
                *result = 1;
            }
        }
        {
            typedef void (ClientManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientManager::clearTpSets)) {
                *result = 2;
            }
        }
        {
            typedef void (ClientManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientManager::notifyAll)) {
                *result = 3;
            }
        }
        {
            typedef void (ClientManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientManager::syncFiles)) {
                *result = 4;
            }
        }
        {
            typedef void (ClientManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientManager::syncMaps)) {
                *result = 5;
            }
        }
        {
            typedef void (ClientManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientManager::disableUi)) {
                *result = 6;
            }
        }
        {
            typedef void (ClientManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientManager::enableUi)) {
                *result = 7;
            }
        }
    }
}

const QMetaObject configuration::ClientManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_configuration__ClientManager.data,
      qt_meta_data_configuration__ClientManager,  qt_static_metacall, 0, 0}
};


const QMetaObject *configuration::ClientManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *configuration::ClientManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_configuration__ClientManager.stringdata))
        return static_cast<void*>(const_cast< ClientManager*>(this));
    return QObject::qt_metacast(_clname);
}

int configuration::ClientManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void configuration::ClientManager::clearConsole()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void configuration::ClientManager::clearTable()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void configuration::ClientManager::clearTpSets()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void configuration::ClientManager::notifyAll()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void configuration::ClientManager::syncFiles()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void configuration::ClientManager::syncMaps()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void configuration::ClientManager::disableUi()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void configuration::ClientManager::enableUi()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}
QT_END_MOC_NAMESPACE
