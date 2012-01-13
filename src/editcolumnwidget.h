#ifndef COLUMNEDITLINE_H
#define COLUMNEDITLINE_H

#include <QWidget>

namespace LBDatabase {
class Column;
class Table;
}

namespace LBGui {

class EditColumnWidgetPrivate;
class EditColumnWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditColumnWidget(LBDatabase::Column *column, QWidget *parent = 0);
    explicit EditColumnWidget(QWidget *parent = 0);
    ~EditColumnWidget();

    void setColumn(LBDatabase::Column *column);
    void setTable(LBDatabase::Table *table);
    bool isValid() const;
    QString columnName() const;
    int columnType() const;
    bool markedForDeletion() const;

    void setMessage(const QString &message);

public Q_SLOTS:
    void saveChanges();
    void markForDeletion(bool);
    void checkValues();

Q_SIGNALS:
    void validChanged(bool valid);
    void removed();

private:
    void setValid(bool valid);

    EditColumnWidgetPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(EditColumnWidget)
};

} // namespace LBGui

#endif // COLUMNEDITLINE_H
