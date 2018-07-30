/****************************************************************************
** Meta object code from reading C++ file 'Tables.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SOP-Converter/Ui/Tables/Tables.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Tables.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Ui__Cell_t {
    QByteArrayData data[1];
    char stringdata[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Ui__Cell_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Ui__Cell_t qt_meta_stringdata_Ui__Cell = {
    {
QT_MOC_LITERAL(0, 0, 8)
    },
    "Ui::Cell\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui__Cell[] = {

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

void Ui::Cell::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Ui::Cell::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Ui__Cell.data,
      qt_meta_data_Ui__Cell,  qt_static_metacall, 0, 0}
};


const QMetaObject *Ui::Cell::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ui::Cell::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ui__Cell.stringdata))
        return static_cast<void*>(const_cast< Cell*>(this));
    return QObject::qt_metacast(_clname);
}

int Ui::Cell::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_Ui__SetTable_t {
    QByteArrayData data[11];
    char stringdata[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Ui__SetTable_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Ui__SetTable_t qt_meta_stringdata_Ui__SetTable = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 8),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 8),
QT_MOC_LITERAL(4, 32, 14),
QT_MOC_LITERAL(5, 47, 3),
QT_MOC_LITERAL(6, 51, 6),
QT_MOC_LITERAL(7, 58, 10),
QT_MOC_LITERAL(8, 69, 5),
QT_MOC_LITERAL(9, 75, 7),
QT_MOC_LITERAL(10, 83, 6)
    },
    "Ui::SetTable\0syncMaps\0\0loadMaps\0"
    "updateCellInfo\0row\0column\0eraseCells\0"
    "erase\0disable\0enable\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui__SetTable[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08,
       3,    0,   50,    2, 0x08,
       4,    2,   51,    2, 0x08,
       7,    0,   56,    2, 0x08,
       8,    0,   57,    2, 0x08,
       9,    0,   58,    2, 0x08,
      10,    0,   59,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Ui::SetTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SetTable *_t = static_cast<SetTable *>(_o);
        switch (_id) {
        case 0: _t->syncMaps(); break;
        case 1: _t->loadMaps(); break;
        case 2: _t->updateCellInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->eraseCells(); break;
        case 4: _t->erase(); break;
        case 5: _t->disable(); break;
        case 6: _t->enable(); break;
        default: ;
        }
    }
}

const QMetaObject Ui::SetTable::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_Ui__SetTable.data,
      qt_meta_data_Ui__SetTable,  qt_static_metacall, 0, 0}
};


const QMetaObject *Ui::SetTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ui::SetTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ui__SetTable.stringdata))
        return static_cast<void*>(const_cast< SetTable*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int Ui::SetTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_Ui__ControlDictTable_t {
    QByteArrayData data[11];
    char stringdata[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Ui__ControlDictTable_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Ui__ControlDictTable_t qt_meta_stringdata_Ui__ControlDictTable = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 8),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 8),
QT_MOC_LITERAL(4, 40, 14),
QT_MOC_LITERAL(5, 55, 3),
QT_MOC_LITERAL(6, 59, 6),
QT_MOC_LITERAL(7, 66, 10),
QT_MOC_LITERAL(8, 77, 5),
QT_MOC_LITERAL(9, 83, 7),
QT_MOC_LITERAL(10, 91, 6)
    },
    "Ui::ControlDictTable\0syncMaps\0\0loadMaps\0"
    "updateCellInfo\0row\0column\0eraseCells\0"
    "erase\0disable\0enable\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui__ControlDictTable[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08,
       3,    0,   50,    2, 0x08,
       4,    2,   51,    2, 0x08,
       7,    0,   56,    2, 0x08,
       8,    0,   57,    2, 0x08,
       9,    0,   58,    2, 0x08,
      10,    0,   59,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Ui::ControlDictTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ControlDictTable *_t = static_cast<ControlDictTable *>(_o);
        switch (_id) {
        case 0: _t->syncMaps(); break;
        case 1: _t->loadMaps(); break;
        case 2: _t->updateCellInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->eraseCells(); break;
        case 4: _t->erase(); break;
        case 5: _t->disable(); break;
        case 6: _t->enable(); break;
        default: ;
        }
    }
}

const QMetaObject Ui::ControlDictTable::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_Ui__ControlDictTable.data,
      qt_meta_data_Ui__ControlDictTable,  qt_static_metacall, 0, 0}
};


const QMetaObject *Ui::ControlDictTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ui::ControlDictTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ui__ControlDictTable.stringdata))
        return static_cast<void*>(const_cast< ControlDictTable*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int Ui::ControlDictTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
