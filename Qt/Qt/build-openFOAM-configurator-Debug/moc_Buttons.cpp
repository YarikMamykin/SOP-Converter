/****************************************************************************
** Meta object code from reading C++ file 'Buttons.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../openFOAM-configurator/Buttons.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Buttons.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Ui__StartConvertionButton_t {
    QByteArrayData data[3];
    char stringdata[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Ui__StartConvertionButton_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Ui__StartConvertionButton_t qt_meta_stringdata_Ui__StartConvertionButton = {
    {
QT_MOC_LITERAL(0, 0, 25),
QT_MOC_LITERAL(1, 26, 11),
QT_MOC_LITERAL(2, 38, 0)
    },
    "Ui::StartConvertionButton\0showMessage\0"
    "\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui__StartConvertionButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Ui::StartConvertionButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StartConvertionButton *_t = static_cast<StartConvertionButton *>(_o);
        switch (_id) {
        case 0: _t->showMessage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Ui::StartConvertionButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_Ui__StartConvertionButton.data,
      qt_meta_data_Ui__StartConvertionButton,  qt_static_metacall, 0, 0}
};


const QMetaObject *Ui::StartConvertionButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ui::StartConvertionButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ui__StartConvertionButton.stringdata))
        return static_cast<void*>(const_cast< StartConvertionButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int Ui::StartConvertionButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_Ui__ResetSettingsButton_t {
    QByteArrayData data[3];
    char stringdata[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Ui__ResetSettingsButton_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Ui__ResetSettingsButton_t qt_meta_stringdata_Ui__ResetSettingsButton = {
    {
QT_MOC_LITERAL(0, 0, 23),
QT_MOC_LITERAL(1, 24, 11),
QT_MOC_LITERAL(2, 36, 0)
    },
    "Ui::ResetSettingsButton\0showMessage\0"
    "\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui__ResetSettingsButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Ui::ResetSettingsButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ResetSettingsButton *_t = static_cast<ResetSettingsButton *>(_o);
        switch (_id) {
        case 0: _t->showMessage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Ui::ResetSettingsButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_Ui__ResetSettingsButton.data,
      qt_meta_data_Ui__ResetSettingsButton,  qt_static_metacall, 0, 0}
};


const QMetaObject *Ui::ResetSettingsButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ui::ResetSettingsButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ui__ResetSettingsButton.stringdata))
        return static_cast<void*>(const_cast< ResetSettingsButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int Ui::ResetSettingsButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_Ui__SaveSettingsButton_t {
    QByteArrayData data[3];
    char stringdata[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Ui__SaveSettingsButton_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Ui__SaveSettingsButton_t qt_meta_stringdata_Ui__SaveSettingsButton = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 11),
QT_MOC_LITERAL(2, 35, 0)
    },
    "Ui::SaveSettingsButton\0showMessage\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui__SaveSettingsButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Ui::SaveSettingsButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SaveSettingsButton *_t = static_cast<SaveSettingsButton *>(_o);
        switch (_id) {
        case 0: _t->showMessage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Ui::SaveSettingsButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_Ui__SaveSettingsButton.data,
      qt_meta_data_Ui__SaveSettingsButton,  qt_static_metacall, 0, 0}
};


const QMetaObject *Ui::SaveSettingsButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ui::SaveSettingsButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ui__SaveSettingsButton.stringdata))
        return static_cast<void*>(const_cast< SaveSettingsButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int Ui::SaveSettingsButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
