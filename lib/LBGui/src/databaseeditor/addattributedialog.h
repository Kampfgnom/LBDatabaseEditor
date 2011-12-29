#ifndef LBGUI_ADDATTRIBUTEDIALOG_H
#define LBGUI_ADDATTRIBUTEDIALOG_H

#include <QDialog>

namespace LBDatabase {
class Table;
}

namespace LBGui {

namespace Ui {
class AddAttributeDialog;
}

class DatabaseAttributeEditDialog;

class AddAttributeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddAttributeDialog(LBDatabase::Table *table, QWidget *parent = 0);
    ~AddAttributeDialog();
    
private slots:
    void addDatabaseAttribute();

private:
    Ui::AddAttributeDialog *ui;
    DatabaseAttributeEditDialog *m_databaseEditDialog;

    LBDatabase::Table *m_table;
};


} // namespace LBGui
#endif // LBGUI_ADDATTRIBUTEDIALOG_H
