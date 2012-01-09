#include "addentitytypedialog.h"
#include "ui_addentitytypedialog.h"

#include "entitytypecombobox.h"

#include <LBDatabase/LBDatabase.h>

AddEntityTypeDialog::AddEntityTypeDialog(LBDatabase::Context* context, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEntityTypeDialog),
    m_context(context)
{
    ui->setupUi(this);

    m_parentComboBox = new EntityTypeComboBox(context->entityTypes(),this);
    ui->gridLayout->addWidget(m_parentComboBox,1,1);

}

AddEntityTypeDialog::~AddEntityTypeDialog()
{
    delete ui;
}

void AddEntityTypeDialog::on_pushButtonOK_clicked()
{
    if(ui->lineEdit->text() != ""){
        m_context->addEntityType(ui->lineEdit->text(),m_parentComboBox->currentItem());
    }

    this->accept();
}
