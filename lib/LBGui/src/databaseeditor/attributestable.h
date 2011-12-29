#ifndef LBGUI_ATTRIBUTESTABLE_H
#define LBGUI_ATTRIBUTESTABLE_H

#include <widgets/treeview.h>

class QSortFilterProxyModel;

namespace LBDatabase {
class AttributeMetaData;
class Table;
class TableMetaData;
}

namespace LBGui {

class AttributesTable : public TreeView
{
public:
    explicit AttributesTable(QWidget *parent);

    void setTable(LBDatabase::Table *table);

    LBDatabase::AttributeMetaData *firstSelectedAttributeMetaData() const;

private:
    LBDatabase::Table *m_table;
    QSortFilterProxyModel *m_proxyModel;
    LBDatabase::TableMetaData *m_metaData;
};

} // namespace LBGui

#endif // LBGUI_ATTRIBUTESTABLE_H
