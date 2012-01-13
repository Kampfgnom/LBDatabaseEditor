#ifndef ENTITYTYPECOMBOBOX_H
#define ENTITYTYPECOMBOBOX_H

#include <QComboBox>

namespace LBDatabase {
class EntityType;
}

class EntityTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit EntityTypeComboBox(QList<LBDatabase::EntityType*> types, QWidget *parent = 0);

    LBDatabase::EntityType* currentItem();

signals:

    void currentEntityTypeChanged();

public slots:

private slots:
    void onCurrentEntityTypeChanged(int index);

private:
    void updateComboBox();

    LBDatabase::EntityType* m_selectedType;
    QList<LBDatabase::EntityType*> m_types;

};

#endif // ENTITYTYPECOMBOBOX_H
