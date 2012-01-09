#include "entitytypecombobox.h"

#include <LBDatabase/LBDatabase.h>

EntityTypeComboBox::EntityTypeComboBox(QList<LBDatabase::EntityType*> types, QWidget *parent) :
    QComboBox(parent),
    m_types(types),
    m_selectedType(types.first())
{
    foreach(LBDatabase::EntityType* type, types){
        this->addItem(type->name());
    }

    connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(onCurrentEntityTypeChanged(int)));
}

void EntityTypeComboBox::onCurrentEntityTypeChanged(int index)
{
    m_selectedType = m_types.at(index);

    emit currentEntityTypeChanged();
}

LBDatabase::EntityType* EntityTypeComboBox::currentItem()
{
    return m_selectedType;
}

void EntityTypeComboBox::updateComboBox(){
    this->clear();

    foreach(LBDatabase::EntityType* type, m_types){
        this->addItem(type->name());
    }
}