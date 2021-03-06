QT          += core sql widgets testlib
TARGET       = test
TEMPLATE     = app
INCLUDEPATH += ..
CONFIG      += c++11

SOURCES     += ../consolewriter.cpp \
               ../filewriter.cpp \
               ../guiwriter.cpp \
               ../loggedquery.cpp \
               ../logger.cpp \
               ../logmessage.cpp \
               ../preferences.cpp \
               ../severity.cpp \
               ../tracer.cpp \
               main.cpp \
               frameworktest.cpp \
               testpreferences.cpp

HEADERS     += ../consolewriter.h \
               ../enum_to_string.h \
               ../filewriter.h \
               ../guiwriter.h \
               ../loggedquery.h \
               ../logger.h \
               ../logmessage.h \
               ../logwriter.h \
               ../preferences.h \
               ../severity.h \
               ../sevexception.h \
               ../tracer.h \
               frameworktest.h \
               testpreferences.h



