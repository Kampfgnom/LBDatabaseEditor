#ifndef CREATETABLEDIALOG_H
#define CREATETABLEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateTableDialog;
}

class CreateTableDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateTableDialog(QWidget *parent = 0);
    ~CreateTableDialog();

    QString name() const;
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CreateTableDialog *ui;
};

#endif // CREATETABLEDIALOG_H
