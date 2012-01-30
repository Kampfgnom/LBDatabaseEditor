#ifndef LBGUI_STORAGEWIDGET_H
#define LBGUI_STORAGEWIDGET_H

#include <LBGui/LBGui.h>

class QListWidget;

namespace LBDatabase {
class Storage;
}

namespace LBGui {

class StorageWidget : public TabWidget
{
    Q_OBJECT
public:
    explicit StorageWidget(QWidget *parent = 0);

    void setStorage(LBDatabase::Storage *storage);

private slots:
    void exportSource();

private:
    QListWidget *m_contextListWidget;
    QLineEdit *m_sourcePathLineEdit;
    LBDatabase::Storage *m_storage;
};

} // namespace LBGui

#endif // LBGUI_STORAGEWIDGET_H
