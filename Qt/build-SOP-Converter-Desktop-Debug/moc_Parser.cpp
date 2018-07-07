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
    QByteArrayData data[14];
    char stringdata[162];
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
QT_MOC_LITERAL(3, 36, 6),
QT_MOC_LITERAL(4, 43, 22),
QT_MOC_LITERAL(5, 66, 5),
QT_MOC_LITERAL(6, 72, 6),
QT_MOC_LITERAL(7, 79, 5),
QT_MOC_LITERAL(8, 85, 13),
QT_MOC_LITERAL(9, 99, 5),
QT_MOC_LITERAL(10, 105, 16),
QT_MOC_LITERAL(11, 122, 6),
QT_MOC_LITERAL(12, 129, 24),
QT_MOC_LITERAL(13, 154, 6)
    },
    "configuration::Parser\0startParsing\0\0"
    "parseP\0std::shared_ptr<QFile>\0pFile\0"
    "parseU\0uFile\0parseBoundary\0bFile\0"
    "parseControlDict\0cdFile\0"
    "parseTransportProperties\0tpFile\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_configuration__Parser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a,
       3,    1,   45,    2, 0x08,
       6,    1,   48,    2, 0x08,
       8,    1,   51,    2, 0x08,
      10,    1,   54,    2, 0x08,
      12,    1,   57,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 4,    5,
    QMetaType::Bool, 0x80000000 | 4,    7,
    QMetaType::Bool, 0x80000000 | 4,    9,
    QMetaType::Bool, 0x80000000 | 4,   11,
    QMetaType::Bool, 0x80000000 | 4,   13,

       0        // eod
};

void configuration::Parser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Parser *_t = static_cast<Parser *>(_o);
        switch (_id) {
        case 0: _t->startParsing(); break;
        case 1: { bool _r = _t->parseP((*reinterpret_cast< std::shared_ptr<QFile>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->parseU((*reinterpret_cast< std::shared_ptr<QFile>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->parseBoundary((*reinterpret_cast< std::shared_ptr<QFile>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->parseControlDict((*reinterpret_cast< std::shared_ptr<QFile>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->parseTransportProperties((*reinterpret_cast< std::shared_ptr<QFile>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
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
QT_END_MOC_NAMESPACE
