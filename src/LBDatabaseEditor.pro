QT       += core gui sql

TARGET = LBDatabaseTest
TEMPLATE = app

DESTDIR = $$OUT_PWD/../
OBJECTS_DIR = $$OUT_PWD/../build/

INCLUDEPATH += $$PWD/../lib/LBDatabase/include
INCLUDEPATH += $$PWD/../lib/LBGui/include

# add a build command
defineReplace( nc  ) {
    return( $$escape_expand(\\n\\t)$$1    )
}
# add a silent build command
defineReplace( snc ) {
    return( $$escape_expand(\\n\\t)"@"$$1 )
}
# add end of line
defineReplace( nl  ) {
    return( $$escape_expand(\\n)         )
}

macx {
    LIBS += -L$$OUT_PWD/../lib/LBDatabase/
    LIBS += -llbdatabase

    LIBS += -L$$OUT_PWD/../lib/LBGui/
    LIBS += -llbgui

    copyFrameworks.target = frameworks
    copyFrameworks.commands += rm -Rf $$DESTDIR/LBDatabaseTest.app/Contents/Frameworks/
    copyFrameworks.commands += $$snc( mkdir -p $$DESTDIR/LBDatabaseTest.app/Contents/Frameworks/ )
    copyFrameworks.commands += $$snc( cp -R $$PWD/../lib/LBDatabase/frameworks/* $$DESTDIR/LBDatabaseTest.app/Contents/Frameworks/ )

    copyDylibs.target = dylibs
    copyDylibs.commands += mkdir -p $$DESTDIR/LBDatabaseTest.app/Contents/MacOS/
    copyDylibs.commands += $$snc(   cp $$DESTDIR/lib/LBDatabase/liblbdatabase.1.0.0.dylib $$DESTDIR/LBDatabaseTest.app/Contents/MacOS/ )
    copyDylibs.commands += $$snc(   cp $$DESTDIR/lib/LBDatabase/liblbdatabase.1.dylib $$DESTDIR/LBDatabaseTest.app/Contents/MacOS/ )
    copyDylibs.commands += $$snc(   cp $$DESTDIR/lib/LBGui/liblbgui.1.0.0.dylib $$DESTDIR/LBDatabaseTest.app/Contents/MacOS/ )
    copyDylibs.commands += $$snc(   cp $$DESTDIR/lib/LBGui/liblbgui.1.dylib $$DESTDIR/LBDatabaseTest.app/Contents/MacOS/ )

    QMAKE_POST_LINK = install_name_tool -id @executable_path/liblbdatabase.1.dylib $$DESTDIR/LBDatabaseTest.app/Contents/MacOS/liblbdatabase.1.dylib &&
    QMAKE_POST_LINK += install_name_tool -id @executable_path/liblbgui.1.dylib $$DESTDIR/LBDatabaseTest.app/Contents/MacOS/liblbgui.1.dylib &&
    QMAKE_POST_LINK += install_name_tool -change liblbdatabase.1.dylib @executable_path/liblbdatabase.1.dylib $$DESTDIR/LBDatabaseTest.app/Contents/MacOS/LBDatabaseTest &&
    QMAKE_POST_LINK += install_name_tool -change liblbgui.1.dylib @executable_path/liblbgui.1.dylib $$DESTDIR/LBDatabaseTest.app/Contents/MacOS/LBDatabaseTest

    QMAKE_EXTRA_TARGETS += copyFrameworks copyDylibs
    PRE_TARGETDEPS += frameworks dylibs
}

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

FORMS += \
    createtabledialog.ui \
    addentitytypedialog.ui \
    createcontextdialog.ui \
    editentitytypesdialog.ui \
    editattributewidget.ui \
    editrelationwidget.ui

RESOURCES += \
    resources/databaseeditor/databaseeditor.qrc



















