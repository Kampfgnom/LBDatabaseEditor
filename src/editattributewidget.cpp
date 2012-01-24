#include "editattributewidget.h"
#include "ui_editattributewidget.h"

#include <LBDatabase/LBDatabase.h>

EditAttributeWidget::EditAttributeWidget(LBDatabase::Attribute* attribute, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditAttributeWidget),
    m_attribute(attribute)
{
    ui->setupUi(this);

    updateWidget();

    this->setContentsMargins(0,0,0,0);
}

EditAttributeWidget::~EditAttributeWidget()
{
    delete ui;
}

void EditAttributeWidget::updateWidget()
{
    ui->lineEditDisplayName->setText(m_attribute->displayName());
    ui->labelName->setText(m_attribute->name());

}
