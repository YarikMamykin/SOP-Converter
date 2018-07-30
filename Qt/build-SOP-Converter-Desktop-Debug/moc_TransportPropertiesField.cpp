/****************************************************************************
** Meta object code from reading C++ file 'TransportPropertiesField.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SOP-Converter/Ui/TransportPropertiesField/TransportPropertiesField.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TransportPropertiesField.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Ui__TransportPropertiesField_t {
    QByteArrayData data[7];
    char stringdata[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Ui__TransportPropertiesField_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Ui__TransportPropertiesField_t qt_meta_stringdata_Ui__TransportPropertiesField = {
    {
QT_MOC_LITERAL(0, 0, 28),
QT_MOC_LITERAL(1, 29, 7),
QT_MOC_LITERAL(2, 37, 0),
QT_MOC_LITERAL(3, 38, 7),
QT_MOC_LITERAL(4, 46, 5),
QT_MOC_LITERAL(5, 52, 7),
QT_MOC_LITERAL(6, 60, 6)
    },
    "Ui::TransportPropertiesField\0loadMap\0"
    "\0syncMap\0reset\0disable\0enable\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui__TransportPropertiesField[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08,
       3,    0,   40,    2, 0x08,
       4,    0,   41,    2, 0x08,
       5,    0,   42,    2, 0x08,
       6,    0,   43,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Ui::TransportPropertiesField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TransportPropertiesField *_t = static_cast<TransportPropertiesField *>(_o);
        switch (_id) {
        case 0: _t->loadMap(); break;
        case 1: _t->syncMap(); break;
        case 2: _t->reset(); break;
        case 3: _t->disable(); break;
        case 4: _t->enable(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Ui::TransportPropertiesField::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_Ui__TransportPropertiesField.data,
      qt_meta_data_Ui__TransportPropertiesField,  qt_static_metacall, 0, 0}
};


const QMetaObject *Ui::TransportPropertiesField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ui::TransportPropertiesField::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ui__TransportPropertiesField.stringdata))
        return static_cast<void*>(const_cast< TransportPropertiesField*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int Ui::TransportPropertiesField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
