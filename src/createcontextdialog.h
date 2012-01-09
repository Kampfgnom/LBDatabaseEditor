#ifndef CREATECONTEXTDIALOG_H
#define CREATECONTEXTDIALOG_H

#include <QDialog>

namespace Ui {
    class CreateContextDialog;
}

class CreateContextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateContextDialog(QWidget *parent = 0);
    ~CreateContextDialog();

    QString contextName() const;

    QString baseEntityTypeName() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CreateContextDialog *ui;
};

#endif // CREATECONTEXTDIALOG_H
