#ifndef ADDENTITYTYPEDIALOG_H
#define ADDENTITYTYPEDIALOG_H

#include <QDialog>

namespace Ui {
    class AddEntityTypeDialog;
}

namespace LBDatabase {
class Context;
}

class EntityTypeComboBox;

class AddEntityTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEntityTypeDialog(LBDatabase::Context* context, QWidget *parent = 0);
    ~AddEntityTypeDialog();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::AddEntityTypeDialog *ui;
    LBDatabase::Context* m_context;
    EntityTypeComboBox* m_parentComboBox;
};

#endif // ADDENTITYTYPEDIALOG_H
