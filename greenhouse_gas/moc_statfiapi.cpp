/****************************************************************************
** Meta object code from reading C++ file 'statfiapi.hh'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "statfiapi.hh"
#include <QtNetwork/QSslError>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'statfiapi.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_statfiApi_t {
    const uint offsetsAndSize[38];
    char stringdata0[261];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_statfiApi_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_statfiApi_t qt_meta_stringdata_statfiApi = {
    {
QT_MOC_LITERAL(0, 9), // "statfiApi"
QT_MOC_LITERAL(10, 17), // "currentUrlChanged"
QT_MOC_LITERAL(28, 0), // ""
QT_MOC_LITERAL(29, 24), // "currentStatuscodeChanged"
QT_MOC_LITERAL(54, 21), // "currentContentChanged"
QT_MOC_LITERAL(76, 16), // "requestCompleted"
QT_MOC_LITERAL(93, 14), // "QNetworkReply*"
QT_MOC_LITERAL(108, 12), // "networkReply"
QT_MOC_LITERAL(121, 12), // "requestError"
QT_MOC_LITERAL(134, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(162, 9), // "errorCode"
QT_MOC_LITERAL(172, 13), // "requestUrlGet"
QT_MOC_LITERAL(186, 3), // "url"
QT_MOC_LITERAL(190, 6), // "header"
QT_MOC_LITERAL(197, 14), // "requestUrlPost"
QT_MOC_LITERAL(212, 4), // "data"
QT_MOC_LITERAL(217, 10), // "currentUrl"
QT_MOC_LITERAL(228, 17), // "currentStatuscode"
QT_MOC_LITERAL(246, 14) // "currentContent"

    },
    "statfiApi\0currentUrlChanged\0\0"
    "currentStatuscodeChanged\0currentContentChanged\0"
    "requestCompleted\0QNetworkReply*\0"
    "networkReply\0requestError\0"
    "QNetworkReply::NetworkError\0errorCode\0"
    "requestUrlGet\0url\0header\0requestUrlPost\0"
    "data\0currentUrl\0currentStatuscode\0"
    "currentContent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_statfiApi[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       3,   97, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    3 /* Public */,
       3,    0,   69,    2, 0x06,    4 /* Public */,
       4,    0,   70,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   71,    2, 0x08,    6 /* Private */,
       8,    1,   74,    2, 0x08,    8 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      11,    2,   77,    2, 0x02,   10 /* Public */,
      11,    1,   82,    2, 0x22,   13 /* Public | MethodCloned */,
      14,    3,   85,    2, 0x02,   15 /* Public */,
      14,    2,   92,    2, 0x22,   19 /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   12,   13,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   12,   15,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   12,   15,

 // properties: name, type, flags
      16, QMetaType::QUrl, 0x00015001, uint(0), 0,
      17, QMetaType::Int, 0x00015001, uint(1), 0,
      18, QMetaType::QString, 0x00015001, uint(2), 0,

       0        // eod
};

void statfiApi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<statfiApi *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->currentUrlChanged(); break;
        case 1: _t->currentStatuscodeChanged(); break;
        case 2: _t->currentContentChanged(); break;
        case 3: _t->requestCompleted((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->requestError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 5: _t->requestUrlGet((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->requestUrlGet((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->requestUrlPost((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 8: _t->requestUrlPost((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (statfiApi::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&statfiApi::currentUrlChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (statfiApi::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&statfiApi::currentStatuscodeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (statfiApi::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&statfiApi::currentContentChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<statfiApi *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QUrl*>(_v) = _t->getCurrentUrl(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->getCurrentStatuscode(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getCurrentContent(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject statfiApi::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_statfiApi.offsetsAndSize,
    qt_meta_data_statfiApi,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_statfiApi_t
, QtPrivate::TypeAndForceComplete<QUrl, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QNetworkReply *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QNetworkReply::NetworkError, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>

>,
    nullptr
} };


const QMetaObject *statfiApi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *statfiApi::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_statfiApi.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int statfiApi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void statfiApi::currentUrlChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void statfiApi::currentStatuscodeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void statfiApi::currentContentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
