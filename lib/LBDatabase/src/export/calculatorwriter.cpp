#include "calculatorwriter.h"

#include "../entitytype.h"
#include "../function.h"

namespace LBDatabase {

CalculatorWriter::CalculatorWriter(const CppExporter *exporter) :
    Writer(exporter)
{
}

void CalculatorWriter::setEntityType(EntityType *type)
{
    m_entityType = type;
}

void CalculatorWriter::write() const
{
    if(isNeeded()) {
        exportHeader();
        exportSource();
    }
}

bool CalculatorWriter::isNeeded() const
{
    bool hasCalculatedProperties = false;
    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->isCalculated()) {
            hasCalculatedProperties = true;
        }
    }

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        if(function->isCalculated()) {
            hasCalculatedProperties = true;
        }
    }

    return hasCalculatedProperties;
}

void CalculatorWriter::exportHeader() const
{
    QString calculatorClass = makeClassname(m_entityType->name() + QLatin1String("Calculator"));
    QString header;

    startHeader(calculatorClass, header);
    startNamespace(header);

    header.append(QLatin1String(
        "\nclass ")+calculatorClass+QLatin1String(" : public LBDatabase::Calculator\n"
        "{\n"
        "public:\n\tQ_INVOKABLE explicit ")+
            calculatorClass+QLatin1String("(QObject *parent = 0);\n\n")
    );

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->isCalculated()) {
            header.append(QLatin1String("\t\n\tQ_INVOKABLE QVariant ")+makeMethodName(attribute->name())+QLatin1String("(const LBDatabase::Entity *entity) const;\n"));
        }
    }

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        if(function->isCalculated()) {
            header.append(QLatin1String("\t\n\tQ_INVOKABLE EntityVariantHash ")+makeMethodName(function->name())+QLatin1String("(const LBDatabase::Entity *entity) const;\n"));
        }
    }

    header.append(QLatin1String("};\n\n"));

    endNamespace(header);
    endHeader(calculatorClass, header);

    writeToFile(makeHeaderFilename(calculatorClass), header);
}

void CalculatorWriter::exportSource() const
{
    QString calculatorClass = makeClassname(m_entityType->name() + QLatin1String("Calculator"));
    QString source;

    writeInclude(calculatorClass, source);
    startNamespace(source);

    source.append(QLatin1String("\n")+
            calculatorClass+QLatin1String("::")+calculatorClass+QLatin1String(
    "(QObject *parent) :\n"
        "\tCalculator(parent)\n"
      "{\n"
      "}\n\n"));

    foreach(Attribute *attribute, m_entityType->nonInhertitedAttributes()) {
        if(attribute->isCalculated()) {
            source.append(QLatin1String("QVariant ")+calculatorClass+QLatin1String("::")+makeMethodName(attribute->name())+QLatin1String("(const LBDatabase::Entity *entity) const\n"
            "{\n"
                 "\t//! \\todo IMPLEMENT ME\n"
                 "\treturn QVariant();\n"
            "}\n\n"));
        }
    }

    foreach(Function *function, m_entityType->nonInhertitedFunctions()) {
        if(function->isCalculated()) {
            source.append(QLatin1String("EntityVariantHash ")+calculatorClass+QLatin1String("::")+makeMethodName(function->name())+QLatin1String("(const LBDatabase::Entity *entity) const\n"
            "{\n"
                 "\t//! \\todo IMPLEMENT ME\n"
                 "\treturn EntityVariantHash();\n"
            "}\n\n"));
        }
    }
    endNamespace(source);

    writeToFile(makeSourceFilename(calculatorClass), source);
}

} // namespace LBDatabase
