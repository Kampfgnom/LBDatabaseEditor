#include "columneditline.h"

#include <LBDatabase/LBDatabase.h>

#include <QGridLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>

namespace LBGui {

class ColumnEditLinePrivate {
    ColumnEditLinePrivate() :
        column(0),
        table(0),
        valid(true),
        markedForDeletion(false)
    {}

    void init();

    ColumnEditLine * q_ptr;
    Q_DECLARE_PUBLIC(ColumnEditLine)

    LBDatabase::Column *column;
    LBDatabase::Table *table;
    QLineEdit *lineEditName;
    QComboBox *comboBoxType;
    QCheckBox *checkBoxDelete;
    QLabel *warningLabel;
    QPushButton *removeButton;
    bool valid;
    bool markedForDeletion;
};

void ColumnEditLinePrivate::init()
{
    Q_Q(ColumnEditLine);

    QRegExp rx("^[A-Za-z].*");
    QValidator *validator = new QRegExpValidator(rx, q);

    lineEditName = new QLineEdit(q);
    lineEditName->setValidator(validator);
    comboBoxType = new QComboBox(q);
    comboBoxType->addItems(LBDatabase::Column::typeNames());
    comboBoxType->setEnabled(true);
    checkBoxDelete = new QCheckBox(QObject::tr("Delete"), q);
    checkBoxDelete->setVisible(false);
    removeButton = new QPushButton(QObject::tr("Remove"),q);
    removeButton->setVisible(true);
    warningLabel = new QLabel(q);
    warningLabel->setStyleSheet(QLatin1String("QLabel { color:red; font-size: 10px; }"));
    warningLabel->setVisible(false);

    QObject::connect(lineEditName, SIGNAL(textChanged(QString)), q, SLOT(checkValues()));
    QObject::connect(checkBoxDelete, SIGNAL(toggled(bool)), q, SLOT(markForDeletion(bool)));
    QObject::connect(removeButton, SIGNAL(clicked()), q, SIGNAL(removed()));

    QGridLayout *layout = new QGridLayout(q);
    layout->addWidget(lineEditName,0,0);
    layout->addWidget(comboBoxType,0,1);
    layout->addWidget(checkBoxDelete,0,2);
    layout->addWidget(removeButton,0,3);
    layout->addWidget(warningLabel,1,0,1,4);
    layout->setSpacing(5);
    layout->setContentsMargins(0,0,0,0);
    q->setLayout(layout);
}

ColumnEditLine::ColumnEditLine(QWidget *parent) :
    QWidget(parent),
    d_ptr(new ColumnEditLinePrivate)
{
    Q_D(ColumnEditLine);
    d->q_ptr = this;
    d->init();
    setColumn(0);
}

ColumnEditLine::ColumnEditLine(LBDatabase::Column *column, QWidget *parent) :
    QWidget(parent),
    d_ptr(new ColumnEditLinePrivate)
{
    Q_D(ColumnEditLine);
    d->q_ptr = this;
    d->init();
    setColumn(column);
}

ColumnEditLine::~ColumnEditLine()
{
    Q_D(ColumnEditLine);
    delete d;
}

void ColumnEditLine::setColumn(LBDatabase::Column *column)
{
    Q_D(ColumnEditLine);
    if(column == d->column)
        return;

    d->column = column;
    if(column) {
        d->lineEditName->setText(column->name());
        d->lineEditName->setReadOnly(column->name() == QLatin1String("id"));
        d->checkBoxDelete->setEnabled(column->name() != QLatin1String("id"));
        d->checkBoxDelete->setVisible(true);
        d->removeButton->setVisible(false);
        d->comboBoxType->setCurrentIndex(column->type());
        d->comboBoxType->setEnabled(false);
        setTable(column->table());
    }
    else {
        d->lineEditName->setText(QString());
        d->lineEditName->setReadOnly(false);
        d->checkBoxDelete->setVisible(false);
        d->removeButton->setVisible(true);
        d->comboBoxType->setCurrentIndex(0);
        d->comboBoxType->setEnabled(true);
        d->lineEditName->setFocus();
    }
    checkValues();
}

void ColumnEditLine::setTable(LBDatabase::Table *table)
{
    Q_D(ColumnEditLine);
    if(table == d->table)
        return;

    d->table = table;
}

QString ColumnEditLine::columnName() const
{
    Q_D(const ColumnEditLine);
    return d->lineEditName->text();
}

int ColumnEditLine::columnType() const
{
    Q_D(const ColumnEditLine);
    return d->comboBoxType->currentIndex();
}

bool ColumnEditLine::markedForDeletion() const
{
    Q_D(const ColumnEditLine);
    return d->markedForDeletion;
}

void ColumnEditLine::setMessage(const QString &message)
{
    Q_D(ColumnEditLine);
    if(message == d->warningLabel->text())
        return;

    d->warningLabel->setText(message);
}

bool ColumnEditLine::isValid() const
{
    Q_D(const ColumnEditLine);
    return d->valid;
}

void ColumnEditLine::saveChanges()
{
    Q_D(ColumnEditLine);

    if(!d->column && d->table && !columnName().isEmpty()) {
        setColumn(d->table->addColumn(columnName(), LBDatabase::Column::typeToName(static_cast<LBDatabase::Column::Type>(columnType()))));
    }

    if(d->column) {
        if(d->markedForDeletion) {
            setVisible(false);
            d->column->table()->removeColumn(d->column->name());
            deleteLater();
        }
        else {
            d->column->table()->changeColumnName(d->column->name(), columnName());
        }
    }
}

void ColumnEditLine::markForDeletion(bool marked)
{
    Q_D(ColumnEditLine);
    if(marked == d->markedForDeletion)
        return;

    d->lineEditName->setEnabled(!marked);
    //d->comboBoxType->setEnabled(!marked);
    d->markedForDeletion = marked;
}

void ColumnEditLine::checkValues()
{
    Q_D(ColumnEditLine);
    if(
        (d->column && d->column->name() != d->lineEditName->text() &&
         d->column->table()->columnNames().contains(d->lineEditName->text(), Qt::CaseInsensitive))

            ||

        (!d->column && d->table && d->table->columnNames().contains(d->lineEditName->text()))
      )
    {

        d->warningLabel->setText(tr("Column name already exists"));
        d->warningLabel->setVisible(true);
        d->lineEditName->setStyleSheet(QLatin1String("QLineEdit { border: 1px solid red; }"));
        this->layout()->invalidate();
        setValid(false);
    }
    else if(d->column && d->lineEditName->text().isEmpty()) {
        d->warningLabel->setText(tr("Emtpy column names are not allowed."));
        d->warningLabel->setVisible(true);
        d->lineEditName->setStyleSheet(QLatin1String("QLineEdit { border: 1px solid red; }"));
        this->layout()->invalidate();
        setValid(false);
    }
    else {
        d->warningLabel->setVisible(false);
        d->lineEditName->setStyleSheet(QString());
        setValid(true);
    }
}

void ColumnEditLine::setValid(bool valid)
{
    Q_D(ColumnEditLine);
    if(valid == d->valid)
        return;
    d->valid = valid;
    emit validChanged(valid);
}

} // namespace LBGui
