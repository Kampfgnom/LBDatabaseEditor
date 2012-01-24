#include "editentitytypesdialog.h"
#include "ui_editentitytypesdialog.h"

#include "entitytypecombobox.h"
#include "editattributewidget.h"
#include "editrelationwidget.h"
#include "propertycombobox.h"

#include <LBDatabase/LBDatabase.h>

#include <QGroupBox>


EditEntityTypesDialog::EditEntityTypesDialog(LBDatabase::Context* context, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditEntityTypesDialog),
    m_context(context),
    m_entityType(0)
{
    ui->setupUi(this);

    m_entityTypeBox = new EntityTypeComboBox(m_context->entityTypes(),this);
    ui->horizontalLayout->insertWidget(2,m_entityTypeBox);

    QList<LBDatabase::EntityType*> list;
    m_entityTypeParentBox = new EntityTypeComboBox(list,this);
    ui->gridLayout->addWidget(m_entityTypeParentBox,1,1);

    fillDialogWithEntityType(m_context->entityTypes().first());

    connect(m_entityTypeBox,SIGNAL(currentEntityTypeChanged()),this,SLOT(onCurrentEntityTypeChanged()));
}

EditEntityTypesDialog::~EditEntityTypesDialog()
{
    delete ui;
}

void EditEntityTypesDialog::on_buttonBox_accepted()
{
    this->accept();
}

void EditEntityTypesDialog::on_buttonBox_rejected()
{
    this->reject();
}

void EditEntityTypesDialog::onCurrentEntityTypeChanged()
{
    fillDialogWithEntityType(m_entityTypeBox->currentItem());
}

void EditEntityTypesDialog::fillDialogWithEntityType(LBDatabase::EntityType* type)
{
    m_entityType = type;

    ui->lineEdit->setText(m_entityType->name());

    if(m_entityType->parentEntityType()){
        QList<LBDatabase::EntityType*> list = m_context->entityTypes();
        list.removeOne(m_entityType);

        m_entityTypeParentBox->setEntityTypes(list);
    }
    else{
        m_entityTypeParentBox->clear();
    }

    if(ui->gridLayout->itemAtPosition(2,1) && ui->gridLayout->itemAtPosition(3,1)){
        clearAttributesAndRelationsLayouts();
    }

    if(m_entityType->attributes().size() > 0){

        QGroupBox* attributeGroupBox = new QGroupBox(this);

        QList<LBDatabase::Property*> list;
        foreach(LBDatabase::Attribute* attribute, m_entityType->attributes()){
            list.append(attribute);
        }
        m_attributeBox = new PropertyComboBox(list,this);
        m_attributeBox->onCurrentPropertyChanged(0);
        connect(m_attributeBox,SIGNAL(currentPropertyChanged()),this,SLOT(onSelectedAttributeChanged()));

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(m_attributeBox);
        layout->addWidget(new EditAttributeWidget(static_cast<LBDatabase::Attribute*>(m_attributeBox->currentItem())));

        attributeGroupBox->setLayout(layout);

        ui->gridLayout->addWidget(attributeGroupBox,2,1);

    }

    if(m_entityType->relations().size() > 0){
        QGroupBox* relationGroupBox = new QGroupBox(this);

        QList<LBDatabase::Property*> list;
        foreach(LBDatabase::Relation* relation, m_entityType->relations()){
            list.append(relation);
        }
        m_relationsBox = new PropertyComboBox(list,this);
        m_relationsBox->onCurrentPropertyChanged(0);
        connect(m_relationsBox,SIGNAL(currentPropertyChanged()),this,SLOT(onSelectedRelationChanged()));

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(m_relationsBox);
        layout->addWidget(new EditRelationWidget(static_cast<LBDatabase::Relation*>(m_relationsBox->currentItem())));

        relationGroupBox->setLayout(layout);

        ui->gridLayout->addWidget(relationGroupBox,3,1);
    }

}

void EditEntityTypesDialog::clearAttributesAndRelationsLayouts()
{
    QWidget* group = ui->gridLayout->itemAtPosition(2,1)->widget();
    QLayout* layout = group->layout();
    while(!layout->isEmpty()){
        QWidget* widget = layout->takeAt(0)->widget();
        delete widget;
    }
    delete layout;
    delete group;

    QWidget* rel = ui->gridLayout->itemAtPosition(3,1)->widget();
    QLayout* relLay = rel->layout();
    while(!relLay->isEmpty()){
        QWidget* widget = relLay->takeAt(0)->widget();
        delete widget;
    }
    delete relLay;
    delete rel;
}

void EditEntityTypesDialog::onSelectedAttributeChanged()
{
    QVBoxLayout* layout = static_cast<QVBoxLayout*>(ui->gridLayout->itemAtPosition(2,1)->widget()->layout());

    QWidget* widget = layout->takeAt(1)->widget();
    delete widget;

    layout->addWidget(new EditAttributeWidget(static_cast<LBDatabase::Attribute*>(m_attributeBox->currentItem())));
}

void EditEntityTypesDialog::onSelectedRelationChanged()
{
    QVBoxLayout* layout = static_cast<QVBoxLayout*>(ui->gridLayout->itemAtPosition(3,1)->widget()->layout());

    QWidget* widget = layout->takeAt(1)->widget();
    delete widget;

    layout->addWidget(new EditRelationWidget(static_cast<LBDatabase::Relation*>(m_relationsBox->currentItem())));
}
