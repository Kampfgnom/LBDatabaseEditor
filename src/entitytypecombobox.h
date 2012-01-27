#ifndef ENTITYTYPECOMBOBOX_H
#define ENTITYTYPECOMBOBOX_H

#include <QComboBox>

namespace LBDatabase {
class EntityType;
class Context;
}

class EntityTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit EntityTypeComboBox(QList<LBDatabase::EntityType*> types, QWidget *parent = 0);

    explicit EntityTypeComboBox(QList<LBDatabase::Context*> contexts, QWidget *parent = 0);

    LBDatabase::EntityType* currentItem();

    void setEntityTypes(QList<LBDatabase::EntityType*> types);

    void setCurrentEntityType(LBDatabase::EntityType* type);

signals:

    void currentEntityTypeChanged();

public slots:

private slots:
    void onCurrentEntityTypeChanged(int index);

private:
    void updateComboBox();

    QList<LBDatabase::EntityType*> m_types;
    LBDatabase::EntityType* m_selectedType;

};

#endif // ENTITYTYPECOMBOBOX_H
