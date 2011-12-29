#include "databaseeditorsidebar.h"

#include "databaseeditor.h"
#include "databaseeditorcontroller.h"
#include "databasewidget.h"
#include "tablewidget.h"

#include <mainwindow/sidebar/sidebarchildcategorie.h>
#include <mainwindow/sidebar/sidebartreeview.h>
#include <shared/recentfilesmanager.h>

#include <LBDatabase/LBDatabase.h>

#include <QFileInfo>

namespace LBGui {

DatabaseEditorSidebar::DatabaseEditorSidebar(DatabaseEditor *mainWindow) :
    Sidebar(mainWindow),
    m_databaseCategories(QHash<LBDatabase::Database*, SidebarChildCategorie*>())
{
    addParentCategorie("Databases");
}

SidebarChildCategorie *DatabaseEditorSidebar::addDatabaseCategorie(LBDatabase::Database *database)
{
    SidebarChildCategorie *cat = addChildCategorie(0, QFileInfo(database->fileName()).fileName());
    cat->setData(QVariant::fromValue<LBDatabase::Database*>(database), SidebarChildCategorie::CustomDataRole);
    cat->setIcon(QIcon(":/databaseeditor/database"));
    m_databaseCategories.insert(database, cat);

    int index = cat->index().row();
    foreach(LBDatabase::Table *table, database->tables()) {
        SidebarChildCategorie *tableCat = addChildCategorie(0,index, table->name());
        tableCat->setData(QVariant::fromValue<LBDatabase::Table*>(table), SidebarChildCategorie::CustomDataRole);
        tableCat->setIcon(QIcon(":/databaseeditor/table"));
    }

    m_treeView->setSelectedIndex(0, cat->index().row());
    expandAll();
    return cat;
}

} // namespace LBGui
