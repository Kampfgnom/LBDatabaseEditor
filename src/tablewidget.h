#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <LBGui/LBGui.h>

namespace LBDatabase {
class Table;
}

namespace LBGui {

class TableView;

class TableWidget : public TabWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = 0);
    
    void setTable(LBDatabase::Table *table);

private:
    LBDatabase::Table *m_table;
    TableView *m_plainContentsTableView;
};

} // namespace LBGui

#endif // TABLEWIDGET_H
