#ifndef LBGUI_DATABASEEDITORCONTROLLER_H
#define LBGUI_DATABASEEDITORCONTROLLER_H

#include <QObject>

#include <QHash>

namespace LBDatabase {
class Database;
class Table;

class Storage;
class Context;
}

namespace LBGui {

class AutosaveFile;
class DatabaseEditor;

class DatabaseEditorController : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseEditorController(DatabaseEditor *databaseEditor);

    LBDatabase::Database *currentDatabase() const;
    LBDatabase::Table *currentTable() const;
    LBDatabase::Context *currentContext() const;
    LBDatabase::Storage *currentStorage() const;

    bool close();

public slots:
    void openFile();
    void importDatabase();
    void openFile(const QString &fileName);
    void openDatabase(const QString &fileName);
    void openEntityStorage(const QString &fileName);

    void closeDatabase();
    void saveDatabase();

    void appendRow();
    void deleteRow();

    void createTable();
    void editTable();

    void createContext();
    void addEntityType();
    void editEntityTypes();

    void showTable(::LBDatabase::Table *table);
    void showDatabase(::LBDatabase::Database *database);

    void showStorage(::LBDatabase::Storage *storage);
    void showContext(::LBDatabase::Context *context);

    void exportGraphviz();
    void exportCpp();

signals:
    void currentDatabaseChanged(::LBDatabase::Database *database);
    void currentTableChanged(::LBDatabase::Table *table);

    void currentStorageChanged(::LBDatabase::Storage *storage);
    void currentContextChanged(::LBDatabase::Context *context);

private:
    void setCurrentDatabase(::LBDatabase::Database *database);
    void setCurrentTable(::LBDatabase::Table *table);

    void setCurrentStorage(::LBDatabase::Storage *storage);
    void setCurrentContext(::LBDatabase::Context *context);

    DatabaseEditor *m_databaseEditor;

    LBDatabase::Database *m_currentDatabase;
    LBDatabase::Table *m_currentTable;

    LBDatabase::Storage *m_currentStorage;
    LBDatabase::Context *m_currentContext;

    QList<LBDatabase::Database *> m_databases;
    QHash<LBDatabase::Database *, AutosaveFile *> m_autosaveFilesDatabase;

    QList<LBDatabase::Storage *> m_storages;
    QHash<LBDatabase::Storage *, AutosaveFile *> m_autosaveFilesStorage;
};

} // namespace LBGui

#endif // LBGUI_DATABASEEDITORCONTROLLER_H
