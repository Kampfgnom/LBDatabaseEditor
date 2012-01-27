TARGET = lbdatabase
TEMPLATE = lib
CONFIG += staticlib
QT += sql
DEFINES *= QT_USE_QSTRINGBUILDER
INCLUDEPATH += $$PWD/include
DESTDIR = $$PWD/../lib

HEADERS += \
    LBDatabase.h \
    column.h \
    database.h \
    row.h \
    table.h \
    entity.h \
    storage.h \
    context.h \
    entitytype.h \
    attribute.h \
    attributevalue.h \
    relation.h \
    property.h \
    propertyvalue.h \
    relationvalue.h \
    relationvalue_p.h \
    function.h \
    functionvalue.h \
    calculator.h \
    concreterelation.h \
    export/graphvizexporter.h \
    export/cppexporter.h \
    export/storagewriter.h \
    export/writer.h \
    export/contextwriter.h \
    export/entitytypewriter.h

SOURCES += \
    column.cpp \
    database.cpp \
    row.cpp \
    table.cpp \
    entity.cpp \
    storage.cpp \
    context.cpp \
    entitytype.cpp \
    attribute.cpp \
    attributevalue.cpp \
    relation.cpp \
    property.cpp \
    propertyvalue.cpp \
    relationvalue.cpp \
    function.cpp \
    functionvalue.cpp \
    calculator.cpp \
    export/graphvizexporter.cpp \
    export/cppexporter.cpp \
    export/storagewriter.cpp \
    export/writer.cpp \
    export/contextwriter.cpp \
    export/entitytypewriter.cpp

OTHER_FILES +=

