#ifndef EDITRELATIONWIDGET_H
#define EDITRELATIONWIDGET_H

#include <QWidget>

namespace Ui {
    class EditRelationWidget;
}

namespace LBDatabase{
    class Relation;
}

class EntityTypeComboBox;

class EditRelationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditRelationWidget(LBDatabase::Relation* relation, QWidget *parent = 0);
    ~EditRelationWidget();

private slots:
    void on_lineEditDisplayLeft_editingFinished();

    void on_lineEditDisplayRight_editingFinished();

    void on_pushButton_clicked();

private:
    void updateWidget();

    void setCardinality(int cardinality);

    int m_cardinalityCounter;

    Ui::EditRelationWidget *ui;

    LBDatabase::Relation* m_relation;

    EntityTypeComboBox* m_leftEntityBox;
    EntityTypeComboBox* m_rightEntityBox;
};

#endif // EDITRELATIONWIDGET_H
