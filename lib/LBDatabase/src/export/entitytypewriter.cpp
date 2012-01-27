#include "entitytypewriter.h"

#include "attribute.h"
#include "entitytype.h"

namespace LBDatabase {

EntityTypeWriter::EntityTypeWriter(const CppExporter *exporter) :
    Writer(exporter)
{
}

void EntityTypeWriter::setEntityType(EntityType *type)
{
    m_entityType = type;
}

void EntityTypeWriter::write() const
{

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
    QString typeClass = makeClassname(m_entityType->name());
    writeNamespaceBegin(typeClass+QLatin1String("Properties"), header);

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        QString attributeName = attribute->name();
        header.append(QLatin1String("const QString ")+ makeClassname(attributeName) + QLatin1String("Attribute(\"") +
                      attributeName+QLatin1String("\");\n"));
    }

    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        header.append(QLatin1String("const QString ")+ makeRelationName(relation) + QLatin1String("Relation(\"") +
                      relation->name()+QLatin1String("\");\n"));
    }

    writeNamespaceEnd(typeClass+QLatin1String("Properties"), header);
}

void EntityTypeWriter::writeForwardDeclarations(QString &header) const
{
    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(relation->entityTypeLeft() == m_entityType) {
            header.append(QLatin1String("class ") + makeClassname(relation->entityTypeRight()->name()) + QLatin1String(";\n"));
        }
        else {
            header.append(QLatin1String("class ") + makeClassname(relation->entityTypeLeft()->name()) + QLatin1String(";\n"));
        }
    }
}

void EntityTypeWriter::writeDeclaration(QString &header) const
{
    QString typeClass = makeClassname(m_entityType->name());
    QString baseClass = "LBDatabase::Entity";
    if(m_entityType->parentEntityType()) {
        baseClass = makeClassname(m_entityType->parentEntityType()->name());
        writeInclude(baseClass,header);
    }

    writePropertyNameStrings(header);
    writeForwardDeclarations(header);

    header.append(QLatin1String("\nclass ")+typeClass+QLatin1String(" : public ")+baseClass+QLatin1String("\n"
    "{\n"
        "\tQ_OBJECT\n"
    "public:\n"
        "\tQ_INVOKABLE ")+typeClass+QLatin1String("(::LBDatabase::Row *row, ::LBDatabase::Context *context);\n"
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

     foreach(Attribute *attribute, type->nonInhertitedAttributes()) {
         writeAttributeImplementation(attribute, source);
     }

     foreach(Relation *relation, type->nonInhertitedRelations()) {
         QString relationName;
         QString entityType;
         if(relation->entityTypeLeft() == type) {
             relationName = relation->displayNameLeft().trimmed().remove(' ');
             entityType = classname(relation->entityTypeRight()->simplifiedName());
         }
         else {
             relationName = relation->displayNameRight().trimmed().remove(' ').remove('.');
             entityType = classname(relation->entityTypeLeft()->simplifiedName());
         }
         relationName = relationName.left(1).toLower()+relationName.mid(1);
         if(relationName.contains(QRegExp("^\\d"))) {
             relationName.prepend("_");
         }

         if(relation->cardinality() == Relation::OneToOne) {
             source.append(
                         QLatin1String("") + entityType + QLatin1String(" *")+
                                     typeClass+QLatin1String("::")+relationName + QLatin1String("() const\n"
                              "{\n"
                                    "\treturn value<")+entityType+QLatin1String(">(")+typeClass+
                                                QLatin1String("Properties::")+relationName.left(1).toUpper() + relationName.mid(1) + QLatin1String("Attribute)->firstEntity();\n"
                              "}\n\n"));
         }
         else if(relation->cardinality() == Relation::OneToMany) {
             if(relation->entityTypeLeft() == type) {
                 source.append(
                 QLatin1String("QList<") + entityType + QLatin1String(" *> ")+
                             typeClass+QLatin1String("::")+relationName + QLatin1String("() const\n"
                      "{\n"
                            "\treturn value<")+entityType+QLatin1String(">(")+typeClass+
                                        QLatin1String("Properties::")+relationName.left(1).toUpper() + relationName.mid(1) + QLatin1String("Attribute)->entities();\n"
                      "}\n\n"));
             }
             else {
                 source.append(
                 QLatin1String("") + entityType + QLatin1String(" *")+
                             typeClass+QLatin1String("::")+relationName + QLatin1String("() const\n"
                      "{\n"
                            "\treturn value<")+entityType+QLatin1String(">(")+typeClass+
                                        QLatin1String("Properties::")+relationName.left(1).toUpper() + relationName.mid(1) + QLatin1String("Attribute)->firstEntity();\n"
                      "}\n\n"));
             }
         }
         else {
             if(relation->cardinality() == Relation::ManyToMany) {
                 source.append(
                 QLatin1String("QList<") + entityType + QLatin1String(" *> ")+
                             typeClass+QLatin1String("::")+relationName + QLatin1String("() const\n"
                      "{\n"
                            "\treturn value<")+entityType+QLatin1String(">(")+typeClass+
                                        QLatin1String("Properties::")+relationName.left(1).toUpper() + relationName.mid(1) + QLatin1String("Attribute)->entities();\n"
                      "}\n\n"));
             }
         }
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
    source.append(attributeType+QLatin1String(" ")+typeClass+QLatin1String("::")+attributeName.left(1).toLower()+attributeName.mid(1)+
                  QLatin1String("() const\n"
                                "{\n"
                                "\treturn value(")+typeClass+
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
                  relationName + QLatin1String("() const;\n"));
    }
    else if(relation->cardinality() == Relation::ManyToMany ||
            (relation->cardinality() == Relation::OneToMany &&
             relation->entityTypeLeft() == m_entityType)) {
        header.append(QLatin1String("\tQList<") + entityType + QLatin1String(" *> ") +
                  relationName + QLatin1String("() const;\n"));
    }
}

void EntityTypeWriter::exportHeader() const
{
    QString typeClass = makeClassname(m_entityType->simplifiedName());
    QString header;

    startHeader(typeClass, header);
    startNamespace(header);

    writeEntityTypeDeclaration(type, header);

    endNamespace(header);
    endHeader(typeClass, header);

    writeToFile(makeHeaderFilename(typeClass), header);
}

void EntityTypeWriter::exportSource() const
{
//    QString typeClass = classname(type->simplifiedName());
//    QString fileName = directory + typeClass.toLower().append(QLatin1String(".cpp"));
//    QString headerFile = headerFileName(type);
//    QString source;

//    source.append(QLatin1String("#include \"") + headerFile + QLatin1String("\"\n\n"));

//    writeNeededHeaders(type, source);
//    source.append(QLatin1String("\n"));
//    startNamespace(source);

//    writeEntityTypeImplementation(type, source);

//    endNamespace(source);

//    QFile file(fileName);
//    if(!file.open(QFile::WriteOnly))
//        return;

//    QTextStream out(&file);
//    out << source;
    //    file.close();
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
