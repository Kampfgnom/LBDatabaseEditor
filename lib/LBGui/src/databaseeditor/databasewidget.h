#ifndef LBGUI_DATABASEWIDGET_H
#define LBGUI_DATABASEWIDGET_H

#include <widgets/tabwidget.h>

class QListWidget;

namespace LBDatabase {
class Database;
}

namespace LBGui {

class DatabaseWidget : public TabWidget
{
    Q_OBJECT
public:
    explicit DatabaseWidget(QWidget *parent = 0);

    void setDatabase(LBDatabase::Database *database);
    
private:
    QListWidget *m_tablesListWidget;
};

} // namespace LBGui

#endif // LBGUI_DATABASEWIDGET_H
