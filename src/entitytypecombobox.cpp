#include "entitytypecombobox.h"

#include <LBDatabase/LBDatabase.h>

#include <QDebug>

EntityTypeComboBox::EntityTypeComboBox(QList<LBDatabase::EntityType*> types, QWidget *parent) :
    QComboBox(parent),
    m_types(types),
    m_selectedType(0)
{
    foreach(LBDatabase::EntityType* type, types){
        this->addItem(type->name());
    }

    connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(onCurrentEntityTypeChanged(int)));
}

EntityTypeComboBox::EntityTypeComboBox(QList<LBDatabase::Context*> contexts, QWidget *parent) :
    QComboBox(parent),
    m_selectedType(0)
{
    foreach(LBDatabase::Context* context, contexts){
        foreach(LBDatabase::EntityType* type, context->entityTypes()){
            this->addItem(type->name());
            m_types.append(type);
        }
        //this->insertSeparator(this->count());
    }

    connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(onCurrentEntityTypeChanged(int)));
}

void EntityTypeComboBox::onCurrentEntityTypeChanged(int index)
{
    if(index >= 0){
        m_selectedType = m_types.at(index);

        emit currentEntityTypeChanged();
     }
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

void EntityTypeComboBox::setEntityTypes(QList<LBDatabase::EntityType*> types)
{
    m_types = types;

    updateComboBox();
}

void EntityTypeComboBox::setCurrentEntityType(LBDatabase::EntityType* type)
{
    if(m_types.contains(type)){
        this->setCurrentIndex(this->findText(type->name()));
    }
    else{
        qWarning() << "EntityTypeComboBox::setCurrentEntityType: Type with name " << type->name() << " couldn't found in list!";
    }
}
