#include "contextview.h"

#include <LBDatabase/LBDatabase.h>

#include <QSortFilterProxyModel>
#include <QHeaderView>

namespace LBGui {

class ContextViewPrivate {
    ContextViewPrivate() : context(0) {}

    void init();
    void resizeAllColumnsToContents();

    LBDatabase::Context *context;
    QSortFilterProxyModel *contextSortProxyModel;

    ContextView * q_ptr;
    Q_DECLARE_PUBLIC(ContextView)
};

void ContextViewPrivate::init()
{
    Q_Q(ContextView);
    q->setSortingEnabled(true);
    q->setUniformRowHeights(true);
    q->setSelectionMode(QAbstractItemView::ExtendedSelection);
    q->setDoubleClickActions(TreeView::EditAttributeAction);

    contextSortProxyModel = new QSortFilterProxyModel(q);
    q->setModel(contextSortProxyModel);
}

void ContextViewPrivate::resizeAllColumnsToContents()
{
    Q_Q(ContextView);
    for(int i = 0; i < contextSortProxyModel->columnCount(); ++i) {
        q->resizeColumnToContents(i);
    }
}

ContextView::ContextView(QWidget *parent) :
    TreeView(parent),
    d_ptr(new ContextViewPrivate)
{
    Q_D(ContextView);
    d->q_ptr = this;
    d->init();
}

ContextView::~ContextView()
{
    Q_D(ContextView);
    delete d;
}

void ContextView::setContext(LBDatabase::Context *context)
{
    Q_D(ContextView);
    if(d->context == context)
        return;

    header()->setResizeMode(QHeaderView::ResizeToContents);
    d->contextSortProxyModel->setSourceModel(context);
    d->context = context;
    header()->setResizeMode(QHeaderView::Interactive);
    resizeColumnToContents(d->contextSortProxyModel->columnCount() - 1);
}

LBDatabase::Context *ContextView::context() const
{
    Q_D(const ContextView);
    return d->context;
}

LBDatabase::Entity *ContextView::firstSelectedEntity() const
{
    Q_D(const ContextView);
    if(!d->context)
        return 0;

    QModelIndexList list = selectionModel()->selectedRows();
    if(list.isEmpty())
        return 0;

    QModelIndex index = d->contextSortProxyModel->mapToSource(list.first());
    return d->context->entities().at(index.row());
}

QList<LBDatabase::Entity *> ContextView::selectedEntities() const
{
    Q_D(const ContextView);

    QList<LBDatabase::Entity *> entitys;

    if(!d->context)
        return entitys;

    foreach(QModelIndex i, selectionModel()->selectedRows()) {
        QModelIndex index = d->contextSortProxyModel->mapToSource(i);
        entitys.append(d->context->entities().at(index.row()));
    }

    return entitys;
}


} // namespace LBGui
