/****************************************************************************
** Meta object code from reading C++ file 'BM_SceneManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/BM_SceneManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BM_SceneManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BLOCKMOD__SceneManager_t {
    QByteArrayData data[9];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BLOCKMOD__SceneManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BLOCKMOD__SceneManager_t qt_meta_stringdata_BLOCKMOD__SceneManager = {
    {
QT_MOC_LITERAL(0, 0, 22), // "BLOCKMOD::SceneManager"
QT_MOC_LITERAL(1, 23, 18), // "newConnectionAdded"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 20), // "blockActionTriggered"
QT_MOC_LITERAL(4, 64, 16), // "const BlockItem*"
QT_MOC_LITERAL(5, 81, 9), // "blockItem"
QT_MOC_LITERAL(6, 91, 16), // "newBlockSelected"
QT_MOC_LITERAL(7, 108, 9), // "blockName"
QT_MOC_LITERAL(8, 118, 22) // "networkGeometryChanged"

    },
    "BLOCKMOD::SceneManager\0newConnectionAdded\0"
    "\0blockActionTriggered\0const BlockItem*\0"
    "blockItem\0newBlockSelected\0blockName\0"
    "networkGeometryChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BLOCKMOD__SceneManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,
       6,    1,   38,    2, 0x06 /* Public */,
       8,    0,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,

       0        // eod
};

void BLOCKMOD::SceneManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SceneManager *_t = static_cast<SceneManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newConnectionAdded(); break;
        case 1: _t->blockActionTriggered((*reinterpret_cast< const BlockItem*(*)>(_a[1]))); break;
        case 2: _t->newBlockSelected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->networkGeometryChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (SceneManager::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SceneManager::newConnectionAdded)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SceneManager::*_t)(const BlockItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SceneManager::blockActionTriggered)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (SceneManager::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SceneManager::newBlockSelected)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (SceneManager::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SceneManager::networkGeometryChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject BLOCKMOD::SceneManager::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_BLOCKMOD__SceneManager.data,
      qt_meta_data_BLOCKMOD__SceneManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BLOCKMOD::SceneManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BLOCKMOD::SceneManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BLOCKMOD__SceneManager.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int BLOCKMOD::SceneManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void BLOCKMOD::SceneManager::newConnectionAdded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BLOCKMOD::SceneManager::blockActionTriggered(const BlockItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BLOCKMOD::SceneManager::newBlockSelected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BLOCKMOD::SceneManager::networkGeometryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
