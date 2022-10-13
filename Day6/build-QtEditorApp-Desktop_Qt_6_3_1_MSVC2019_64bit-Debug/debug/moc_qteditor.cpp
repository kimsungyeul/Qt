/****************************************************************************
** Meta object code from reading C++ file 'qteditor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QtEditorApp/qteditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qteditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtEditor_t {
    const uint offsetsAndSize[44];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QtEditor_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QtEditor_t qt_meta_stringdata_QtEditor = {
    {
QT_MOC_LITERAL(0, 8), // "QtEditor"
QT_MOC_LITERAL(9, 7), // "newFile"
QT_MOC_LITERAL(17, 0), // ""
QT_MOC_LITERAL(18, 8), // "openFile"
QT_MOC_LITERAL(27, 8), // "saveFile"
QT_MOC_LITERAL(36, 10), // "saveasFile"
QT_MOC_LITERAL(47, 9), // "printFile"
QT_MOC_LITERAL(57, 4), // "undo"
QT_MOC_LITERAL(62, 4), // "redo"
QT_MOC_LITERAL(67, 4), // "copy"
QT_MOC_LITERAL(72, 3), // "cut"
QT_MOC_LITERAL(76, 5), // "paste"
QT_MOC_LITERAL(82, 6), // "zoomIn"
QT_MOC_LITERAL(89, 7), // "zoomOut"
QT_MOC_LITERAL(97, 9), // "alignText"
QT_MOC_LITERAL(107, 13), // "connectWindow"
QT_MOC_LITERAL(121, 14), // "QMdiSubWindow*"
QT_MOC_LITERAL(136, 11), // "setTextFont"
QT_MOC_LITERAL(148, 11), // "setTextSize"
QT_MOC_LITERAL(160, 13), // "setFontWidget"
QT_MOC_LITERAL(174, 16), // "setCurrentWindow"
QT_MOC_LITERAL(191, 5) // "about"

    },
    "QtEditor\0newFile\0\0openFile\0saveFile\0"
    "saveasFile\0printFile\0undo\0redo\0copy\0"
    "cut\0paste\0zoomIn\0zoomOut\0alignText\0"
    "connectWindow\0QMdiSubWindow*\0setTextFont\0"
    "setTextSize\0setFontWidget\0setCurrentWindow\0"
    "about"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtEditor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  128,    2, 0x0a,    1 /* Public */,
       3,    0,  129,    2, 0x0a,    2 /* Public */,
       4,    0,  130,    2, 0x0a,    3 /* Public */,
       5,    0,  131,    2, 0x0a,    4 /* Public */,
       6,    0,  132,    2, 0x0a,    5 /* Public */,
       7,    0,  133,    2, 0x0a,    6 /* Public */,
       8,    0,  134,    2, 0x0a,    7 /* Public */,
       9,    0,  135,    2, 0x0a,    8 /* Public */,
      10,    0,  136,    2, 0x0a,    9 /* Public */,
      11,    0,  137,    2, 0x0a,   10 /* Public */,
      12,    0,  138,    2, 0x0a,   11 /* Public */,
      13,    0,  139,    2, 0x0a,   12 /* Public */,
      14,    0,  140,    2, 0x0a,   13 /* Public */,
      15,    1,  141,    2, 0x0a,   14 /* Public */,
      17,    1,  144,    2, 0x0a,   16 /* Public */,
      18,    1,  147,    2, 0x0a,   18 /* Public */,
      19,    0,  150,    2, 0x0a,   20 /* Public */,
      20,    0,  151,    2, 0x0a,   21 /* Public */,
      21,    0,  152,    2, 0x0a,   22 /* Public */,

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
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, QMetaType::QFont,    2,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newFile(); break;
        case 1: _t->openFile(); break;
        case 2: _t->saveFile(); break;
        case 3: _t->saveasFile(); break;
        case 4: _t->printFile(); break;
        case 5: _t->undo(); break;
        case 6: _t->redo(); break;
        case 7: _t->copy(); break;
        case 8: _t->cut(); break;
        case 9: _t->paste(); break;
        case 10: _t->zoomIn(); break;
        case 11: _t->zoomOut(); break;
        case 12: _t->alignText(); break;
        case 13: _t->connectWindow((*reinterpret_cast< std::add_pointer_t<QMdiSubWindow*>>(_a[1]))); break;
        case 14: _t->setTextFont((*reinterpret_cast< std::add_pointer_t<QFont>>(_a[1]))); break;
        case 15: _t->setTextSize((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 16: _t->setFontWidget(); break;
        case 17: _t->setCurrentWindow(); break;
        case 18: _t->about(); break;
        default: ;
        }
    }
}

const QMetaObject QtEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_QtEditor.offsetsAndSize,
    qt_meta_data_QtEditor,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QtEditor_t
, QtPrivate::TypeAndForceComplete<QtEditor, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMdiSubWindow *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QFont, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *QtEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtEditor.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QtEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
