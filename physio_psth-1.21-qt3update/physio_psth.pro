TARGET       = physio_psth
TEMPLATE     = app
CONFIG      += qt warn_on debug thread
MOC_DIR      = moc
OBJECTS_DIR  = obj
INCLUDEPATH  += $(QTDIR) /usr/local/src/qwt/include /usr/local/include /usr/include/qwt
DEPENDPATH   = 

LIBS += -L/usr/local/lib -L/usr/local/src/qwt/lib -lqwt -lcomedi

TMAKE_CXXFLAGS += -fno-exceptions 

SOURCES = physio_psth.cpp psthplot.cpp dataplot.cpp main.cpp
HEADERS = physio_psth.h psthplot.h dataplot.h

