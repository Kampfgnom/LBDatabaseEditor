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

private:
    QListWidget *m_contextListWidget;
};

} // namespace LBGui

#endif // LBGUI_STORAGEWIDGET_H
