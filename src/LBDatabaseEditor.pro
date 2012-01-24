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
    model2/skatround.cpp \
    model2/skatofflinegame.cpp \
    model2/skatlivegame.cpp \
    model2/schmeisserei.cpp \
    model2/rule.cpp \
    model2/round.cpp \
    model2/projectstatsstorage.cpp \
    model2/prognoseofflinegame.cpp \
    model2/pokerofflinegame.cpp \
    model2/player.cpp \
    model2/place.cpp \
    model2/offlinegameinformation.cpp \
    model2/offlinegame.cpp \
    model2/livegamedrink.cpp \
    model2/livegame.cpp \
    model2/heartsofflinegame.cpp \
    model2/game.cpp \
    model2/drink.cpp \
    model2/doppelkopfround.cpp \
    model2/doppelkopfofflinegame.cpp \
    model2/doppelkopflivegame.cpp \
    model2/dokoofflinegamebuddy.cpp \
    model2/categoryassignment.cpp \
    model2/category.cpp # model/game.cpp \
#    model/psstorage.cpp \
#    model/gamecalculator.cpp \
#    model/livegame.cpp \
#    model/livegamecalculator.cpp \
#    model/player.cpp \
#    model/round.cpp

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
    model2/skatround.h \
    model2/skatofflinegame.h \
    model2/skatlivegame.h \
    model2/schmeisserei.h \
    model2/rule.h \
    model2/round.h \
    model2/projectstatsstorage.h \
    model2/prognoseofflinegame.h \
    model2/pokerofflinegame.h \
    model2/player.h \
    model2/place.h \
    model2/offlinegameinformation.h \
    model2/offlinegame.h \
    model2/livegamedrink.h \
    model2/livegame.h \
    model2/heartsofflinegame.h \
    model2/game.h \
    model2/drink.h \
    model2/doppelkopfround.h \
    model2/doppelkopfofflinegame.h \
    model2/doppelkopflivegame.h \
    model2/dokoofflinegamebuddy.h \
    model2/categoryassignment.h \
    model2/category.h # model/game.h
#    model/psstorage.h \
#    model/gamecalculator.h \
#    model/livegame.h \
#    model/livegamecalculator.h \
#    model/player.h \
#    model/round.h

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








