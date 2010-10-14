TARGET = physio_psth
TEMPLATE = app
CONFIG += qt \
    warn_on \
    debug \
    thread
MOC_DIR = moc
OBJECTS_DIR = obj
INCLUDEPATH += $(QTDIR) \
    /usr/include/qwt-qt4/ \
    /usr/local/include
DEPENDPATH = 
LIBS += -L/usr/local/lib \
    -lqwt-qt4 \
    -lcomedi
TMAKE_CXXFLAGS += -fno-exceptions
SOURCES = psthplot.cpp \
    dataplot.cpp \
    main.cpp \
    physio_psth.cpp
HEADERS = physio_psth.h \
    psthplot.h \
    dataplot.h

# The following line was inserted by qt3to4
QT += qt3support
