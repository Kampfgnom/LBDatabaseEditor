QT       += core gui sql

TARGET = LBDatabaseTest
TEMPLATE = app
DESTDIR     = $PWD/../

SOURCES += main.cpp\
    tablewidget.cpp \
    edittabledialog.cpp \
    databasewidget.cpp \
    databaseeditorsidebar.cpp \
    databaseeditorcontroller.cpp \
    databaseeditoractions.cpp \
    databaseeditor.cpp \
    createtabledialog.cpp \
    editcolumnwidget.cpp \
    tableview.cpp \
    storagewidget.cpp \
    contextwidget.cpp \
    contextview.cpp \
    addentitytypedialog.cpp \
    entitytypecombobox.cpp \
    createcontextdialog.cpp

HEADERS  += \
    tablewidget.h \
    edittabledialog.h \
    databasewidget.h \
    databaseeditorsidebar.h \
    databaseeditorcontroller.h \
    databaseeditoractions.h \
    databaseeditor.h \
    createtabledialog.h \
    editcolumnwidget.h \
    tableview.h \
    storagewidget.h \
    contextwidget.h \
    contextview.h \
    addentitytypedialog.h \
    entitytypecombobox.h \
    createcontextdialog.h

LIBS += -L$$PWD/../lib/LBDatabase/lib/ -llbdatabase
INCLUDEPATH += $$PWD/../lib/LBDatabase/include
PRE_TARGETDEPS += $$PWD/../lib/LBDatabase/lib/liblbdatabase.a

LIBS += -L$$PWD/../lib/LBGui/lib/ -llbgui
INCLUDEPATH += $$PWD/../lib/LBGui/include
PRE_TARGETDEPS += $$PWD/../lib/LBGui/lib/liblbgui.a

FORMS += \
    createtabledialog.ui \
    addentitytypedialog.ui \
    createcontextdialog.ui

RESOURCES += \
    resources/databaseeditor/databaseeditor.qrc








