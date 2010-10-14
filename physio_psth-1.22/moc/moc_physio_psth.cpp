/****************************************************************************
** Meta object code from reading C++ file 'physio_psth.h'
**
** Created: Thu Jan 14 00:29:30 2010
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../physio_psth.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'physio_psth.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      24,   11,   11,   11, 0x08,
      40,   11,   11,   11, 0x08,
      60,   58,   11,   11, 0x08,
      85,   83,   11,   11, 0x08,
     113,  111,   11,   11, 0x08,
     139,  137,   11,   11, 0x08,
     165,   11,   11,   11, 0x08,
     180,   11,   11,   11, 0x08,
     205,   11,   11,   11, 0x08,
     224,   11,   11,   11, 0x08,
     242,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0slotPrint()\0slotClearPsth()\0"
    "slotTriggerPsth()\0c\0slotSetChannel(double)\0"
    "l\0slotSetPsthLength(double)\0b\0"
    "slotSetPsthBinw(double)\0t\0"
    "slotSetSpikeThres(double)\0slotSavePsth()\0"
    "slotSetNumTrials(double)\0slotStartPsthRec()\0"
    "slotSoundToggle()\0slotAveragePsth()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

const QMetaObject *MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotPrint(); break;
        case 1: slotClearPsth(); break;
        case 2: slotTriggerPsth(); break;
        case 3: slotSetChannel((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: slotSetPsthLength((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: slotSetPsthBinw((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: slotSetSpikeThres((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: slotSavePsth(); break;
        case 8: slotSetNumTrials((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: slotStartPsthRec(); break;
        case 10: slotSoundToggle(); break;
        case 11: slotAveragePsth(); break;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
