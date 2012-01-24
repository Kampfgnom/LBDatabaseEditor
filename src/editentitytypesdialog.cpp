#include "editentitytypesdialog.h"
#include "ui_editentitytypesdialog.h"

#include "entitytypecombobox.h"
#include "editattributewidget.h"
#include "editrelationwidget.h"

#include <LBDatabase/LBDatabase.h>


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
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setContentsMargins(0,0,0,0);
        layout->setAlignment(Qt::AlignTop);
        foreach(LBDatabase::Attribute* attribute, m_entityType->attributes()){
            EditAttributeWidget* w = new EditAttributeWidget(attribute);
            layout->addWidget(w);
        }
        ui->gridLayout->addLayout(layout,2,1);
        ui->gridLayout->itemAtPosition(2,1)->setAlignment(Qt::AlignTop);
    }

    if(m_entityType->relations().size() > 0){
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setContentsMargins(0,0,0,0);
        layout->setAlignment(Qt::AlignTop);
        foreach(LBDatabase::Relation* relation, m_entityType->relations()){
            EditRelationWidget* w = new EditRelationWidget(relation);
            layout->addWidget(w);
        }
        ui->gridLayout->addLayout(layout,3,1);
        ui->gridLayout->itemAtPosition(3,1)->setAlignment(Qt::AlignTop);
    }

}

void EditEntityTypesDialog::clearAttributesAndRelationsLayouts()
{
    QLayout* layout = ui->gridLayout->itemAtPosition(2,1)->layout();
    while(!layout->isEmpty()){
        QWidget* widget = layout->takeAt(0)->widget();
        delete widget;
    }
    delete layout;

    QLayout* rel = ui->gridLayout->itemAtPosition(3,1)->layout();
    while(!rel->isEmpty()){
        QWidget* widget = rel->takeAt(0)->widget();
        delete widget;
    }
    delete rel;
}
