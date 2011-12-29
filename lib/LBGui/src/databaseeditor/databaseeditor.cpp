#include "databaseeditor.h"

#include "databaseeditorcontroller.h"
#include "databaseeditoractions.h"
#include "databaseeditorsidebar.h"
#include "databasewidget.h"
#include "tablewidget.h"

#include <mainwindow/menubar.h>
#include <mainwindow/sidebar/sidebarchildcategorie.h>
#include <mainwindow/toolbar.h>
#include <shared/action.h>
#include <shared/actionsmanager.h>
#include <shared/recentfilesmanager.h>

#include <LBDatabase/LBDatabase.h>

#include <QVBoxLayout>
#include <QPushButton>
#include <QToolBar>
#include <QStackedWidget>
#include <QFile>
#include <QSettings>
#include <QFileInfo>

namespace LBGui {

DatabaseEditor::DatabaseEditor(QWidget *parent) :
    MainWindow(parent),
    m_controller(new DatabaseEditorController(this)),
    m_actions(new DatabaseEditorActions(m_controller)),
    m_recentFiles(new RecentFilesManager(this)),
    m_toolBar(new ToolBar(this)),
    m_databaseWidget(new DatabaseWidget()),
    m_tableWidget(new TableWidget())
{
    setSaveSettings(true);
    setSettingsName(QLatin1String("DatabaseEditor"));

    m_centralViewStackedWidget->addWidget(m_databaseWidget);
    m_centralViewStackedWidget->addWidget(m_tableWidget);

    // Recent files
    m_recentFiles->setSettingsName(m_settingsName+QLatin1String("/RecentFiles"));
    m_recentFiles->populateFromSettings();
    connect(m_recentFiles, SIGNAL(fileTriggered(QString)), m_controller, SLOT(openDatabase(QString)));

    // MenuBar
    createMenuBar();

    // SideBar
    createSideBar();

    // ToolBar
    createToolBar();

    setTitle(tr("Database Editor"));
    restoreSettings();

    m_menuBar->addWindow(this);
}

DatabaseEditorSidebar *DatabaseEditor::dbeSidebar() const
{
    return static_cast<DatabaseEditorSidebar*>(m_leftSideBar);
}

RecentFilesManager *DatabaseEditor::recentFilesManager() const
{
    return m_recentFiles;
}

DatabaseEditorController *DatabaseEditor::controller() const
{
    return m_controller;
}

void DatabaseEditor::showCategorieWidget(SidebarChildCategorie *categorie)
{
    if(categorie->level() == 1) {
        LBDatabase::Database *database = categorie->data(SidebarChildCategorie::CustomDataRole).value<LBDatabase::Database *>();
        m_databaseWidget->setDatabase(database);
        m_centralViewStackedWidget->setCurrentWidget(m_databaseWidget);
    }
    else if(categorie->level() == 2) {
        LBDatabase::Table *table = categorie->data(SidebarChildCategorie::CustomDataRole).value<LBDatabase::Table *>();
        m_tableWidget->setTable(table);
        m_centralViewStackedWidget->setCurrentWidget(m_tableWidget);
    }
}

void DatabaseEditor::createSideBar()
{
    LBGui::DatabaseEditorSidebar* sidebar = new LBGui::DatabaseEditorSidebar(this);
    sidebar->setStyle(LBGui::Sidebar::MacOSLionMailStyle);

    connect(sidebar, SIGNAL(categorieChanged(::LBGui::SidebarChildCategorie*)),
            this,    SLOT(showCategorieWidget(::LBGui::SidebarChildCategorie*)));

    sidebar->setSelectedCategorie(0,0);
    sidebar->expandAll();
    setLeftSideBar(sidebar);
}

void DatabaseEditor::createMenuBar()
{
    m_menuBar->addAction(tr("File"),m_actions->openDatabaseAction());
    m_menuBar->addMenu(tr("File"), m_recentFiles->recentFilesMenu());

    m_menuBar->addMenu(m_menuBar->windowMenu());
    m_menuBar->addMenu(m_menuBar->helpMenu());
}

void DatabaseEditor::createToolBar()
{
    m_toolBar->addAction(m_actions->openDatabaseAction());
    addToolBar(m_toolBar);
    setUnifiedTitleAndToolBarOnMac(true);
}

} //namespace Gui
