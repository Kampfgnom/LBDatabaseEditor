#include "cppexporter.h"

#include "attribute.h"
#include "context.h"
#include "entitytype.h"
#include "storage.h"

#include <QFile>
#include <QTextStream>

#include <QDebug>

namespace LBDatabase {

class CppExporterPrivate
{
    CppExporterPrivate() : storage(0) {}

    void exportCpp() const;

    void exportStorage() const;
    void exportStorageHeader() const;
    void exportStorageSource() const;

    void exportContext(Context *context) const;
    void exportContextHeader(Context *context) const;
    void exportContextSource(Context *context) const;

    void writeNeededHeaders(EntityType *type, QString &source) const;

    void startHeader(const QString &name, QString &header) const;
    void endHeader(const QString &name, QString &header) const;

    void startNamespace(QString &file) const;
    void endNamespace(QString &file) const;

    void writeEntityTypeDeclaration(EntityType *type, QString &header) const;
    void writeEntityTypeImplementation(EntityType *type, QString &source) const;

    void exportEntityType(EntityType *type) const;
    void exportEntityTypeHeader(EntityType *type) const;
    void exportEntityTypeSource(EntityType *type) const;

    QString headerFileName(EntityType *entityType) const;
    QString classname(const QString &name) const;

    Storage *storage;
    QString directory;
    QString namespaceName;

    CppExporter * q_ptr;
    Q_DECLARE_PUBLIC(CppExporter)
};

void CppExporterPrivate::exportCpp() const
{
    if(!storage)
        return;

    exportStorage();

    foreach(Context *context, storage->contexts()) {
        exportContext(context);
    }
}

void CppExporterPrivate::exportStorage() const
{
    exportStorageHeader();
    exportStorageSource();
}

void CppExporterPrivate::exportStorageHeader() const
{
    QString storageClass = classname(storage->name().simplified().remove(' ').append(QLatin1String("Storage")));
    QString fileName = directory + storageClass.toLower() + QLatin1String(".h");
    QString header;

    startHeader(storageClass, header);
    startNamespace(header);

    foreach(Context *context, storage->contexts()) {
        QString contextName = classname(context->simplifiedName() + QLatin1String("Context"));
        header.append(QLatin1String("class ")+contextName+QLatin1String(";\n"));
    }

    header.append(QLatin1String("\nclass ")+storageClass+QLatin1String(" : public LBDatabase::Storage\n"
    "{\n"
    "public:\n\t")+
        storageClass+QLatin1String("(const QString &fileName, QObject *parent = 0);\n\n"));

    foreach(Context *context, storage->contexts()) {
        QString contextName = classname(context->simplifiedName() + QLatin1String("Context"));
        header.append(QLatin1String("\t")+contextName+QLatin1String(" *")+contextName.left(1).toLower()+contextName.mid(1)+QLatin1String("() const;\n"));
    }

    header.append(QLatin1String("};\n\n"));


    endNamespace(header);
    endHeader(storageClass, header);

    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return;

    QTextStream out(&file);
    out << header;
    file.close();
}

void CppExporterPrivate::exportStorageSource() const
{
    QString storageClass = classname(storage->name().simplified().remove(' ').append(QLatin1String("Storage")));
    QString fileName = directory + storageClass.toLower() + QLatin1String(".cpp");
    QString source;

    source.append(QLatin1String("#include \"") + storageClass.toLower() + QLatin1String(".h\"\n\n"));
    startNamespace(source);

    foreach(Context *context, storage->contexts()) {
        QString file = context->baseEntityType()->simplifiedName().toLower().append(".h");
        source.append(QLatin1String("#include \"") + file + QLatin1String("\"\n"));
    }

    source.append(QLatin1String("\n")+
            storageClass+QLatin1String("::")+storageClass+QLatin1String(
    "(const QString &fileName, QObject *parent) :\n"
        "\tStorage(fileName, parent)\n"
    "{\n"));

    foreach(Context *context, storage->contexts()) {
        QString contextName = classname(context->simplifiedName()) + QLatin1String("Context");
        source.append(QLatin1String("\tregisterContextType<") + contextName + QLatin1String(">();\n"));
    }
    source.append(QLatin1String("}\n\n"));

    foreach(Context *context, storage->contexts()) {
        QString contextName = classname(context->simplifiedName()) + QLatin1String("Context");
        source.append(
                    contextName+QLatin1String(" *")+storageClass+QLatin1String("::")+contextName.left(1).toLower()+contextName.mid(1)+QLatin1String("() const\n"
        "{\n"
            "\treturn static_cast<")+contextName+QLatin1String(" *>(context(")+contextName+QLatin1String("::Name));\n"
        "}\n\n"));
    }

    endNamespace(source);

    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return;

    QTextStream out(&file);
    out << source;
    file.close();
}

void CppExporterPrivate::exportContext(Context *context) const
{
    exportContextHeader(context);
    exportContextSource(context);

    foreach(EntityType *type, context->entityTypes()) {
        if(type != context->baseEntityType()) {
            exportEntityType(type);
        }
    }
}

void CppExporterPrivate::exportContextHeader(Context *context) const
{
    QString contextName = classname(context->simplifiedName() + QLatin1String("Context"));
    QString baseEntityTypeName = classname(context->baseEntityType()->simplifiedName());
    QString fileName = directory + headerFileName(context->baseEntityType());
    QString header;

    startHeader(baseEntityTypeName, header);
    startNamespace(header);

    writeEntityTypeDeclaration(context->baseEntityType(), header);

    header.append(QLatin1String("class ")+contextName+QLatin1String(" : public LBDatabase::Context\n"
                                                                    "{\n"
                                                                    "\tQ_OBJECT\n"
                                                                    "public:\n"
                                                                    "\tQ_INVOKABLE "));

    header.append(contextName + QLatin1String("(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);\n"));
    header.append(QLatin1String("\tstatic const QString Name;\n\n\t"));
    header.append(baseEntityTypeName+QLatin1String(" *")+baseEntityTypeName.left(1).toLower()+baseEntityTypeName.mid(1)+QLatin1String("(int id) const;\n"));
    header.append(QLatin1String("};\n\n"));

    endNamespace(header);
    endHeader(baseEntityTypeName, header);

    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return;

    QTextStream out(&file);
    out << header;
    file.close();
}

void CppExporterPrivate::exportContextSource(Context *context) const
{
    QString contextName = classname(context->simplifiedName() + QLatin1String("Context"));
    QString baseEntityTypeName = classname(context->baseEntityType()->simplifiedName());
    QString fileName = directory + baseEntityTypeName.toLower().append(QLatin1String(".cpp"));
    QString headerFile = headerFileName(context->baseEntityType());
    QString source;


    source.append(QLatin1String("#include \"") + headerFile + QLatin1String("\"\n\n"));

    writeNeededHeaders(context->baseEntityType(), source);

    startNamespace(source);

    foreach(EntityType *type, context->entityTypes()) {
        if(type != context->baseEntityType()) {
            QString file = headerFileName(type);
            source.append(QLatin1String("#include \"") + file + QLatin1String("\"\n"));
        }
    }

    source.append(QLatin1String("\nconst QString ") + contextName + QLatin1String("::Name(\"") + context->name() + QLatin1String("\");\n"));

    source.append(
            contextName+QLatin1String("::")+contextName+QLatin1String(
    "(LBDatabase::Row *row, LBDatabase::Storage *parent) :\n"
        "\tContext(row, parent)\n"
    "{\n"));

    foreach(EntityType *type, context->entityTypes()) {
        source.append(QLatin1String("\tregisterEntityClass<") + classname(type->simplifiedName()) + QLatin1String(">();\n"));
        //source.append(QLatin1String("\tregisterCalculatorClass<") + classname(type->simplifiedName()) + QLatin1String(",") + classname(type->simplifiedName()) + QLatin1String("Calculator>();\n\n"));
    }
    source.append(QLatin1String("}\n\n"));

    source.append(
    baseEntityTypeName+QLatin1String(" *")+contextName+QLatin1String("::")+baseEntityTypeName.left(1).toLower()+baseEntityTypeName.mid(1)+QLatin1String("(int id) const\n"
    "{\n"
        "\treturn static_cast<")+baseEntityTypeName+QLatin1String(" *>(entity(id));\n"
    "}\n\n"));

    writeEntityTypeImplementation(context->baseEntityType(), source);

    endNamespace(source);

    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return;

    QTextStream out(&file);
    out << source;
    file.close();
}

void CppExporterPrivate::writeNeededHeaders(EntityType *type, QString &source) const
{
    foreach(Attribute *attribute, type->nonInhertitedAttributes()) {
        if(attribute->type() == Attribute::Pixmap) {
            source.append(QLatin1String("#include <QPixmap>\n"));
        }
        else if(attribute->type() == Attribute::Icon) {
            source.append(QLatin1String("#include <QIcon>\n"));
        }
        else if(attribute->type() == Attribute::DateTime) {
            source.append(QLatin1String("#include <QDateTime>\n"));
        }
        else if(attribute->type() == Attribute::Time) {
            source.append(QLatin1String("#include <QTime>\n"));
        }
        else if(attribute->type() == Attribute::Color) {
            source.append(QLatin1String("#include <QColor>\n"));
        }
    }
    source.append(QLatin1String("\n"));
}

void CppExporterPrivate::startHeader(const QString &name, QString &header) const
{
    QString guard = namespaceName.toUpper();
    if(!guard.isEmpty())
        guard += QLatin1String("_");
    guard += name.toUpper() + QLatin1String("_H\n");

    header.append(QLatin1String("#ifndef "));
    header.append(guard);
    header.append(QLatin1String("#define "));
    header.append(guard);
    header.append(QLatin1String("\n#include <LBDatabase/LBDatabase.h>\n\n"));
}

void CppExporterPrivate::endHeader(const QString &name, QString &header) const
{
    QString guard = namespaceName.toUpper();
    if(!guard.isEmpty())
        guard += QLatin1String("_");
    guard += name.toUpper() + QLatin1String("_H\n");

    header.append(QLatin1String("#endif // ") + guard);
}

void CppExporterPrivate::startNamespace(QString &file) const
{
    if(!namespaceName.isEmpty())
        file.append(QLatin1String("namespace ")+namespaceName+QLatin1String(" {\n\n"));
}

void CppExporterPrivate::endNamespace(QString &file) const
{
    if(!namespaceName.isEmpty())
        file.append(QLatin1String("} // namespace ")+namespaceName+QLatin1String("\n\n"));
}

void CppExporterPrivate::writeEntityTypeDeclaration(EntityType *type, QString &header) const
{
    QString typeClass = classname(type->simplifiedName());
    QString baseClass = "LBDatabase::Entity";
    if(type->parentEntityType()) {
        baseClass = classname(type->parentEntityType()->simplifiedName());
        header.append(QLatin1String("#include \"") + baseClass.toLower() + QLatin1String(".h\"\n\n"));
    }

    header.append(QLatin1String("namespace ")+typeClass+QLatin1String("Properties {\n"));
    foreach(Attribute *attribute, type->nonInhertitedAttributes()) {
        QString attributeName = attribute->name();
        header.append(QLatin1String("const QString ")+ attributeName.left(1).toUpper() + attributeName.mid(1) + QLatin1String("Attribute(\"") +
                      attributeName+QLatin1String("\");\n"));
    }
    foreach(Relation *relation, type->nonInhertitedRelations()) {
        QString relationName = relation->name();
        header.append(QLatin1String("const QString ")+ relationName.left(1).toUpper() + relationName.mid(1) + QLatin1String("Relation(\"") +
                      relationName+QLatin1String("\");\n"));
    }

    header.append(QLatin1String("}\n\n"));

    foreach(Relation *relation, type->nonInhertitedRelations()) {
        if(relation->entityTypeLeft() == type) {
            header.append(QLatin1String("class ") + classname(relation->entityTypeRight()->simplifiedName()) + QLatin1String(";\n"));
        }
        else {
            header.append(QLatin1String("class ") + classname(relation->entityTypeLeft()->simplifiedName()) + QLatin1String(";\n"));
        }
    }

    header.append(QLatin1String("\nclass ")+typeClass+QLatin1String(" : public ")+baseClass+QLatin1String("\n"
    "{\n"
        "\tQ_OBJECT\n"
    "public:\n"
        "\tQ_INVOKABLE ")+typeClass+QLatin1String("(::LBDatabase::Row *row, ::LBDatabase::Context *context);\n"
        "\tstatic const QString Name;\n\n"));

    foreach(Attribute *attribute, type->nonInhertitedAttributes()) {
        QString attributeType = attribute->qtType();
        QString attributeName = attribute->name();
        header.append(QLatin1String("\t") + attributeType + QLatin1String(" ") +
                      attributeName.left(1).toLower() + attributeName.mid(1) + QLatin1String("() const;\n"));
    }

//        QString name() const;
//        QDateTime date() const;
//        QString comment() const;
//        Entity *site() const;

//        QList<Player *> players() const;
//        QList<Player *> playersByPosition() const;
//        virtual QList<Player *> playersByPlacement() const;
    header.append(QLatin1String("};\n\n"));
}

void CppExporterPrivate::writeEntityTypeImplementation(EntityType *type, QString &source) const
{
    QString typeClass = classname(type->simplifiedName());
    QString baseClass("Entity");
    if(type->parentEntityType())
        baseClass = classname(type->parentEntityType()->simplifiedName());

    source.append(QLatin1String("const QString ") + typeClass + QLatin1String("::Name(\"") + type->name() + QLatin1String("\");\n\n"));

     source.append(
             typeClass+QLatin1String("::")+typeClass+QLatin1String(
     "(LBDatabase::Row *row, LBDatabase::Context *context) :\n"
         "\t") + baseClass + QLatin1String("(row, context)\n"
     "{\n"
     "}\n\n"));

     foreach(Attribute *attribute, type->nonInhertitedAttributes()) {
         QString attributeType = attribute->qtType();
         QString attributeName = attribute->name();
         source.append(attributeType+QLatin1String(" ")+typeClass+QLatin1String("::")+attributeName.left(1).toLower()+attributeName.mid(1)+
                       QLatin1String("() const\n"
                                     "{\n"
                                     "\treturn value(")+typeClass+
                       QLatin1String("Properties::")+attributeName.left(1).toUpper() + attributeName.mid(1) + QLatin1String("Attribute).value<") +
                       attributeType+QLatin1String(">();\n"
                                                   "}\n\n"));
     }
}

void CppExporterPrivate::exportEntityType(EntityType *type) const
{
    exportEntityTypeHeader(type);
    exportEntityTypeSource(type);
}

void CppExporterPrivate::exportEntityTypeHeader(EntityType *type) const
{
    QString typeClass = classname(type->simplifiedName());
    QString fileName = directory + headerFileName(type);
    QString header;

    startHeader(typeClass, header);
    startNamespace(header);

    writeEntityTypeDeclaration(type, header);

    endNamespace(header);
    endHeader(typeClass, header);

    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return;

    QTextStream out(&file);
    out << header;
    file.close();
}

void CppExporterPrivate::exportEntityTypeSource(EntityType *type) const
{
    QString typeClass = classname(type->simplifiedName());
    QString fileName = directory + typeClass.toLower().append(QLatin1String(".cpp"));
    QString headerFile = headerFileName(type);
    QString source;

    source.append(QLatin1String("#include \"") + headerFile + QLatin1String("\"\n\n"));

    writeNeededHeaders(type, source);
    source.append(QLatin1String("\n"));
    startNamespace(source);

    writeEntityTypeImplementation(type, source);

    endNamespace(source);

    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return;

    QTextStream out(&file);
    out << source;
    file.close();
}

QString CppExporterPrivate::headerFileName(EntityType *entityType) const
{
     return entityType->simplifiedName().toLower().append(QLatin1String(".h"));
}

QString CppExporterPrivate::classname(const QString &name) const
{
    return name.left(1).toUpper()+name.mid(1);
}


CppExporter::CppExporter(QObject *parent) :
    QObject(parent),
    d_ptr(new CppExporterPrivate)
{
    Q_D(CppExporter);
    d->q_ptr = this;
}

CppExporter::~CppExporter()
{
}

void CppExporter::setStorage(Storage *storage)
{
    Q_D(CppExporter);
    d->storage = storage;
}

void CppExporter::setDirectory(const QString &directory)
{
    Q_D(CppExporter);
    if(!directory.endsWith('/'))
        d->directory = directory + '/';
    else
        d->directory = directory;
}

void CppExporter::setNamespaceName(const QString &namespaceName)
{
    Q_D(CppExporter);
    d->namespaceName = namespaceName;
}

void CppExporter::exportCpp() const
{
    Q_D(const CppExporter);
    d->exportCpp();
}


} // namespace LBDatabase
