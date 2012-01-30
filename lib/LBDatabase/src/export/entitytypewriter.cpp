#include "entitytypewriter.h"

#include "calculatorwriter.h"

#include "../attribute.h"
#include "../entitytype.h"
#include "../enumattribute.h"
#include "../function.h"

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

void EntityTypeWriter::writeNeededHeaders(QString &source) const
{
    QStringList declaredTypes;
    QString name;

    source.append(QLatin1String("\n"));

    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(relation->entityTypeLeft() == m_entityType) {
            name = makeClassname(relation->entityTypeRight()->name());
        }
        else {
            name = makeClassname(relation->entityTypeLeft()->name());
        }

        if(!declaredTypes.contains(name)) {
            declaredTypes << name;
            writeInclude(name, source);
        }
    }

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        name = makeClassname(function->keyEntityType()->name());
        if(!declaredTypes.contains(name)) {
            declaredTypes << name;
            writeInclude(name, source);
        }
    }

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
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

void EntityTypeWriter::writePropertyNameStrings(QString &header) const
{
    writeNamespaceBegin(m_classname+QLatin1String("Properties"), header);

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        QString attributeName = attribute->name();
        header.append(QLatin1String("const QString ")+ makeClassname(attributeName) + QLatin1String("Attribute(\"") +
                      attributeName+QLatin1String("\");\n"));
    }

    QList<Relation *> visitedRelations;
    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(!visitedRelations.contains(relation)) {
            header.append(QLatin1String("const QString ")+ makeRelationName(relation) + QLatin1String("Relation(\"") +
                          relation->name()+QLatin1String("\");\n"));
            visitedRelations.append(relation);
        }
    }

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        QString functionName = function->name();
        header.append(QLatin1String("const QString ")+ makeClassname(functionName) + QLatin1String("Function(\"") +
                      functionName+QLatin1String("\");\n"));
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

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        name = makeClassname(function->keyEntityType()->name());
        if(!declaredTypes.contains(name)) {
            declaredTypes << name;
            header.append(QLatin1String("class ") + name + QLatin1String(";\n"));
        }
    }
}

void EntityTypeWriter::writeDeclaration(QString &header) const
{
    QString oldContent = readFromFile(makeHeaderFilename(m_classname));
    QString extraContent = extractExtraContent(oldContent);

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
        if(attribute->type() == Attribute::Enum) {
            writeEnum(static_cast<EnumAttribute *>(attribute), header);
        }
    }

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        writeAttributeGetterDeclaration(attribute, header);
    }

    header.append(QLatin1String("\n"));

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->isEditable()) {
           writeAttributeSetterDeclaration(attribute, header);
        }
    }

    header.append(QLatin1String("\n"));

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        writeFunctionDeclaration(function, header);
    }

    header.append(QLatin1String("\n"));

    QList<Relation *> visitedRelations;
    foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
        if(!visitedRelations.contains(relation)) {
            writeRelationDeclaration(relation, header);
            visitedRelations.append(relation);
        }
    }

    writeExtraContent(extraContent, header);

    header.append(QLatin1String("\n"));

    header.append(QLatin1String("signals:\n"));

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->isEditable()) {
           writeAttributeChangedSignal(attribute, header);
        }
    }

    header.append(QLatin1String("};\n\n"));
}

void EntityTypeWriter::writeImplementation(QString &source) const
{
    QString oldContent = readFromFile(makeSourceFilename(m_classname));
    QString extraContent = extractExtraContent(oldContent);

    QString baseClass("Entity");
    if(m_entityType->parentEntityType())
        baseClass = makeClassname(m_entityType->parentEntityType()->name());

    source.append(QLatin1String("const QString ") + m_classname + QLatin1String("::Name(\"") + m_entityType->name() + QLatin1String("\");\n\n"));

    source.append(
         m_classname+QLatin1String("::")+m_classname+QLatin1String(
    "(LBDatabase::Row *row, LBDatabase::Context *context) :\n"
        "\t") + baseClass + QLatin1String("(row, context)\n"
    "{\n"
    "}\n\n"));

     foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
         writeAttributeGetterImplementation(attribute, source);
     }

     foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
         if(attribute->isEditable()) {
            writeAttributeSetterImplementation(attribute, source);
         }
     }

     QList<Relation *> visitedRelations;
     foreach(Relation *relation, m_entityType->nonInhertitedRelations()) {
         if(!visitedRelations.contains(relation)) {
            writeRelationImplementation(relation, source);
            visitedRelations.append(relation);
         }
     }

     foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
         writeFunctionImplementation(function, source);
     }

     writeExtraContent(extraContent, source);

     source.append(QLatin1String("\n"));
}

void EntityTypeWriter::writeEnum(EnumAttribute *attribute, QString &header) const
{
    header.append(QLatin1String("\tenum ")+makeClassname(attribute->name())+QLatin1String(" {\n"));

    const QMap<int, QString> map = attribute->enumValues();
    QMap<int, QString>::const_iterator i = map.constBegin();
    while (i != map.constEnd()) {
        if(i != map.constBegin()) {
            header.append(QLatin1String(",\n"));
        }
        header.append(QLatin1String("\t\t")+i.value()+QLatin1String(" = ")+QString::number(i.key()));
        ++i;
    }
    header.append(QLatin1String("\n\t};\n\n"));
}

void EntityTypeWriter::writeAttributeGetterDeclaration(Attribute *attribute, QString &header) const
{
    header.append(QLatin1String("\t") + attribute->qtType() + QLatin1String(" ") +
                  makeMethodName(attribute->name()) + QLatin1String("() const;\n"));
}

void EntityTypeWriter::writeAttributeSetterDeclaration(Attribute *attribute, QString &header) const
{
    QString constString;
    QString ampString;
    if(attribute->qtType().startsWith("Q")) {
        constString = QLatin1String("const ");
        ampString = QLatin1String("&");
    }

    header.append(QLatin1String("\tvoid set") +
                  makeClassname(attribute->name()) + QLatin1String("(")+constString+attribute->qtType()+QLatin1String(" ")+ampString+makeMethodName(attribute->name())+QLatin1String(");\n"));
}

void EntityTypeWriter::writeAttributeGetterImplementation(Attribute *attribute, QString &source) const
{
    QString attributeType = attribute->qtType();
    QString attributeName = attribute->name();
    if(attribute->type() == Attribute::Enum) {
        source.append(m_classname+QLatin1String("::")+makeClassname(attributeType)+QLatin1String(" ")+m_classname+QLatin1String("::")+makeMethodName(attributeName)+
                      QLatin1String("() const\n"
                                    "{\n"
                                    "\treturn static_cast<")+makeClassname(attributeType)+QLatin1String(">(value(")+m_classname+
                      QLatin1String("Properties::")+attributeName.left(1).toUpper() + attributeName.mid(1) + QLatin1String("Attribute).value<int>());\n"
                                                  "}\n\n"));
    }
    else {
        source.append(attributeType+QLatin1String(" ")+m_classname+QLatin1String("::")+makeMethodName(attributeName)+
                      QLatin1String("() const\n"
                                    "{\n"
                                    "\treturn value(")+m_classname+
                      QLatin1String("Properties::")+attributeName.left(1).toUpper() + attributeName.mid(1) + QLatin1String("Attribute).value<") +
                      attributeType+QLatin1String(">();\n"
                                                  "}\n\n"));
    }
}

void EntityTypeWriter::writeAttributeSetterImplementation(Attribute *attribute, QString &source) const
{
    QString attributeType = attribute->qtType();
    QString attributeName = attribute->name();
    if(attribute->type() == Attribute::Enum) {
        source.append(m_classname+QLatin1String("::")+makeClassname(attributeType)+QLatin1String(" ")+m_classname+QLatin1String("::")+makeMethodName(attributeName)+
                      QLatin1String("() const\n"
                                    "{\n"
                                    "\treturn static_cast<")+makeClassname(attributeType)+QLatin1String(">(value(")+m_classname+
                      QLatin1String("Properties::")+attributeName.left(1).toUpper() + attributeName.mid(1) + QLatin1String("Attribute).value<int>());\n"
                                                  "}\n\n"));
    }
    else {
        QString constString;
        QString ampString;
        if(attribute->qtType().startsWith("Q")) {
            constString = QLatin1String("const ");
            ampString = QLatin1String("&");
        }

        source.append(QLatin1String("void ")+m_classname+QLatin1String("::set")+makeClassname(attribute->name()) + QLatin1String("(")+constString+attribute->qtType()+QLatin1String(" ")+ampString+makeMethodName(attribute->name())+QLatin1String(")\n"
                                    "{\n"
                                    "\tif(")+makeMethodName(attribute->name())+QLatin1String(" == this->")+makeMethodName(attribute->name())+QLatin1String("())\n"
                                    "\t\treturn;\n"
                                    "\tsetValue(")+m_classname+
                      QLatin1String("Properties::")+attributeName.left(1).toUpper() + attributeName.mid(1) + QLatin1String("Attribute,"
                                                  "QVariant::fromValue<") +
                      attributeType+QLatin1String(">(") +
                      makeMethodName(attribute->name())+QLatin1String("));\n"
                                                  "\temit ")+makeMethodName(attribute->name())+QLatin1String("Changed(")+
                     makeMethodName(attribute->name())+QLatin1String(");\n"
                                                  "}\n\n"));
    }
}

void EntityTypeWriter::writeAttributeChangedSignal(Attribute *attribute, QString &header) const
{
    header.append(QLatin1String("\tvoid ") +
                  makeMethodName(attribute->name()) + QLatin1String("Changed(") + attribute->qtType() + QLatin1String(" ")
                  + makeMethodName(attribute->name()) + QLatin1String(");\n"));
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

void EntityTypeWriter::writeFunctionDeclaration(Function *function, QString &header) const
{
    header.append(QLatin1String("\t") + function->qtTypeName() + QLatin1String(" ") +
                  makeMethodName(function->name()) + QLatin1String("(const ")+makeClassname(function->keyEntityType()->name())+
                  QLatin1String(" *")+makeMethodName(function->keyEntityType()->name())+QLatin1String(") const;\n"));
}

void EntityTypeWriter::writeFunctionImplementation(Function *function, QString &source) const
{
    source.append(function->qtTypeName() + QLatin1String(" ") +m_classname+QLatin1String("::")+
                  makeMethodName(function->name()) + QLatin1String("(const ")+makeClassname(function->keyEntityType()->name())+
                  QLatin1String(" *")+makeMethodName(function->keyEntityType()->name())+QLatin1String(") const\n"
                                "{\n"
                                "\treturn function(")+m_classname+
                  QLatin1String("Properties::")+makeClassname(function->name()) + QLatin1String("Function)->value(")+
                  makeMethodName(function->keyEntityType()->name())+QLatin1String(").value<") +
                  function->qtTypeName()+QLatin1String(">();\n"
                                              "}\n\n"));
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
