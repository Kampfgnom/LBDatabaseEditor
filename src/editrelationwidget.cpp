#include "editrelationwidget.h"
#include "ui_editrelationwidget.h"

#include <LBDatabase/LBDatabase.h>

EditRelationWidget::EditRelationWidget(LBDatabase::Relation* relation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditRelationWidget),
    m_relation(relation)
{
    ui->setupUi(this);

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

}
