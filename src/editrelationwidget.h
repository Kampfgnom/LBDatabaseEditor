#ifndef EDITRELATIONWIDGET_H
#define EDITRELATIONWIDGET_H

#include <QWidget>

namespace Ui {
    class EditRelationWidget;
}

namespace LBDatabase{
    class Relation;
}

class EditRelationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditRelationWidget(LBDatabase::Relation* relation, QWidget *parent = 0);
    ~EditRelationWidget();

private:
    void updateWidget();

    Ui::EditRelationWidget *ui;

    LBDatabase::Relation* m_relation;
};

#endif // EDITRELATIONWIDGET_H
