#ifndef LBGUI_DATABASEEDITORSIDEBAR_H
#define LBGUI_DATABASEEDITORSIDEBAR_H

#include <LBGui/LBGui.h>

#include <QHash>

namespace LBDatabase {
class Database;
class Table;
class Storage;
class Context;
}

namespace LBGui {

class DatabaseEditor;

class DatabaseEditorSidebar : public Sidebar
{
    Q_OBJECT
public:
    DatabaseEditorSidebar(DatabaseEditor *mainWindow);

    SidebarChildCategorie *addDatabaseCategorie(LBDatabase::Database* database);
    void closeDatabase(LBDatabase::Database *database);
    void addTableCategorie(LBDatabase::Table *table);

    LBDatabase::Database *selectedDatabase() const;
    void setSelectedDatabase(LBDatabase::Database *database);


    SidebarChildCategorie *addEntityStorageCategorie(LBDatabase::Storage *storage);


signals:
    void tableSelected(::LBDatabase::Table *table);
    void databaseSelected(::LBDatabase::Database *database);

    void storageSelected(::LBDatabase::Storage *storage);
    void contextSelected(::LBDatabase::Context *context);

private slots:
    void onCategorieChanged(::LBGui::SidebarChildCategorie* cat);
    void onDirtyStateChanged(bool);

private:
    QHash<LBDatabase::Database*, SidebarChildCategorie*> m_databaseCategories;
    QHash<LBDatabase::Storage*, SidebarChildCategorie*> m_storageCategories;
};

} // namespace LBGui

#endif // LBGUI_DATABASEEDITORSIDEBAR_H
