#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <LBGui/LBGui.h>

namespace LBDatabase {
class Database;
class Table;
}

namespace LBGui {

class DatabaseEditorController;
class DatabaseEditorActions;
class DatabaseEditorSidebar;
class RecentFilesManager;
class ToolBar;
class DatabaseWidget;
class TableWidget;

class DatabaseEditor : public MainWindow
{
    Q_OBJECT

public:
    explicit DatabaseEditor(QWidget *parent = 0);

    DatabaseEditorSidebar *dbeSidebar() const;

    RecentFilesManager *recentFilesManager() const;

    DatabaseEditorController *controller() const;
    DatabaseEditorActions *actions() const;

    void showDatabase(LBDatabase::Database *database);
    void showTable(LBDatabase::Table *table);

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
};

} //namespace LBGui

#endif // DATABASEWINDOW_H
