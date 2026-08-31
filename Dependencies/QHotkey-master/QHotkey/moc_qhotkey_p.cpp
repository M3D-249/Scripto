/****************************************************************************
** Meta object code from reading C++ file 'qhotkey_p.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qhotkey_p.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhotkey_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN14QHotkeyPrivateE_t {};
} // unnamed namespace

template <> constexpr inline auto QHotkeyPrivate::qt_create_metaobjectdata<qt_meta_tag_ZN14QHotkeyPrivateE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "QHotkeyPrivate",
        "addMappingInvoked",
        "",
        "Qt::Key",
        "keycode",
        "Qt::KeyboardModifiers",
        "modifiers",
        "QHotkey::NativeShortcut",
        "nativeShortcut",
        "addShortcutInvoked",
        "QHotkey*",
        "hotkey",
        "removeShortcutInvoked",
        "nativeShortcutInvoked"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'addMappingInvoked'
        QtMocHelpers::MethodData<void(Qt::Key, Qt::KeyboardModifiers, QHotkey::NativeShortcut)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 }, { 0x80000000 | 7, 8 },
        }}),
        // Method 'addShortcutInvoked'
        QtMocHelpers::MethodData<bool(QHotkey *)>(9, 2, QMC::AccessPrivate, QMetaType::Bool, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Method 'removeShortcutInvoked'
        QtMocHelpers::MethodData<bool(QHotkey *)>(12, 2, QMC::AccessPrivate, QMetaType::Bool, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Method 'nativeShortcutInvoked'
        QtMocHelpers::MethodData<QHotkey::NativeShortcut(Qt::Key, Qt::KeyboardModifiers)>(13, 2, QMC::AccessPrivate, 0x80000000 | 7, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<QHotkeyPrivate, qt_meta_tag_ZN14QHotkeyPrivateE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject QHotkeyPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14QHotkeyPrivateE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14QHotkeyPrivateE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14QHotkeyPrivateE_t>.metaTypes,
    nullptr
} };

void QHotkeyPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QHotkeyPrivate *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->addMappingInvoked((*reinterpret_cast<std::add_pointer_t<Qt::Key>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Qt::KeyboardModifiers>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QHotkey::NativeShortcut>>(_a[3]))); break;
        case 1: { bool _r = _t->addShortcutInvoked((*reinterpret_cast<std::add_pointer_t<QHotkey*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->removeShortcutInvoked((*reinterpret_cast<std::add_pointer_t<QHotkey*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { QHotkey::NativeShortcut _r = _t->nativeShortcutInvoked((*reinterpret_cast<std::add_pointer_t<Qt::Key>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Qt::KeyboardModifiers>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QHotkey::NativeShortcut*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QHotkey::NativeShortcut >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QHotkey* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QHotkey* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *QHotkeyPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QHotkeyPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14QHotkeyPrivateE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QAbstractNativeEventFilter"))
        return static_cast< QAbstractNativeEventFilter*>(this);
    return QObject::qt_metacast(_clname);
}

int QHotkeyPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
