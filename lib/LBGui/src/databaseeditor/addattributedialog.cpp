#include "addattributedialog.h"
#include "ui_addattributedialog.h"

#include "databaseattributeeditdialog.h"

#include <LBDatabase/LBDatabase.h>

namespace LBGui {

AddAttributeDialog::AddAttributeDialog(LBDatabase::Table *table, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAttributeDialog),
    m_databaseEditDialog(0),
    m_table(table)
{
    ui->setupUi(this);
    m_databaseEditDialog = new DatabaseAttributeEditDialog();
    connect(m_databaseEditDialog,SIGNAL(accepted()), this, SLOT(addDatabaseAttribute()));
    connect(m_databaseEditDialog,SIGNAL(rejected()), this, SLOT(reject()));
    ui->editorStackedWidget->addWidget(m_databaseEditDialog);
    ui->editorStackedWidget->setCurrentWidget(m_databaseEditDialog);

    ui->typeComboBox->addItem(LBDatabase::AttributeMetaData::typeToName(LBDatabase::AttributeMetaData::DatabaseAttributeType));
    setMinimumSize(minimumSize() + m_databaseEditDialog->minimumSize());
}

AddAttributeDialog::~AddAttributeDialog()
{
    delete ui;
}

void AddAttributeDialog::addDatabaseAttribute()
{
    m_table->addDatabaseAttribute(m_databaseEditDialog->name(),
                                  m_databaseEditDialog->displayName(),
                                  m_databaseEditDialog->sqlType());
    this->accept();
}

} // namespace LBGui
