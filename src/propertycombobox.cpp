#include "propertycombobox.h"

#include <LBDatabase/LBDatabase.h>

PropertyComboBox::PropertyComboBox(QList<LBDatabase::Property*> properties, QWidget *parent) :
    QComboBox(parent),
    m_properties(properties),
    m_selectedProperty(0)
{
    foreach(LBDatabase::Property* property, properties){
        this->addItem(property->displayName());
    }

    connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(onCurrentPropertyChanged(int)));
}

void PropertyComboBox::onCurrentPropertyChanged(int index)
{
    if(index >= 0){
        m_selectedProperty = m_properties.at(index);

        emit currentPropertyChanged();
     }
}

LBDatabase::Property* PropertyComboBox::currentItem()
{
    return m_selectedProperty;
}

void PropertyComboBox::updateComboBox(){
    this->clear();

    foreach(LBDatabase::Property* prop, m_properties){
        this->addItem(prop->name());
    }
}

void PropertyComboBox::setPropertys(QList<LBDatabase::Property*> properties)
{
    m_properties = properties;

    updateComboBox();
}
