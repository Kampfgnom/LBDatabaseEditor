#ifndef LBGUI_DATABASEEDITORSIDEBAR_H
#define LBGUI_DATABASEEDITORSIDEBAR_H

#include <mainwindow/sidebar/sidebar.h>

#include <QHash>

namespace LBDatabase {
class Database;
}

namespace LBGui {

class DatabaseEditor;

class DatabaseEditorSidebar : public Sidebar
{
    Q_OBJECT
public:
    DatabaseEditorSidebar(DatabaseEditor *mainWindow);

    SidebarChildCategorie *addDatabaseCategorie(LBDatabase::Database* database);

private:
    QHash<LBDatabase::Database*, SidebarChildCategorie*> m_databaseCategories;
};

} // namespace LBGui

#endif // LBGUI_DATABASEEDITORSIDEBAR_H
