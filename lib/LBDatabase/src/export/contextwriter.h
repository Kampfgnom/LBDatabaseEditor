#ifndef LBDATABASE_CONTEXTWRITER_H
#define LBDATABASE_CONTEXTWRITER_H

#include "writer.h"

namespace LBDatabase {

class CppExporter;
class Context;

class ContextWriter : public Writer
{
public:
    ContextWriter(const CppExporter *exporter);

    void setContext(Context *context);

    void write() const;

private:
    Context *m_context;

    void exportContextHeader() const;
    void exportContextSource() const;
};

} // namespace LBDatabase

#endif // LBDATABASE_CONTEXTWRITER_H
