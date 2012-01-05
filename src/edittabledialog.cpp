#include "edittabledialog.h"

#include "editcolumnwidget.h"

#include <LBDatabase/LBDatabase.h>

#include <QComboBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace LBGui {

class EditTableDialogPrivate {
    EditTableDialogPrivate() : table(0), lineEditName(0), q_ptr(0) {}

    void init();
    void save();

    LBDatabase::Table *table;
    QLineEdit* lineEditName;
    EditTableDialog * q_ptr;
    QList<EditColumnWidget *> columnEditLines;
    QFormLayout *formLayout;
    QDialogButtonBox *buttonBox;

    Q_DECLARE_PUBLIC(EditTableDialog)
};

void EditTableDialogPrivate::init()
{
    Q_Q(EditTableDialog);
    QVBoxLayout *layout = new QVBoxLayout(q);

    QWidget *widgetName = new QWidget(q);
    QHBoxLayout *layoutName = new QHBoxLayout(widgetName);
    widgetName->setLayout(layoutName);
    QLabel *labelName = new QLabel(QObject::tr("Table Name:"), widgetName);
    lineEditName = new QLineEdit(widgetName);
    lineEditName->setReadOnly(true);
    layoutName->addWidget(labelName);
    layoutName->addWidget(lineEditName);
    layout->addWidget(widgetName);

    QWidget *columns = new QWidget(q);
    formLayout = new QFormLayout(columns);
    formLayout->setSpacing(5);
    columns->setLayout(formLayout);
    layout->addWidget(columns);

    buttonBox = new QDialogButtonBox(q);

    QPushButton *addColumnButton = new QPushButton(QObject::tr("&Add Column"));
    QObject::connect(addColumnButton, SIGNAL(clicked()), q, SLOT(addColumn()));

    buttonBox->addButton(addColumnButton, QDialogButtonBox::ActionRole);
    buttonBox->setStandardButtons(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    QObject::connect(buttonBox, SIGNAL(accepted()), q, SLOT(save()));
    QObject::connect(buttonBox, SIGNAL(rejected()), q, SLOT(reject()));
    layout->addWidget(buttonBox);

    q->setLayout(layout);
    q->setWindowModality(Qt::WindowModal);
    q->setAttribute(Qt::WA_DeleteOnClose);
}

void EditTableDialogPrivate::save()
{
    Q_Q(EditTableDialog);

    foreach(EditColumnWidget *columnEditLine, columnEditLines) {
        columnEditLine->saveChanges();
    }

    q->accept();
}

EditTableDialog::EditTableDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new EditTableDialogPrivate)
{
    Q_D(EditTableDialog);
    d->q_ptr = this;
    d->init();
    setTable(0);
}

EditTableDialog::EditTableDialog(LBDatabase::Table *table, QWidget *parent) :
    QDialog(parent),
    d_ptr(new EditTableDialogPrivate)
{
    Q_D(EditTableDialog);
    d->q_ptr = this;
    d->init();
    setTable(table);
}

EditTableDialog::~EditTableDialog()
{
    Q_D(EditTableDialog);
    delete d;
}

void EditTableDialog::setTable(LBDatabase::Table *table)
{
    Q_D(EditTableDialog);
    if(table == d->table)
        return;

    QLayoutItem *child;
    while (!d->formLayout->children().isEmpty() && (child = d->formLayout->takeAt(0)) != 0) {
      delete child;
    }
    while (!d->columnEditLines.isEmpty()) {
      delete d->columnEditLines.takeAt(0);
    }

    if(table) {
        d->lineEditName->setText(table->name());

        foreach(LBDatabase::Column *column, table->columns()) {
            EditColumnWidget *columnEditLine = addColumn();
            columnEditLine->setColumn(column);
        }
    }

    d->table = table;
}

void EditTableDialog::save()
{
    Q_D(EditTableDialog);
    d->save();
}

EditColumnWidget *EditTableDialog::addColumn()
{
    Q_D(EditTableDialog);
    EditColumnWidget *columnEditLine = new EditColumnWidget(this);
    columnEditLine->setTable(d->table);
    connect(columnEditLine, SIGNAL(validChanged(bool)), d->buttonBox->button(QDialogButtonBox::Save), SLOT(setEnabled(bool)));
    connect(columnEditLine, SIGNAL(removed()), this, SLOT(removeColumn()));
    d->formLayout->addWidget(columnEditLine);
    d->columnEditLines.append(columnEditLine);
    return columnEditLine;
}

void EditTableDialog::removeColumn()
{
    Q_D(EditTableDialog);
    EditColumnWidget *columnEditLine = static_cast<EditColumnWidget *>(sender());
    d->formLayout->removeWidget(columnEditLine);
    columnEditLine->setVisible(false);
    d->columnEditLines.removeAll(columnEditLine);
}


} // namespace LBGui
