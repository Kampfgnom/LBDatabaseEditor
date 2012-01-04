#ifndef LBGUI_DATABASEEDITORSIDEBAR_H
#define LBGUI_DATABASEEDITORSIDEBAR_H

#include <LBGui/LBGui.h>

#include <QHash>

namespace LBDatabase {
class Database;
class Table;
}

namespace LBGui {

class DatabaseEditor;

class DatabaseEditorSidebar : public Sidebar
{
    Q_OBJECT
public:
    DatabaseEditorSidebar(DatabaseEditor *mainWindow);

    SidebarChildCategorie *addDatabaseCategorie(LBDatabase::Database* database);

    void setSelectedDatabase(LBDatabase::Database *database);

    LBDatabase::Database *selectedDatabase() const;

    void closeDatabase(LBDatabase::Database *database);

    void addTableCategorie(LBDatabase::Table *table);

signals:
    void tableSelected(::LBDatabase::Table *table);
    void databaseSelected(::LBDatabase::Database *database);

private slots:
    void onCategorieChanged(::LBGui::SidebarChildCategorie* cat);
    void onDirtyStateChanged(bool);

private:
    QHash<LBDatabase::Database*, SidebarChildCategorie*> m_databaseCategories;
};

} // namespace LBGui

#endif // LBGUI_DATABASEEDITORSIDEBAR_H
