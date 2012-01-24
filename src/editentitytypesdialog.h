#ifndef EDITENTITYTYPESDIALOG_H
#define EDITENTITYTYPESDIALOG_H

#include <QDialog>

namespace Ui {
    class EditEntityTypesDialog;
}

namespace LBDatabase {
class Context;
class EntityType;
}

class EntityTypeComboBox;
class PropertyComboBox;

class EditEntityTypesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditEntityTypesDialog(LBDatabase::Context* context, QWidget *parent = 0);
    ~EditEntityTypesDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void onCurrentEntityTypeChanged();

    void onSelectedAttributeChanged();

    void onSelectedRelationChanged();

    void fillDialogWithEntityType(LBDatabase::EntityType* type);

private:
    void clearAttributesAndRelationsLayouts();

    Ui::EditEntityTypesDialog *ui;

    LBDatabase::Context* m_context;
    LBDatabase::EntityType* m_entityType;

    EntityTypeComboBox* m_entityTypeBox;
    EntityTypeComboBox* m_entityTypeParentBox;

    PropertyComboBox* m_attributeBox;
    PropertyComboBox* m_relationsBox;
};

#endif // EDITENTITYTYPESDIALOG_H
