/****************************************************************************
** Meta object code from reading C++ file 'BM_ZoomMeshGraphicsView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/BM_ZoomMeshGraphicsView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BM_ZoomMeshGraphicsView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BLOCKMOD__ZoomMeshGraphicsView_t {
    QByteArrayData data[14];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BLOCKMOD__ZoomMeshGraphicsView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BLOCKMOD__ZoomMeshGraphicsView_t qt_meta_stringdata_BLOCKMOD__ZoomMeshGraphicsView = {
    {
QT_MOC_LITERAL(0, 0, 30), // "BLOCKMOD::ZoomMeshGraphicsView"
QT_MOC_LITERAL(1, 31, 12), // "setGridColor"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 5), // "color"
QT_MOC_LITERAL(4, 51, 14), // "setGridEnabled"
QT_MOC_LITERAL(5, 66, 6), // "zoomIn"
QT_MOC_LITERAL(6, 73, 7), // "zoomOut"
QT_MOC_LITERAL(7, 81, 12), // "setZoomLevel"
QT_MOC_LITERAL(8, 94, 9), // "zoomLevel"
QT_MOC_LITERAL(9, 104, 9), // "resetZoom"
QT_MOC_LITERAL(10, 114, 11), // "setGridStep"
QT_MOC_LITERAL(11, 126, 8), // "gridStep"
QT_MOC_LITERAL(12, 135, 13), // "setResolution"
QT_MOC_LITERAL(13, 149, 3) // "res"

    },
    "BLOCKMOD::ZoomMeshGraphicsView\0"
    "setGridColor\0\0color\0setGridEnabled\0"
    "zoomIn\0zoomOut\0setZoomLevel\0zoomLevel\0"
    "resetZoom\0setGridStep\0gridStep\0"
    "setResolution\0res"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BLOCKMOD__ZoomMeshGraphicsView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       4,    1,   62,    2, 0x0a /* Public */,
       5,    0,   65,    2, 0x0a /* Public */,
       6,    0,   66,    2, 0x0a /* Public */,
       7,    1,   67,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    1,   72,    2, 0x0a /* Public */,
      12,    1,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   13,

       0        // eod
};

void BLOCKMOD::ZoomMeshGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZoomMeshGraphicsView *_t = static_cast<ZoomMeshGraphicsView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setGridColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 1: _t->setGridEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->zoomIn(); break;
        case 3: _t->zoomOut(); break;
        case 4: _t->setZoomLevel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: { int _r = _t->zoomLevel();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->resetZoom(); break;
        case 7: _t->setGridStep((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->setResolution((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject BLOCKMOD::ZoomMeshGraphicsView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_BLOCKMOD__ZoomMeshGraphicsView.data,
      qt_meta_data_BLOCKMOD__ZoomMeshGraphicsView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BLOCKMOD::ZoomMeshGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BLOCKMOD::ZoomMeshGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BLOCKMOD__ZoomMeshGraphicsView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int BLOCKMOD::ZoomMeshGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
