#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <LBGui/LBGui.h>

namespace LBDatabase {
class Database;
class Table;
class Storage;
class Context;
}

namespace LBGui {

class DatabaseEditorController;
class DatabaseEditorActions;
class DatabaseEditorSidebar;
class RecentFilesManager;
class ToolBar;
class DatabaseWidget;
class TableWidget;
class StorageWidget;
class ContextWidget;

class DatabaseEditor : public MainWindow
{
    Q_OBJECT

public:
    explicit DatabaseEditor(QWidget *parent = 0);

    DatabaseEditorSidebar *dbeSidebar() const;

    RecentFilesManager *recentFilesManager() const;

    TableWidget *tableWidget() const;

    DatabaseEditorController *controller() const;
    DatabaseEditorActions *actions() const;

    void showDatabase(LBDatabase::Database *database);
    void showTable(LBDatabase::Table *table);

    void showStorage(LBDatabase::Storage *storage);
    void showContext(LBDatabase::Context *context);

    void closeEvent(QCloseEvent *event);

protected slots:
    friend class DatabaseEditorController;

    void reflectCurrentDatabaseDirtyState();

private:
    void createSideBar();
    void createMenuBar();
    void createToolBar();

    DatabaseEditorController *m_controller;
    DatabaseEditorActions *m_actions;
    RecentFilesManager *m_recentFiles;

    ToolBar *m_toolBar;

    DatabaseWidget *m_databaseWidget;
    TableWidget *m_tableWidget;

    StorageWidget *m_storageWidget;
    ContextWidget *m_contextWidget;
};

} //namespace LBGui

#endif // DATABASEWINDOW_H
