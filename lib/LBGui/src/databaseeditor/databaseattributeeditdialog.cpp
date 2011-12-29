#include "databaseattributeeditdialog.h"
#include "ui_databaseattributeeditdialog.h"

#include <LBDatabase/LBDatabase.h>

#include <QLabel>

namespace LBGui {

DatabaseAttributeEditDialog::DatabaseAttributeEditDialog(LBDatabase::DatabaseAttributeMetaData *metaData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseAttributeEditDialog),
    m_metaData(metaData)
{
    ui->setupUi(this);
    ui->lineEditName->setText(metaData->name());
    ui->lineEditDisplayName->setText(metaData->displayName());
    ui->comboBoxSqlType->addItems(LBDatabase::DatabaseAttributeMetaData::sqlTypeNames());
    ui->comboBoxSqlType->setCurrentIndex(metaData->sqlType());
    ui->comboBoxSqlType->setEditable(false);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveMetaData()));
}

DatabaseAttributeEditDialog::DatabaseAttributeEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseAttributeEditDialog),
    m_metaData(0)
{
    ui->setupUi(this);
    ui->comboBoxSqlType->addItems(LBDatabase::DatabaseAttributeMetaData::sqlTypeNames());
    ui->comboBoxSqlType->setCurrentIndex(0);
}

DatabaseAttributeEditDialog::~DatabaseAttributeEditDialog()
{
    delete ui;
}

QString DatabaseAttributeEditDialog::name() const
{
    return ui->lineEditName->text();
}

QString DatabaseAttributeEditDialog::displayName() const
{
    return ui->lineEditDisplayName->text();
}

LBDatabase::DatabaseAttributeMetaData::SqlType DatabaseAttributeEditDialog::sqlType() const
{
    return static_cast<LBDatabase::DatabaseAttributeMetaData::SqlType>(ui->comboBoxSqlType->currentIndex() + 1);
}

void DatabaseAttributeEditDialog::saveMetaData()
{
    m_metaData->setName(name());
    m_metaData->setDisplayName(displayName());
}



} // namespace LBGui
