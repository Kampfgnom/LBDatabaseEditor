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
    createcontextdialog.cpp \
    editentitytypesdialog.cpp \
    editattributewidget.cpp \
    editrelationwidget.cpp \
    propertycombobox.cpp \
    model/skatround.cpp \
    model/skatofflinegame.cpp \
    model/skatlivegame.cpp \
    model/schmeisserei.cpp \
    model/rule.cpp \
    model/round.cpp \
    model/projectstatsstorage.cpp \
    model/prognoseofflinegame.cpp \
    model/pokerofflinegame.cpp \
    model/playercalculator.cpp \
    model/player.cpp \
    model/placecalculator.cpp \
    model/place.cpp \
    model/offlinegame.cpp \
    model/livegamecalculator.cpp \
    model/livegame.cpp \
    model/livedrink.cpp \
    model/heartsofflinegame.cpp \
    model/gamecalculator.cpp \
    model/game.cpp \
    model/drinkcalculator.cpp \
    model/drink.cpp \
    model/doppelkopfround.cpp \
    model/doppelkopfofflinegame.cpp \
    model/doppelkopflivegame.cpp \
    model/category.cpp

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
    createcontextdialog.h \
    editentitytypesdialog.h \
    editattributewidget.h \
    editrelationwidget.h \
    propertycombobox.h \
    model/skatround.h \
    model/skatofflinegame.h \
    model/skatlivegame.h \
    model/schmeisserei.h \
    model/rule.h \
    model/round.h \
    model/projectstatsstorage.h \
    model/prognoseofflinegame.h \
    model/pokerofflinegame.h \
    model/playercalculator.h \
    model/player.h \
    model/placecalculator.h \
    model/place.h \
    model/offlinegame.h \
    model/livegamecalculator.h \
    model/livegame.h \
    model/livedrink.h \
    model/heartsofflinegame.h \
    model/gamecalculator.h \
    model/game.h \
    model/drinkcalculator.h \
    model/drink.h \
    model/doppelkopfround.h \
    model/doppelkopfofflinegame.h \
    model/doppelkopflivegame.h \
    model/category.h

LIBS += -L$$PWD/../lib/LBDatabase/lib/ -llbdatabase
INCLUDEPATH += $$PWD/../lib/LBDatabase/include
PRE_TARGETDEPS += $$PWD/../lib/LBDatabase/lib/liblbdatabase.a

LIBS += -L$$PWD/../lib/LBGui/lib/ -llbgui
INCLUDEPATH += $$PWD/../lib/LBGui/include
PRE_TARGETDEPS += $$PWD/../lib/LBGui/lib/liblbgui.a

FORMS += \
    createtabledialog.ui \
    addentitytypedialog.ui \
    createcontextdialog.ui \
    editentitytypesdialog.ui \
    editattributewidget.ui \
    editrelationwidget.ui

RESOURCES += \
    resources/databaseeditor/databaseeditor.qrc



















