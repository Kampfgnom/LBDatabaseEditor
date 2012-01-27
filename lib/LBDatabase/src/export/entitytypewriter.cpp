#include "entitytypewriter.h"

#include "calculatorwriter.h"

#include "../attribute.h"
#include "../entitytype.h"

#include <QStringList>

namespace LBDatabase {

EntityTypeWriter::EntityTypeWriter(const CppExporter *exporter) :
    Writer(exporter)
{
}

void EntityTypeWriter::setEntityType(EntityType *type)
{
    m_entityType = type;
    m_classname = makeClassname(m_entityType->name());
}

void EntityTypeWriter::write() const
{
    exportHeader();
    exportSource();

    CalculatorWriter writer(m_exporter);
    writer.setEntityType(m_entityType);
    writer.write();
}

void EntityTypeWriter::writeNeededHeaders(QString &header) const
{
    QString type;
    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->type() == Attribute::Pixmap) {
            header.append(QLatin1String("#include <QPixmap>\n"));
        }
        else if(attribute->type() == Attribute::Icon) {
            header.append(QLatin1String("#include <QIcon>\n"));
        }
        else if(attribute->type() == Attribute::DateTime) {
            header.append(QLatin1String("#include <QDateTime>\n"));
        }
        else if(attribute->type() == Attribute::Time) {
            header.append(QLatin1String("#include <QTime>\n"));
        }
        else if(attribute->type() == Attribute::Color) {
            header.append(QLatin1String("#include <QColor>\n"));
        }
    }
    header.append(QLatin1String("\n"));
}

void EntityTypeWriter::writePropertyNameStrings(QString &header) const
{
    writeNamespaceBegin(m_classname+QLatin1String("Properties"), header);

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        QString attributeName = attribute->name();
        header.append(QLatin1String("const QString ")+ makeClassname(attributeName) + QLatin1String("Attribute(\"") +
                      attributeName+QLatin1String("\");\n"));
    }

    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        header.append(QLatin1String("const QString ")+ makeRelationName(relation) + QLatin1String("Relation(\"") +
                      relation->name()+QLatin1String("\");\n"));
    }

    writeNamespaceEnd(m_classname+QLatin1String("Properties"), header);
}

void EntityTypeWriter::writeForwardDeclarations(QString &header) const
{
    QStringList declaredTypes;
    QString name;
    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(relation->entityTypeLeft() == m_entityType) {
            name = makeClassname(relation->entityTypeRight()->name());
        }
        else {
            name = makeClassname(relation->entityTypeLeft()->name());
        }

        if(!declaredTypes.contains(name)) {
            declaredTypes << name;
            header.append(QLatin1String("class ") + name + QLatin1String(";\n"));
        }
    }
}

void EntityTypeWriter::writeDeclaration(QString &header) const
{
    QString baseClass = "LBDatabase::Entity";
    if(m_entityType->parentEntityType()) {
        baseClass = makeClassname(m_entityType->parentEntityType()->name());
        writeInclude(baseClass,header);
    }

    header.append(QLatin1String("\n"));

    writePropertyNameStrings(header);
    writeForwardDeclarations(header);

    header.append(QLatin1String("\nclass ")+m_classname+QLatin1String(" : public ")+baseClass+QLatin1String("\n"
    "{\n"
        "\tQ_OBJECT\n"
    "public:\n"
        "\tQ_INVOKABLE ")+m_classname+QLatin1String("(::LBDatabase::Row *row, ::LBDatabase::Context *context);\n"
        "\tstatic const QString Name;\n\n"));

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        writeAttributeDeclaration(attribute, header);
    }

    header.append(QLatin1String("\n"));

    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        writeRelationDeclaration(relation, header);
    }

    header.append(QLatin1String("};\n\n"));
}

void EntityTypeWriter::writeImplementation(QString &source) const
{
    QString typeClass = makeClassname(m_entityType->name());
    QString baseClass("Entity");
    if(m_entityType->parentEntityType())
        baseClass = makeClassname(m_entityType->parentEntityType()->name());

    source.append(QLatin1String("const QString ") + typeClass + QLatin1String("::Name(\"") + m_entityType->name() + QLatin1String("\");\n\n"));

    source.append(
         typeClass+QLatin1String("::")+typeClass+QLatin1String(
    "(LBDatabase::Row *row, LBDatabase::Context *context) :\n"
        "\t") + baseClass + QLatin1String("(row, context)\n"
    "{\n"
    "}\n\n"));

     foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
         writeAttributeImplementation(attribute, source);
     }

     foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
         writeRelationImplementation(relation, source);
     }
}

void EntityTypeWriter::writeAttributeDeclaration(Attribute *attribute, QString &header) const
{
    header.append(QLatin1String("\t") + attribute->qtType() + QLatin1String(" ") +
                  makeMethodName(attribute->name()) + QLatin1String("() const;\n"));
}

void EntityTypeWriter::writeAttributeImplementation(Attribute *attribute, QString &source) const
{
    QString attributeType = attribute->qtType();
    QString attributeName = attribute->name();
    source.append(attributeType+QLatin1String(" ")+m_classname+QLatin1String("::")+attributeName.left(1).toLower()+attributeName.mid(1)+
                  QLatin1String("() const\n"
                                "{\n"
                                "\treturn value(")+m_classname+
                  QLatin1String("Properties::")+attributeName.left(1).toUpper() + attributeName.mid(1) + QLatin1String("Attribute).value<") +
                  attributeType+QLatin1String(">();\n"
                                              "}\n\n"));
}

void EntityTypeWriter::writeRelationDeclaration(Relation *relation, QString &header) const
{
    QString relationName = makeRelationName(relation);
    QString entityType = makeRelationType(relation);

    if(relation->cardinality() == Relation::OneToOne ||
            (relation->cardinality() == Relation::OneToMany &&
             relation->entityTypeRight() == m_entityType)) {
        header.append(QLatin1String("\t") + entityType + QLatin1String(" *") +
                  makeMethodName(relationName) + QLatin1String("() const;\n"));
    }
    else if(relation->cardinality() == Relation::ManyToMany ||
            (relation->cardinality() == Relation::OneToMany &&
             relation->entityTypeLeft() == m_entityType)) {
        header.append(QLatin1String("\tQList<") + entityType + QLatin1String(" *> ") +
                  makeMethodName(relationName) + QLatin1String("() const;\n"));
    }
}

void EntityTypeWriter::writeRelationImplementation(Relation *relation, QString &source) const
{
    QString relationName = makeRelationName(relation);
    QString entityType = makeRelationType(relation);

    if(relation->cardinality() == Relation::OneToOne ||
            (relation->cardinality() == Relation::OneToMany &&
             relation->entityTypeRight() == m_entityType)) {
         source.append(
         QLatin1String("") + entityType + QLatin1String(" *")+
                     m_classname+QLatin1String("::")+makeMethodName(relationName)+QLatin1String("() const\n"
              "{\n"
                    "\treturn relation<")+entityType+QLatin1String(">(")+m_classname+
                                QLatin1String("Properties::")+relationName+QLatin1String("Relation)->firstEntity();\n"
              "}\n\n"));
    }
    else if(relation->cardinality() == Relation::ManyToMany ||
            (relation->cardinality() == Relation::OneToMany &&
             relation->entityTypeLeft() == m_entityType)) {
         source.append(
         QLatin1String("QList<") + entityType + QLatin1String(" *> ")+
                     m_classname+QLatin1String("::")+makeMethodName(relationName)+QLatin1String("() const\n"
              "{\n"
                    "\treturn relation<")+entityType+QLatin1String(">(")+m_classname+
                                QLatin1String("Properties::")+relationName+QLatin1String("Relation)->entities();\n"
              "}\n\n"));
    }
}

void EntityTypeWriter::exportHeader() const
{
    QString header;

    startHeader(m_classname, header);
    startNamespace(header);

    writeDeclaration(header);

    endNamespace(header);
    endHeader(m_classname, header);

    writeToFile(makeHeaderFilename(m_classname), header);
}

void EntityTypeWriter::exportSource() const
{
    QString source;

    writeInclude(m_classname, source);

    writeNeededHeaders(source);

    source.append(QLatin1String("\n"));

    startNamespace(source);

    writeImplementation(source);

    endNamespace(source);

    writeToFile(makeSourceFilename(m_classname), source);
}

QString EntityTypeWriter::makeRelationName(Relation *relation) const
{
    if(relation->entityTypeLeft() == m_entityType) {
        return makeClassname(relation->displayNameLeft());
    }
    else {
        return makeClassname(relation->displayNameRight());
    }
}

QString EntityTypeWriter::makeRelationType(Relation *relation) const
{
    if(relation->entityTypeLeft() == m_entityType) {
        return makeClassname(relation->entityTypeRight()->name());
    }
    else {
        return makeClassname(relation->entityTypeLeft()->name());
    }
}

} // namespace LBDatabase
