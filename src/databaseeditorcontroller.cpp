#include "databaseeditorcontroller.h"

#include "databaseeditor.h"
#include "databaseeditorsidebar.h"
#include "databaseeditoractions.h"
#include "createtabledialog.h"
#include "edittabledialog.h"

#include <LBGui/LBGui.h>
#include <LBDatabase/LBDatabase.h>

#include <QFileInfo>
#include <QMessageBox>

namespace LBGui {

DatabaseEditorController::DatabaseEditorController(DatabaseEditor *databaseEditor) :
    QObject(databaseEditor),
    m_databaseEditor(databaseEditor),
    m_currentDatabase(0),
    m_currentTable(0),
    m_databases(QList<LBDatabase::Database *>())
{
    connect(m_databaseEditor->dbeSidebar(), SIGNAL(databaseSelected(::LBDatabase::Database*)), this, SLOT(showDatabase(::LBDatabase::Database*)));
    connect(m_databaseEditor->dbeSidebar(), SIGNAL(tableSelected(::LBDatabase::Table*)), this, SLOT(showTable(::LBDatabase::Table*)));
    connect(this, SIGNAL(currentDatabaseChanged(::LBDatabase::Database*)), m_databaseEditor, SLOT(reflectCurrentDatabaseDirtyState()));
}

LBDatabase::Database *DatabaseEditorController::currentDatabase() const
{
    return m_currentDatabase;
}

LBDatabase::Table *DatabaseEditorController::currentTable() const
{
    return m_currentTable;
}

bool DatabaseEditorController::close()
{
    bool confirm = false;
    foreach(LBDatabase::Database *database, m_databases) {
        confirm |= database->isDirty();
    }

    if(confirm) {
        QMessageBox msg(m_databaseEditor);
        msg.setInformativeText(tr("Some of your database files have unsaved changes."));
        msg.setText(tr("Do you want to save your changes?"));
        msg.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard);
        msg.setDefaultButton(QMessageBox::Save);
        msg.setIcon(QMessageBox::Warning);
        msg.setWindowModality(Qt::WindowModal);

        int ret = msg.exec();
        if(ret == QMessageBox::Discard) {
            return true;
        }
        else if(ret == QMessageBox::Cancel) {
            return false;
        }
        else if(ret == QMessageBox::Save) {
            foreach(LBDatabase::Database *database, m_databases) {
                if(database->isDirty()) {
                    m_autosaveFiles.value(database)->save();
                }
            }
            return true;
        }
    }
    return true;
}

void DatabaseEditorController::openDatabase()
{
    openDatabase(getOpenFileName(tr("Open Database"), tr("Database Files(*.db)")));
}

void DatabaseEditorController::openDatabase(const QString &fileName)
{
    if(fileName.isNull() || fileName.isEmpty()) {
        return;
    }

    AutosaveFile *autosaveFile = AutosaveFile::instance(fileName);
    LBDatabase::Database *database = LBDatabase::Database::instance(autosaveFile->copyFileName());
    if(m_databases.contains(database)) {
        m_databaseEditor->dbeSidebar()->setSelectedDatabase(database);
        showDatabase(database);
        return;
    }

    database->open();
    connect(database,SIGNAL(dirtyChanged(bool)),m_databaseEditor->actions(),SLOT(updateActions()));
    connect(database,SIGNAL(dirtyChanged(bool)),m_databaseEditor,SLOT(reflectCurrentDatabaseDirtyState()));
    m_databases.append(database);
    m_databaseEditor->recentFilesManager()->addFile(fileName);
    m_autosaveFiles.insert(database, autosaveFile);
    m_databaseEditor->dbeSidebar()->addDatabaseCategorie(database);
    m_databaseEditor->dbeSidebar()->setSelectedDatabase(database);
    showDatabase(database);
}

void DatabaseEditorController::closeDatabase()
{
    if(m_currentDatabase) {
        m_databases.removeAll(m_currentDatabase);
        m_databaseEditor->dbeSidebar()->closeDatabase(m_currentDatabase);
        m_databaseEditor->showDatabase(0);
        setCurrentDatabase(0);
        setCurrentTable(0);
    }
}

void DatabaseEditorController::saveDatabase()
{
    if(m_currentDatabase) {
        m_autosaveFiles.value(m_currentDatabase)->save();
        m_currentDatabase->setDirty(false);
    }
}

void DatabaseEditorController::appendRow()
{
    if(m_currentTable) {
        m_currentTable->appendRow();
    }
}

void DatabaseEditorController::createTable()
{
    if(m_currentDatabase) {
        CreateTableDialog *d = new CreateTableDialog(m_databaseEditor);
        if(d->exec() == QDialog::Accepted) {
            LBDatabase::Table *table = m_currentDatabase->createTable(d->name());
            m_databaseEditor->dbeSidebar()->addTableCategorie(table);
        }
    }
}

void DatabaseEditorController::editTable()
{
    if(m_currentTable) {
        EditTableDialog *d = new EditTableDialog(m_currentTable, m_databaseEditor);
        d->exec();
    }
}

void DatabaseEditorController::showTable(LBDatabase::Table *table)
{
    m_databaseEditor->showTable(table);
    setCurrentDatabase(table->database());
    setCurrentTable(table);
}

void DatabaseEditorController::showDatabase(LBDatabase::Database *database)
{
    m_databaseEditor->showDatabase(database);
    setCurrentTable(0);
    setCurrentDatabase(database);
}

void DatabaseEditorController::setCurrentDatabase(LBDatabase::Database *database)
{
    if(database == m_currentDatabase)
        return;
    m_currentDatabase = database;
    emit currentDatabaseChanged(database);
}

void DatabaseEditorController::setCurrentTable(LBDatabase::Table *table)
{
    if(table == m_currentTable)
        return;
    m_currentTable = table;
    emit currentTableChanged(table);
}

} // namespace LBGui
