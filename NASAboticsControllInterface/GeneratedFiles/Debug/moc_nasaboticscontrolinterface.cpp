/****************************************************************************
** Meta object code from reading C++ file 'nasaboticscontrolinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../nasaboticscontrolinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nasaboticscontrolinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NASAboticsControlInterface_t {
    QByteArrayData data[7];
    char stringdata[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_NASAboticsControlInterface_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_NASAboticsControlInterface_t qt_meta_stringdata_NASAboticsControlInterface = {
    {
QT_MOC_LITERAL(0, 0, 26),
QT_MOC_LITERAL(1, 27, 11),
QT_MOC_LITERAL(2, 39, 0),
QT_MOC_LITERAL(3, 40, 9),
QT_MOC_LITERAL(4, 50, 19),
QT_MOC_LITERAL(5, 70, 10),
QT_MOC_LITERAL(6, 81, 13)
    },
    "NASAboticsControlInterface\0SetSendRate\0"
    "\0frequency\0AttachNewController\0"
    "new_device\0WriteCommands\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NASAboticsControlInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a,
       4,    1,   32,    2, 0x0a,
       6,    0,   35,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void NASAboticsControlInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NASAboticsControlInterface *_t = static_cast<NASAboticsControlInterface *>(_o);
        switch (_id) {
        case 0: _t->SetSendRate((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->AttachNewController((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->WriteCommands(); break;
        default: ;
        }
    }
}

const QMetaObject NASAboticsControlInterface::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NASAboticsControlInterface.data,
      qt_meta_data_NASAboticsControlInterface,  qt_static_metacall, 0, 0}
};


const QMetaObject *NASAboticsControlInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NASAboticsControlInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NASAboticsControlInterface.stringdata))
        return static_cast<void*>(const_cast< NASAboticsControlInterface*>(this));
    return QWidget::qt_metacast(_clname);
}

int NASAboticsControlInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
