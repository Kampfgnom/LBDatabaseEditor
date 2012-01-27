#include "contextwriter.h"

#include "entitytypewriter.h"

#include "../context.h"
#include "../entitytype.h"

namespace LBDatabase {

ContextWriter::ContextWriter(const CppExporter *exporter) :
    Writer(exporter),
    m_context(0)
{
}

void ContextWriter::setContext(Context *context)
{
    m_context = context;
}

void ContextWriter::write() const
{
    if(!m_context)
        return;

    exportContextHeader();
    exportContextSource();

    EntityTypeWriter writer(m_exporter);
    foreach(EntityType *type, m_context->entityTypes()) {
        if(type != m_context->baseEntityType()) {
            writer.setEntityType(type);
            writer.write();
        }
    }
}

void ContextWriter::exportContextHeader() const
{
//    QString contextName = makeClassname(m_context->name() + QLatin1String("Context"));
//    QString baseEntityTypeName = makeClassname(m_context->baseEntityType()->name());
//    QString header;

//    startHeader(baseEntityTypeName, header);
//    startNamespace(header);

//    //writeEntityTypeDeclaration(context->baseEntityType(), header);

//    header.append(QLatin1String("class ")+contextName+QLatin1String(" : public LBDatabase::Context\n"
//                                                                    "{\n"
//                                                                    "\tQ_OBJECT\n"
//                                                                    "public:\n"
//                                                                    "\tQ_INVOKABLE "));

//    header.append(contextName + QLatin1String("(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);\n"));
//    header.append(QLatin1String("\tstatic const QString Name;\n\n\t"));
//    header.append(baseEntityTypeName+QLatin1String(" *")+makeMethodName(baseEntityTypeName)+QLatin1String("(int id) const;\n"));
//    header.append(QLatin1String("};\n\n"));

//    endNamespace(header);
//    endHeader(baseEntityTypeName, header);

//    writeToFile(makeHeaderFilename(baseEntityTypeName), header);
}

void ContextWriter::exportContextSource() const
{
//    QString contextName = makeClassname(m_context->name() + QLatin1String("Context"));
//    QString baseEntityTypeName = makeClassname(m_context->baseEntityType()->name());
//    QString source;

//    writeInclude(baseEntityTypeName, source);

//    writeNeededHeaders(context->baseEntityType(), source);

//    startNamespace(source);

//    foreach(EntityType *type, context->entityTypes()) {
//        if(type != context->baseEntityType()) {
//            QString file = headerFileName(type);
//            source.append(QLatin1String("#include \"") + file + QLatin1String("\"\n"));
//        }
//    }

//    source.append(QLatin1String("\nconst QString ") + contextName + QLatin1String("::Name(\"") + context->name() + QLatin1String("\");\n"));

//    source.append(
//            contextName+QLatin1String("::")+contextName+QLatin1String(
//    "(LBDatabase::Row *row, LBDatabase::Storage *parent) :\n"
//        "\tContext(row, parent)\n"
//    "{\n"));

//    foreach(EntityType *type, context->entityTypes()) {
//        source.append(QLatin1String("\tregisterEntityClass<") + classname(type->simplifiedName()) + QLatin1String(">();\n"));
//        //source.append(QLatin1String("\tregisterCalculatorClass<") + classname(type->simplifiedName()) + QLatin1String(",") + classname(type->simplifiedName()) + QLatin1String("Calculator>();\n\n"));
//    }
//    source.append(QLatin1String("}\n\n"));

//    source.append(
//    baseEntityTypeName+QLatin1String(" *")+contextName+QLatin1String("::")+baseEntityTypeName.left(1).toLower()+baseEntityTypeName.mid(1)+QLatin1String("(int id) const\n"
//    "{\n"
//        "\treturn static_cast<")+baseEntityTypeName+QLatin1String(" *>(entity(id));\n"
//    "}\n\n"));

//    writeEntityTypeImplementation(context->baseEntityType(), source);

//    endNamespace(source);

//    QFile file(fileName);
//    if(!file.open(QFile::WriteOnly))
//        return;

//    QTextStream out(&file);
//    out << source;
//    file.close();
}
} // namespace LBDatabase
