#include "createtabledialog.h"
#include "ui_createtabledialog.h"

#include <QString>

CreateTableDialog::CreateTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTableDialog)
{
    ui->setupUi(this);
}

CreateTableDialog::~CreateTableDialog()
{
    delete ui;
}

QString CreateTableDialog::name() const
{
    return ui->lineEditName->text();
}

void CreateTableDialog::on_buttonBox_accepted()
{
    this->accept();
}

void CreateTableDialog::on_buttonBox_rejected()
{
    this->reject();
}
