#ifndef LBGUI_TABLEVIEW_H
#define LBGUI_TABLEVIEW_H

#include <LBGui/LBGui.h>

namespace LBDatabase {
class Row;
class Table;
}

namespace LBGui {

class TableViewPrivate;
class TableView : public LBGui::TreeView
{
public:
    TableView(QWidget *parent = 0);
    ~TableView();

    void setTable(LBDatabase::Table *table);
    LBDatabase::Table *table() const;

    LBDatabase::Row *firstSelectedRow() const;
    QList<LBDatabase::Row *> selectedRows() const;

private:
    TableViewPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(TableView)
};

} // namespace LBGui

#endif // LBGUI_TABLEVIEW_H
