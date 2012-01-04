#include "databaseeditorsidebar.h"

#include "databaseeditor.h"
#include "databaseeditorcontroller.h"
#include "databasewidget.h"
#include "tablewidget.h"

#include <LBGui/LBGui.h>
#include <LBDatabase/LBDatabase.h>

#include <QFileInfo>

namespace LBGui {

DatabaseEditorSidebar::DatabaseEditorSidebar(DatabaseEditor *mainWindow) :
    Sidebar(mainWindow),
    m_databaseCategories(QHash<LBDatabase::Database*, SidebarChildCategorie*>())
{
    addParentCategorie("Databases");
    connect(m_treeView,SIGNAL(categorieChanged(::LBGui::SidebarChildCategorie*)),this, SLOT(onCategorieChanged(::LBGui::SidebarChildCategorie*)));
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

    connect(database, SIGNAL(dirtyChanged(bool)), this, SLOT(onDirtyStateChanged(bool)));

    m_treeView->setSelectedIndex(0, cat->index().row());
    expandAll();
    return cat;
}

void DatabaseEditorSidebar::setSelectedDatabase(LBDatabase::Database *database)
{
    SidebarChildCategorie *cat = m_databaseCategories.value(database);

    m_treeView->setSelectedIndex(0, cat->index().row());
}

LBDatabase::Database *DatabaseEditorSidebar::selectedDatabase() const
{
    SidebarChildCategorie *cat = m_treeView->currentIndex().data(SidebarChildCategorie::SelfRole).value<SidebarChildCategorie*>();
    if(!cat) {
        return 0;
    }

    LBDatabase::Database *database = 0;
    if(cat->level() == 2) {
        database = cat->data(SidebarChildCategorie::CustomDataRole).value<LBDatabase::Table *>()->database();
    }
    else if(cat->level() == 1) {
        database = cat->data(SidebarChildCategorie::CustomDataRole).value<LBDatabase::Database *>();
    }

    return database;
}

void DatabaseEditorSidebar::closeDatabase(LBDatabase::Database *database)
{
    SidebarChildCategorie *cat = m_databaseCategories.value(database);
    m_databaseCategories.remove(database);
    removeCategorie(cat);
}

void DatabaseEditorSidebar::addTableCategorie(LBDatabase::Table *table)
{
    SidebarChildCategorie *cat = m_databaseCategories.value(table->database());
    int index = cat->index().row();
    SidebarChildCategorie *tableCat = addChildCategorie(0,index, table->name());
    tableCat->setData(QVariant::fromValue<LBDatabase::Table*>(table), SidebarChildCategorie::CustomDataRole);
    tableCat->setIcon(QIcon(":/databaseeditor/table"));
    m_treeView->setSelectedIndex(cat->index().row(),tableCat->index().row());
}

void DatabaseEditorSidebar::onCategorieChanged(SidebarChildCategorie *cat)
{
    if(cat->level() == 1) {
        emit databaseSelected(cat->data(SidebarChildCategorie::CustomDataRole).value<LBDatabase::Database *>());
    }
    else {
        emit tableSelected(cat->data(SidebarChildCategorie::CustomDataRole).value<LBDatabase::Table *>());
    }
}

void DatabaseEditorSidebar::onDirtyStateChanged(bool)
{
    LBDatabase::Database *database = static_cast<LBDatabase::Database *>(sender());
    if(database) {
        SidebarChildCategorie *cat = m_databaseCategories.value(database);
        if(cat) {
            QString text = QFileInfo(database->fileName()).fileName();
            if(database->isDirty()) {
                text += "*";
            }
            cat->setData( QVariant(text), SidebarChildCategorie::TitleRole);
        }
    }
}

} // namespace LBGui
