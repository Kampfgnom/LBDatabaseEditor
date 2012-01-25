#include "editrelationwidget.h"
#include "ui_editrelationwidget.h"

#include "entitytypecombobox.h"

#include <LBDatabase/LBDatabase.h>

EditRelationWidget::EditRelationWidget(LBDatabase::Relation* relation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditRelationWidget),
    m_relation(relation)
{
    ui->setupUi(this);

    m_leftEntityBox = new EntityTypeComboBox(m_relation->storage()->contexts(),this);
    ui->verticalLayoutLeft->addWidget(m_leftEntityBox);


    m_rightEntityBox = new EntityTypeComboBox(m_relation->storage()->contexts(),this);
    ui->verticalLayoutRight->addWidget(m_rightEntityBox);


    updateWidget();
}

EditRelationWidget::~EditRelationWidget()
{
    delete ui;
}

void EditRelationWidget::updateWidget()
{
    ui->labelRelationName->setText(m_relation->name());
    ui->lineEditDisplayLeft->setText(m_relation->displayNameLeft());
    ui->lineEditDisplayRight->setText(m_relation->displayNameRight());

    m_leftEntityBox->setCurrentEntityType(m_relation->entityTypeLeft());
    m_rightEntityBox->setCurrentEntityType(m_relation->entityTypeRight());

    setCardinality(m_relation->cardinality());

}

void EditRelationWidget::on_lineEditDisplayLeft_editingFinished()
{

}

void EditRelationWidget::on_lineEditDisplayRight_editingFinished()
{

}

void EditRelationWidget::on_pushButton_clicked()
{
    m_cardinalityCounter++;

    setCardinality(m_cardinalityCounter);
}

void EditRelationWidget::setCardinality(int cardinality)
{
    m_cardinalityCounter = cardinality;

    switch(cardinality%3){
        case LBDatabase::Relation::OneToOne:
            ui->pushButton->setText("1:1");
            break;
        case LBDatabase::Relation::OneToMany:
            ui->pushButton->setText("1:M");
            break;
        case LBDatabase::Relation::ManyToMany:
            ui->pushButton->setText("M:M");
            break;
    }
}
