/****************************************************************************
** Meta object code from reading C++ file 'image_processing.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../image_processing.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'image_processing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Image_processing_t {
    QByteArrayData data[22];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Image_processing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Image_processing_t qt_meta_stringdata_Image_processing = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Image_processing"
QT_MOC_LITERAL(1, 17, 4), // "open"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 4), // "save"
QT_MOC_LITERAL(4, 28, 4), // "exit"
QT_MOC_LITERAL(5, 33, 6), // "saveAs"
QT_MOC_LITERAL(6, 40, 8), // "rotation"
QT_MOC_LITERAL(7, 49, 3), // "cut"
QT_MOC_LITERAL(8, 53, 5), // "light"
QT_MOC_LITERAL(9, 59, 10), // "saturation"
QT_MOC_LITERAL(10, 70, 4), // "tone"
QT_MOC_LITERAL(11, 75, 11), // "linearTrans"
QT_MOC_LITERAL(12, 87, 20), // "piecewiseLinearTrans"
QT_MOC_LITERAL(13, 108, 14), // "nonlinearTrans"
QT_MOC_LITERAL(14, 123, 21), // "histogramEqualization"
QT_MOC_LITERAL(15, 145, 22), // "histogramSpecification"
QT_MOC_LITERAL(16, 168, 12), // "medianFilter"
QT_MOC_LITERAL(17, 181, 12), // "gaussianBlur"
QT_MOC_LITERAL(18, 194, 7), // "sharpen"
QT_MOC_LITERAL(19, 202, 15), // "frequencySmooth"
QT_MOC_LITERAL(20, 218, 16), // "frequencySharpen"
QT_MOC_LITERAL(21, 235, 6) // "filter"

    },
    "Image_processing\0open\0\0save\0exit\0"
    "saveAs\0rotation\0cut\0light\0saturation\0"
    "tone\0linearTrans\0piecewiseLinearTrans\0"
    "nonlinearTrans\0histogramEqualization\0"
    "histogramSpecification\0medianFilter\0"
    "gaussianBlur\0sharpen\0frequencySmooth\0"
    "frequencySharpen\0filter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Image_processing[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x08 /* Private */,
       3,    0,  115,    2, 0x08 /* Private */,
       4,    0,  116,    2, 0x08 /* Private */,
       5,    0,  117,    2, 0x08 /* Private */,
       6,    0,  118,    2, 0x08 /* Private */,
       7,    0,  119,    2, 0x08 /* Private */,
       8,    0,  120,    2, 0x08 /* Private */,
       9,    0,  121,    2, 0x08 /* Private */,
      10,    0,  122,    2, 0x08 /* Private */,
      11,    0,  123,    2, 0x08 /* Private */,
      12,    0,  124,    2, 0x08 /* Private */,
      13,    0,  125,    2, 0x08 /* Private */,
      14,    0,  126,    2, 0x08 /* Private */,
      15,    0,  127,    2, 0x08 /* Private */,
      16,    0,  128,    2, 0x08 /* Private */,
      17,    0,  129,    2, 0x08 /* Private */,
      18,    0,  130,    2, 0x08 /* Private */,
      19,    0,  131,    2, 0x08 /* Private */,
      20,    0,  132,    2, 0x08 /* Private */,
      21,    0,  133,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Image_processing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Image_processing *_t = static_cast<Image_processing *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->open(); break;
        case 1: _t->save(); break;
        case 2: _t->exit(); break;
        case 3: _t->saveAs(); break;
        case 4: _t->rotation(); break;
        case 5: _t->cut(); break;
        case 6: _t->light(); break;
        case 7: _t->saturation(); break;
        case 8: _t->tone(); break;
        case 9: _t->linearTrans(); break;
        case 10: _t->piecewiseLinearTrans(); break;
        case 11: _t->nonlinearTrans(); break;
        case 12: _t->histogramEqualization(); break;
        case 13: _t->histogramSpecification(); break;
        case 14: _t->medianFilter(); break;
        case 15: _t->gaussianBlur(); break;
        case 16: _t->sharpen(); break;
        case 17: _t->frequencySmooth(); break;
        case 18: _t->frequencySharpen(); break;
        case 19: _t->filter(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Image_processing::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Image_processing.data,
      qt_meta_data_Image_processing,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Image_processing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Image_processing::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Image_processing.stringdata0))
        return static_cast<void*>(const_cast< Image_processing*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Image_processing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
