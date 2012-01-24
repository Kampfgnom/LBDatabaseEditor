#ifndef EDITATTRIBUTEWIDGET_H
#define EDITATTRIBUTEWIDGET_H

#include <QWidget>

namespace Ui {
    class EditAttributeWidget;
}

namespace LBDatabase{
    class Attribute;
}

class EditAttributeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditAttributeWidget(LBDatabase::Attribute* attribute, QWidget *parent = 0);
    ~EditAttributeWidget();

private:
    void updateWidget();

    Ui::EditAttributeWidget *ui;

    LBDatabase::Attribute* m_attribute;
};

#endif // EDITATTRIBUTEWIDGET_H
