QT       += core gui sql

TARGET = LBDatabaseTest
TEMPLATE = app
DESTDIR     = $PWD/../

SOURCES += main.cpp\
    database/company.cpp #\
 #   database/employee.cpp \
  #  database/manager.cpp \
   # database/worker.cpp

HEADERS  += \
   database/company.h #\
  #  database/employee.h \
   # database/manager.h \
    #database/worker.h

LIBS += -L$$PWD/../lib/LBDatabase/lib/ -llbdatabase
INCLUDEPATH += $$PWD/../lib/LBDatabase/include
PRE_TARGETDEPS += $$PWD/../lib/LBDatabase/lib/liblbdatabase.a

LIBS += -L$$PWD/../lib/LBGui/lib/ -llbgui
INCLUDEPATH += $$PWD/../lib/LBGui/include
PRE_TARGETDEPS += $$PWD/../lib/LBGui/lib/liblbgui.a
