/****************************************************************************
** Meta object code from reading C++ file 'Parser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SOP-Converter/configuration/Parser/Parser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Parser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_configuration__Parser_t {
    QByteArrayData data[22];
    char stringdata[303];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_configuration__Parser_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_configuration__Parser_t qt_meta_stringdata_configuration__Parser = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 12),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 11),
QT_MOC_LITERAL(4, 48, 11),
QT_MOC_LITERAL(5, 60, 18),
QT_MOC_LITERAL(6, 79, 21),
QT_MOC_LITERAL(7, 101, 29),
QT_MOC_LITERAL(8, 131, 10),
QT_MOC_LITERAL(9, 142, 9),
QT_MOC_LITERAL(10, 152, 14),
QT_MOC_LITERAL(11, 167, 8),
QT_MOC_LITERAL(12, 176, 6),
QT_MOC_LITERAL(13, 183, 6),
QT_MOC_LITERAL(14, 190, 13),
QT_MOC_LITERAL(15, 204, 16),
QT_MOC_LITERAL(16, 221, 24),
QT_MOC_LITERAL(17, 246, 12),
QT_MOC_LITERAL(18, 259, 6),
QT_MOC_LITERAL(19, 266, 14),
QT_MOC_LITERAL(20, 281, 10),
QT_MOC_LITERAL(21, 292, 9)
    },
    "configuration::Parser\0startParsing\0\0"
    "startParseP\0startParseU\0startParseBoundary\0"
    "startParseControlDict\0"
    "startParseTransportProperties\0endParsing\0"
    "notifyAll\0startSyncFiles\0ParseAll\0"
    "parseP\0parseU\0parseBoundary\0"
    "parseControlDict\0parseTransportProperties\0"
    "parsingEnded\0result\0collectResults\0"
    "resetFlags\0syncFiles\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_configuration__Parser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x05,
       3,    0,  110,    2, 0x05,
       4,    0,  111,    2, 0x05,
       5,    0,  112,    2, 0x05,
       6,    0,  113,    2, 0x05,
       7,    0,  114,    2, 0x05,
       8,    1,  115,    2, 0x05,
       9,    0,  118,    2, 0x05,
      10,    0,  119,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      11,    0,  120,    2, 0x08,
      12,    0,  121,    2, 0x08,
      13,    0,  122,    2, 0x08,
      14,    0,  123,    2, 0x08,
      15,    0,  124,    2, 0x08,
      16,    0,  125,    2, 0x08,
      17,    1,  126,    2, 0x08,
      19,    0,  129,    2, 0x08,
      20,    0,  130,    2, 0x08,
      21,    0,  131,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void configuration::Parser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Parser *_t = static_cast<Parser *>(_o);
        switch (_id) {
        case 0: _t->startParsing(); break;
        case 1: _t->startParseP(); break;
        case 2: _t->startParseU(); break;
        case 3: _t->startParseBoundary(); break;
        case 4: _t->startParseControlDict(); break;
        case 5: _t->startParseTransportProperties(); break;
        case 6: _t->endParsing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->notifyAll(); break;
        case 8: _t->startSyncFiles(); break;
        case 9: _t->ParseAll(); break;
        case 10: _t->parseP(); break;
        case 11: _t->parseU(); break;
        case 12: _t->parseBoundary(); break;
        case 13: _t->parseControlDict(); break;
        case 14: _t->parseTransportProperties(); break;
        case 15: _t->parsingEnded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->collectResults(); break;
        case 17: _t->resetFlags(); break;
        case 18: _t->syncFiles(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Parser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Parser::startParsing)) {
                *result = 0;
            }
        }
        {
            typedef void (Parser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Parser::startParseP)) {
                *result = 1;
            }
        }
        {
            typedef void (Parser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Parser::startParseU)) {
                *result = 2;
            }
        }
        {
            typedef void (Parser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Parser::startParseBoundary)) {
                *result = 3;
            }
        }
        {
            typedef void (Parser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Parser::startParseControlDict)) {
                *result = 4;
            }
        }
        {
            typedef void (Parser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Parser::startParseTransportProperties)) {
                *result = 5;
            }
        }
        {
            typedef void (Parser::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Parser::endParsing)) {
                *result = 6;
            }
        }
        {
            typedef void (Parser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Parser::notifyAll)) {
                *result = 7;
            }
        }
        {
            typedef void (Parser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Parser::startSyncFiles)) {
                *result = 8;
            }
        }
    }
}

const QMetaObject configuration::Parser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_configuration__Parser.data,
      qt_meta_data_configuration__Parser,  qt_static_metacall, 0, 0}
};


const QMetaObject *configuration::Parser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *configuration::Parser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_configuration__Parser.stringdata))
        return static_cast<void*>(const_cast< Parser*>(this));
    return QObject::qt_metacast(_clname);
}

int configuration::Parser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void configuration::Parser::startParsing()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void configuration::Parser::startParseP()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void configuration::Parser::startParseU()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void configuration::Parser::startParseBoundary()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void configuration::Parser::startParseControlDict()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void configuration::Parser::startParseTransportProperties()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void configuration::Parser::endParsing(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void configuration::Parser::notifyAll()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void configuration::Parser::startSyncFiles()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
struct qt_meta_stringdata_configuration__ParserThread_t {
    QByteArrayData data[1];
    char stringdata[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_configuration__ParserThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_configuration__ParserThread_t qt_meta_stringdata_configuration__ParserThread = {
    {
QT_MOC_LITERAL(0, 0, 27)
    },
    "configuration::ParserThread\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_configuration__ParserThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void configuration::ParserThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject configuration::ParserThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_configuration__ParserThread.data,
      qt_meta_data_configuration__ParserThread,  qt_static_metacall, 0, 0}
};


const QMetaObject *configuration::ParserThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *configuration::ParserThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_configuration__ParserThread.stringdata))
        return static_cast<void*>(const_cast< ParserThread*>(this));
    return QThread::qt_metacast(_clname);
}

int configuration::ParserThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
