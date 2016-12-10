/****************************************************************************
** Meta object code from reading C++ file 'heat_equation.h'
**
** Created: Sat Dec 10 15:06:50 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "heat_equation.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'heat_equation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_heat_equation[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      42,   37,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_heat_equation[] = {
    "heat_equation\0\0on_goButton_clicked()\0"
    "arg1\0on_comboBox_dim_activated(QString)\0"
};

void heat_equation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        heat_equation *_t = static_cast<heat_equation *>(_o);
        switch (_id) {
        case 0: _t->on_goButton_clicked(); break;
        case 1: _t->on_comboBox_dim_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData heat_equation::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject heat_equation::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_heat_equation,
      qt_meta_data_heat_equation, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &heat_equation::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *heat_equation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *heat_equation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_heat_equation))
        return static_cast<void*>(const_cast< heat_equation*>(this));
    return QWidget::qt_metacast(_clname);
}

int heat_equation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
