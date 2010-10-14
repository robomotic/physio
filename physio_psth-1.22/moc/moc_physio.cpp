/****************************************************************************
** MainWindow meta object code from reading C++ file 'physio.h'
**
** Created: Wed Feb 23 12:44:48 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.3   edited Aug 5 16:40 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../physio.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MainWindow::className() const
{
    return "MainWindow";
}

QMetaObject *MainWindow::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MainWindow( "MainWindow", &MainWindow::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MainWindow::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainWindow", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MainWindow::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainWindow", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MainWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotPrint", 0, 0 };
    static const QUMethod slot_1 = {"slotClearPsth", 0, 0 };
    static const QUMethod slot_2 = {"slotTriggerPsth", 0, 0 };
    static const QUParameter param_slot_3[] = {
	{ "c", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"slotSetChannel", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "l", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"slotSetPsthLength", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "b", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"slotSetPsthBinw", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "t", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"slotSetSpikeThres", 1, param_slot_6 };
    static const QUMethod slot_7 = {"slotSavePsth", 0, 0 };
    static const QUParameter param_slot_8[] = {
	{ 0, &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"slotSetNumTrials", 1, param_slot_8 };
    static const QUMethod slot_9 = {"slotStartPsthRec", 0, 0 };
    static const QUMethod slot_10 = {"slotSoundToggle", 0, 0 };
    static const QUMethod slot_11 = {"slotAveragePsth", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotPrint()", &slot_0, QMetaData::Private },
	{ "slotClearPsth()", &slot_1, QMetaData::Private },
	{ "slotTriggerPsth()", &slot_2, QMetaData::Private },
	{ "slotSetChannel(double)", &slot_3, QMetaData::Private },
	{ "slotSetPsthLength(double)", &slot_4, QMetaData::Private },
	{ "slotSetPsthBinw(double)", &slot_5, QMetaData::Private },
	{ "slotSetSpikeThres(double)", &slot_6, QMetaData::Private },
	{ "slotSavePsth()", &slot_7, QMetaData::Private },
	{ "slotSetNumTrials(double)", &slot_8, QMetaData::Private },
	{ "slotStartPsthRec()", &slot_9, QMetaData::Private },
	{ "slotSoundToggle()", &slot_10, QMetaData::Private },
	{ "slotAveragePsth()", &slot_11, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"MainWindow", parentObject,
	slot_tbl, 12,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MainWindow.setMetaObject( metaObj );
    return metaObj;
}

void* MainWindow::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MainWindow" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool MainWindow::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotPrint(); break;
    case 1: slotClearPsth(); break;
    case 2: slotTriggerPsth(); break;
    case 3: slotSetChannel((double)static_QUType_double.get(_o+1)); break;
    case 4: slotSetPsthLength((double)static_QUType_double.get(_o+1)); break;
    case 5: slotSetPsthBinw((double)static_QUType_double.get(_o+1)); break;
    case 6: slotSetSpikeThres((double)static_QUType_double.get(_o+1)); break;
    case 7: slotSavePsth(); break;
    case 8: slotSetNumTrials((double)static_QUType_double.get(_o+1)); break;
    case 9: slotStartPsthRec(); break;
    case 10: slotSoundToggle(); break;
    case 11: slotAveragePsth(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MainWindow::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MainWindow::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool MainWindow::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
