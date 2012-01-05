#include "tableview.h"

#include <LBDatabase/LBDatabase.h>

#include <QSortFilterProxyModel>
#include <QHeaderView>

namespace LBGui {

class TableViewPrivate {
    TableViewPrivate() : table(0) {}

    void init();
    void resizeAllColumnsToContents();

    LBDatabase::Table *table;
    QSortFilterProxyModel *tableSortProxyModel;

    TableView * q_ptr;
    Q_DECLARE_PUBLIC(TableView)
};

void TableViewPrivate::init()
{
    Q_Q(TableView);
    q->setSortingEnabled(true);
    q->setUniformRowHeights(true);
    q->setSelectionMode(QAbstractItemView::ExtendedSelection);
    q->setDoubleClickActions(TreeView::EditAttributeAction);

    tableSortProxyModel = new QSortFilterProxyModel(q);
    q->setModel(tableSortProxyModel);
}

void TableViewPrivate::resizeAllColumnsToContents()
{
    Q_Q(TableView);
    for(int i = 0; i < tableSortProxyModel->columnCount(); ++i) {
        q->resizeColumnToContents(i);
    }
}

TableView::TableView(QWidget *parent) :
    TreeView(parent),
    d_ptr(new TableViewPrivate)
{
    Q_D(TableView);
    d->q_ptr = this;
    d->init();
}

TableView::~TableView()
{
    Q_D(TableView);
    delete d;
}

void TableView::setTable(LBDatabase::Table *table)
{
    Q_D(TableView);
    if(d->table == table)
        return;

    header()->setResizeMode(QHeaderView::ResizeToContents);
    d->tableSortProxyModel->setSourceModel(table);
    d->table = table;
    header()->setResizeMode(QHeaderView::Interactive);
    resizeColumnToContents(d->tableSortProxyModel->columnCount() - 1);
}

LBDatabase::Table *TableView::table() const
{
    Q_D(const TableView);
    return d->table;
}

LBDatabase::Row *TableView::firstSelectedRow() const
{
    Q_D(const TableView);
    if(!d->table)
        return 0;

    QModelIndexList list = selectionModel()->selectedRows();
    if(list.isEmpty())
        return 0;

    QModelIndex index = d->tableSortProxyModel->mapToSource(list.first());
    return d->table->rowAt(index.row());
}

QList<LBDatabase::Row *> TableView::selectedRows() const
{
    Q_D(const TableView);

    QList<LBDatabase::Row *> rows;

    if(!d->table)
        return rows;

    foreach(QModelIndex i, selectionModel()->selectedRows()) {
        QModelIndex index = d->tableSortProxyModel->mapToSource(i);
        rows.append(d->table->rowAt(index.row()));
    }

    return rows;
}


} // namespace LBGui
