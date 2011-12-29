#ifndef LBGUI_ATTRIBUTEEDITDIALOG_H
#define LBGUI_ATTRIBUTEEDITDIALOG_H

#include <QDialog>

#include <LBDatabase/LBDatabase.h>

namespace LBDatabase {
class AttributeMetaData;
}

namespace LBGui {

namespace Ui {
class DatabaseAttributeEditDialog;
}

class DatabaseAttributeEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DatabaseAttributeEditDialog(LBDatabase::DatabaseAttributeMetaData *metaData, QWidget *parent = 0);
    explicit DatabaseAttributeEditDialog(QWidget *parent = 0);
    ~DatabaseAttributeEditDialog();

    QString name() const;
    QString displayName() const;
    LBDatabase::DatabaseAttributeMetaData::SqlType sqlType() const;

private slots:
    void saveMetaData();

private:
    Ui::DatabaseAttributeEditDialog *ui;
    LBDatabase::AttributeMetaData *m_metaData;
};

} // namespace LBGui

#endif // LBGUI_ATTRIBUTEEDITDIALOG_H
