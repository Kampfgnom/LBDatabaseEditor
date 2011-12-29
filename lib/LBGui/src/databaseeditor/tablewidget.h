#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <widgets/tabwidget.h>

#include <QSortFilterProxyModel>

namespace LBDatabase {
class Table;
}

namespace LBGui {

class AttributesTable;
class TreeView;

class TableWidget : public TabWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = 0);
    
    void setTable(LBDatabase::Table *table);

private slots:
    void editSelectedAttribute();
    void addAttribute();
    void removeAttribute();

private:
    LBDatabase::Table *m_table;
    AttributesTable *m_attributesTable;
    TreeView *m_plainContentsTreeView;
    QSortFilterProxyModel *m_attributesSortProxyModel;
    QSortFilterProxyModel *m_tableSortProxyModel;
};

} // namespace LBGui

#endif // TABLEWIDGET_H
