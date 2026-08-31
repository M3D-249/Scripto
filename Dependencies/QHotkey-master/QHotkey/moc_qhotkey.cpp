/****************************************************************************
** Meta object code from reading C++ file 'qhotkey.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qhotkey.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhotkey.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7QHotkeyE_t {};
} // unnamed namespace

template <> constexpr inline auto QHotkey::qt_create_metaobjectdata<qt_meta_tag_ZN7QHotkeyE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "QHotkey",
        "activated",
        "",
        "released",
        "registeredChanged",
        "registered",
        "setRegistered",
        "setShortcut",
        "QKeySequence",
        "shortcut",
        "autoRegister",
        "Qt::Key",
        "keyCode",
        "Qt::KeyboardModifiers",
        "modifiers",
        "resetShortcut",
        "setNativeShortcut",
        "QHotkey::NativeShortcut",
        "nativeShortcut"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'activated'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'released'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'registeredChanged'
        QtMocHelpers::SignalData<void(bool)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 5 },
        }}),
        // Slot 'setRegistered'
        QtMocHelpers::SlotData<bool(bool)>(6, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Bool, 5 },
        }}),
        // Slot 'setShortcut'
        QtMocHelpers::SlotData<bool(const QKeySequence &, bool)>(7, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 8, 9 }, { QMetaType::Bool, 10 },
        }}),
        // Slot 'setShortcut'
        QtMocHelpers::SlotData<bool(const QKeySequence &)>(7, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Bool, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'setShortcut'
        QtMocHelpers::SlotData<bool(Qt::Key, Qt::KeyboardModifiers, bool)>(7, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 11, 12 }, { 0x80000000 | 13, 14 }, { QMetaType::Bool, 10 },
        }}),
        // Slot 'setShortcut'
        QtMocHelpers::SlotData<bool(Qt::Key, Qt::KeyboardModifiers)>(7, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Bool, {{
            { 0x80000000 | 11, 12 }, { 0x80000000 | 13, 14 },
        }}),
        // Slot 'resetShortcut'
        QtMocHelpers::SlotData<bool()>(15, 2, QMC::AccessPublic, QMetaType::Bool),
        // Slot 'setNativeShortcut'
        QtMocHelpers::SlotData<bool(QHotkey::NativeShortcut, bool)>(16, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 17, 18 }, { QMetaType::Bool, 10 },
        }}),
        // Slot 'setNativeShortcut'
        QtMocHelpers::SlotData<bool(QHotkey::NativeShortcut)>(16, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Bool, {{
            { 0x80000000 | 17, 18 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'registered'
        QtMocHelpers::PropertyData<bool>(5, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'shortcut'
        QtMocHelpers::PropertyData<QKeySequence>(9, 0x80000000 | 8, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Resettable | QMC::EnumOrFlag | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<QHotkey, qt_meta_tag_ZN7QHotkeyE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject QHotkey::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7QHotkeyE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7QHotkeyE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7QHotkeyE_t>.metaTypes,
    nullptr
} };

void QHotkey::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QHotkey *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->activated(QPrivateSignal()); break;
        case 1: _t->released(QPrivateSignal()); break;
        case 2: _t->registeredChanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: { bool _r = _t->setRegistered((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->setShortcut((*reinterpret_cast<std::add_pointer_t<QKeySequence>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->setShortcut((*reinterpret_cast<std::add_pointer_t<QKeySequence>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->setShortcut((*reinterpret_cast<std::add_pointer_t<Qt::Key>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Qt::KeyboardModifiers>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->setShortcut((*reinterpret_cast<std::add_pointer_t<Qt::Key>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Qt::KeyboardModifiers>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->resetShortcut();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->setNativeShortcut((*reinterpret_cast<std::add_pointer_t<QHotkey::NativeShortcut>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->setNativeShortcut((*reinterpret_cast<std::add_pointer_t<QHotkey::NativeShortcut>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QHotkey::NativeShortcut >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QHotkey::NativeShortcut >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (QHotkey::*)(QPrivateSignal)>(_a, &QHotkey::activated, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (QHotkey::*)(QPrivateSignal)>(_a, &QHotkey::released, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (QHotkey::*)(bool )>(_a, &QHotkey::registeredChanged, 2))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isRegistered(); break;
        case 1: *reinterpret_cast<QKeySequence*>(_v) = _t->shortcut(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRegistered(*reinterpret_cast<bool*>(_v)); break;
        case 1: _t->setShortcut(*reinterpret_cast<QKeySequence*>(_v)); break;
        default: break;
        }
    }
    if (_c == QMetaObject::ResetProperty) {
        switch (_id) {
        case 1: _t->resetShortcut(); break;
        default: break;
        }
    }
}

const QMetaObject *QHotkey::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QHotkey::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7QHotkeyE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QHotkey::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QHotkey::activated(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void QHotkey::released(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void QHotkey::registeredChanged(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
