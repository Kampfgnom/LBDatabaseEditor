#ifndef LBGUI_DATABASEEDITORCONTROLLER_H
#define LBGUI_DATABASEEDITORCONTROLLER_H

#include <QObject>

#include <QHash>

namespace LBDatabase {
class Database;
class Table;
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

    bool close();

public slots:
    void openDatabase();
    void openDatabase(const QString &fileName);

    void closeDatabase();
    void saveDatabase();

    void appendRow();

    void createTable();
    void editTable();

    void showTable(::LBDatabase::Table *table);
    void showDatabase(::LBDatabase::Database *database);

signals:
    void currentDatabaseChanged(::LBDatabase::Database *database);
    void currentTableChanged(::LBDatabase::Table *table);

private:
    void setCurrentDatabase(::LBDatabase::Database *database);
    void setCurrentTable(::LBDatabase::Table *table);

    DatabaseEditor *m_databaseEditor;

    LBDatabase::Database *m_currentDatabase;
    LBDatabase::Table *m_currentTable;

    QList<LBDatabase::Database *> m_databases;
    QHash<LBDatabase::Database *, AutosaveFile *> m_autosaveFiles;
};

} // namespace LBGui

#endif // LBGUI_DATABASEEDITORCONTROLLER_H
