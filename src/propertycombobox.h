#ifndef PROPERTYCOMBOBOX_H
#define PROPERTYCOMBOBOX_H

#include <QComboBox>

namespace LBDatabase {
class Property;
}

class PropertyComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit PropertyComboBox(QList<LBDatabase::Property*> properties, QWidget *parent = 0);

    LBDatabase::Property* currentItem();

    void setPropertys(QList<LBDatabase::Property*> properties);

signals:

    void currentPropertyChanged();

public slots:
    void onCurrentPropertyChanged(int index);

private:
    void updateComboBox();

    QList<LBDatabase::Property*> m_properties;
    LBDatabase::Property* m_selectedProperty;
};

#endif // PROPERTYCOMBOBOX_H
