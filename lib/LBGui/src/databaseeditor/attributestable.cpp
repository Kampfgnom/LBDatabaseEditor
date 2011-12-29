#include "attributestable.h"

#include <LBDatabase/LBDatabase.h>

#include <QSortFilterProxyModel>

namespace LBGui {

AttributesTable::AttributesTable(QWidget *parent) :
    TreeView(parent),
    m_table(0),
    m_proxyModel(new QSortFilterProxyModel(this)),
    m_metaData(0)
{
    setSortingEnabled(true);
    setUniformRowHeights(true);
    setModel(m_proxyModel);
}

void AttributesTable::setTable(LBDatabase::Table *table)
{
    if(table) {
        m_metaData = table->metaData();
        m_proxyModel->setSourceModel(m_metaData);
    }
}

LBDatabase::AttributeMetaData *AttributesTable::firstSelectedAttributeMetaData() const
{
    if(!m_metaData) {
        return 0;
    }

    QModelIndexList list = selectionModel()->selectedIndexes();

    if(list.isEmpty()) {
        return 0;
    }

    QModelIndex indexInSource = m_proxyModel->mapToSource(list.first());
    return m_metaData->attributeMetaDataByModelIndex(indexInSource);
}

} // namespace LBGui
