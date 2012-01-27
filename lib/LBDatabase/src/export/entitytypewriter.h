#ifndef LBDATBASE_ENTITYTYPEWRITER_H
#define LBDATBASE_ENTITYTYPEWRITER_H

#include "writer.h"

namespace LBDatabase {

class Attribute;
class CppExporter;
class EntityType;
class Relation;

class EntityTypeWriter : public Writer
{
public:
    EntityTypeWriter(const CppExporter *exporter);

    void setEntityType(EntityType *type);

    void write() const;

private:
    EntityType *m_entityType;

    void exportHeader() const;
    void exportSource() const;

    void writeNeededHeaders(QString &header) const;
    void writePropertyNameStrings(QString &header) const;
    void writeForwardDeclarations(QString &header) const;

    void writeDeclaration(QString &header) const;
    void writeImplementation(QString &source) const;

    void writeAttributeDeclaration(Attribute *attribute, QString &header) const;
    void writeAttributeImplementation(Attribute *attribute, QString &source) const;

    void writeRelationDeclaration(Relation *relation, QString &header) const;

    QString makeRelationName(Relation *relation) const;
    QString makeRelationType(Relation *relation) const;
};

} // namespace LBDatabase

#endif // LBDATBASE_ENTITYTYPEWRITER_H
