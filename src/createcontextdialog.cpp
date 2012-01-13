#include "createcontextdialog.h"
#include "ui_createcontextdialog.h"

CreateContextDialog::CreateContextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateContextDialog)
{
    ui->setupUi(this);
}

CreateContextDialog::~CreateContextDialog()
{
    delete ui;
}

void CreateContextDialog::on_buttonBox_accepted()
{
    this->accept();
}

void CreateContextDialog::on_buttonBox_rejected()
{
    this->reject();
}

QString CreateContextDialog::contextName() const{
    return ui->lineEditContextName->text();
}

QString CreateContextDialog::baseEntityTypeName() const
{
    return ui->lineEditBaseEntityTypeName->text();
}
