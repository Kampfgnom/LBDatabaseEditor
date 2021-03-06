#include "databaseeditorcontroller.h"

#include "databaseeditor.h"
#include "databaseeditorsidebar.h"
#include "databaseeditoractions.h"
#include "createtabledialog.h"
#include "edittabledialog.h"
#include "tablewidget.h"
#include "tableview.h"
#include "addentitytypedialog.h"
#include "createcontextdialog.h"
#include "editentitytypesdialog.h"

#include "model2/projectstatsstorage.h"
#include "model2/game.h"

#include <LBGui/LBGui.h>
#include <LBDatabase/LBDatabase.h>

#include <QFileInfo>
#include <QMessageBox>
#include <QElapsedTimer>

#include <QDateTime>
#include <QTime>

#include <QPushButton>

#include <QDebug>

namespace LBGui {

DatabaseEditorController::DatabaseEditorController(DatabaseEditor *databaseEditor) :
    QObject(databaseEditor),
    m_databaseEditor(databaseEditor),
    m_currentDatabase(0),
    m_currentTable(0),
    m_currentStorage(0),
    m_currentContext(0),
    m_databases(QList<LBDatabase::Database *>())
{
    connect(m_databaseEditor->dbeSidebar(), SIGNAL(databaseSelected(::LBDatabase::Database*)), this, SLOT(showDatabase(::LBDatabase::Database*)));
    connect(m_databaseEditor->dbeSidebar(), SIGNAL(tableSelected(::LBDatabase::Table*)), this, SLOT(showTable(::LBDatabase::Table*)));
    connect(m_databaseEditor->dbeSidebar(), SIGNAL(storageSelected(::LBDatabase::Storage*)), this, SLOT(showStorage(::LBDatabase::Storage*)));
    connect(m_databaseEditor->dbeSidebar(), SIGNAL(contextSelected(::LBDatabase::Context*)), this, SLOT(showContext(::LBDatabase::Context*)));
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

LBDatabase::Context *DatabaseEditorController::currentContext() const
{
    return m_currentContext;
}

LBDatabase::Storage *DatabaseEditorController::currentStorage() const
{
    return m_currentStorage;
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
                    m_autosaveFilesDatabase.value(database)->save();
                }
            }
            return true;
        }
    }
    return true;
}

void DatabaseEditorController::openFile()
{
    openFile(getOpenFileName(tr("Open File"), tr("Entity Storage (*.lbstorage);;Database Files (*.db);;All Files (*.*)")));
}

void DatabaseEditorController::importDatabase()
{
    QString databaseFileName = getOpenFileName(tr("Choose database"), tr("Database Files (*.db);;All Files (*.*)"));
    QString storageFileName = getSaveFileName(tr("Enter storage file name"), tr("Entity Storage (*.lbstorage);;All Files (*.*)"));

    LBDatabase::Storage::convertSqlliteDatabaseToStorage(databaseFileName, storageFileName);
    openFile(storageFileName);
}

void DatabaseEditorController::openFile(const QString &fileName)
{
    if(fileName.isNull() || fileName.isEmpty()) {
        return;
    }

    if(fileName.endsWith(".lbstorage")) {
        openEntityStorage(fileName);
    }
    else {
        openDatabase(fileName);
    }
}

void DatabaseEditorController::openEntityStorage(const QString &fileName)
{
    AutosaveFile *autosaveFile = AutosaveFile::instance(fileName);
    //LBDatabase::Storage *storage = LBDatabase::Storage::instance(autosaveFile->copyFileName());

    static QObject guard;
    ProjectStatsStorage *storage = new ProjectStatsStorage(autosaveFile->copyFileName(), &guard);

    if(m_storages.contains(storage)) {
//        m_databaseEditor->dbeSidebar()->setSelectedDatabase(database);
//        showDatabase(database);
        return;
    }

    QElapsedTimer timer;
    timer.start();
    storage->open();
    qDebug() << "Opening the storage" << fileName << "took "+QString::number(timer.elapsed())+"ms.";
    openDatabase(fileName);

//    LiveGame *game = static_cast<LiveGame *>(storage->gamesContext()->game(250));
//    foreach(Player *player, game->playersByPlacement()) {
//        qDebug() << player->displayName() << game->points(player) << game->placement(player);
//    }

//    LBDatabase::CppExporter exporter;
//    exporter.setStorage(storage);
//    exporter.setDirectory("/Users/niklas/Documents/Programming/LBDatabaseTest/LBDatabaseEditor/src/model2/");
//    exporter.exportCpp();

    //    connect(storage,SIGNAL(dirtyChanged(bool)),m_databaseEditor->actions(),SLOT(updateActions()));
//    connect(storage,SIGNAL(dirtyChanged(bool)),m_databaseEditor,SLOT(reflectCurrentDatabaseDirtyState()));
    m_storages.append(storage);
    m_databaseEditor->dbeSidebar()->addEntityStorageCategorie(storage);
//    m_databaseEditor->dbeSidebar()->setSelectedDatabase(database);
//    showDatabase(database);
}

void DatabaseEditorController::openDatabase(const QString &fileName)
{
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
    m_autosaveFilesDatabase.insert(database, autosaveFile);
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
        m_autosaveFilesDatabase.value(m_currentDatabase)->save();
        m_currentDatabase->setDirty(false);
    }
}

void DatabaseEditorController::appendRow()
{
    if(m_currentTable) {
        m_currentTable->appendRow();
    }
}

void DatabaseEditorController::deleteRow()
{
    if(m_currentTable) {
        LBDatabase::Row *row = m_databaseEditor->tableWidget()->tableView()->firstSelectedRow();
        if(row) {
            int id = m_databaseEditor->tableWidget()->tableView()->firstSelectedRow()->id();
            m_currentTable->deleteRow(id);
        }
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
    setCurrentStorage(0);
    setCurrentContext(0);
}

void DatabaseEditorController::showDatabase(LBDatabase::Database *database)
{
    m_databaseEditor->showDatabase(database);
    setCurrentTable(0);
    setCurrentDatabase(database);
    setCurrentStorage(0);
    setCurrentContext(0);
}

void DatabaseEditorController::showStorage(LBDatabase::Storage *storage)
{
    m_databaseEditor->showStorage(storage);
    setCurrentTable(0);
    setCurrentDatabase(0);
    setCurrentStorage(storage);
    setCurrentContext(0);
}

void DatabaseEditorController::showContext(LBDatabase::Context *context)
{
    m_databaseEditor->showContext(context);
    setCurrentTable(0);
    setCurrentDatabase(0);
    setCurrentStorage(context->storage());
    setCurrentContext(context);
}

void DatabaseEditorController::exportGraphviz()
{
    if(!m_currentStorage)
        return;

    LBDatabase::GraphvizExporter exporter;
    exporter.setStorage(m_currentStorage);
    QString fileName = getSaveFileName("Export", "Graphviz Document (*.dot files)");
    exporter.exportGraph(fileName);
}

void DatabaseEditorController::exportCpp()
{
    if(!m_currentStorage)
        return;

    LBDatabase::CppExporter exporter;
    QString directory = getSaveDirName("Export");
    exporter.setStorage(m_currentStorage);
    exporter.setDirectory(directory);
    exporter.exportCpp();
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

void DatabaseEditorController::setCurrentStorage(LBDatabase::Storage *storage)
{
    if(storage == m_currentStorage)
        return;
    m_currentStorage = storage;
    emit currentStorageChanged(storage);
}

void DatabaseEditorController::setCurrentContext(LBDatabase::Context *context)
{
    if(context == m_currentContext)
        return;
    m_currentContext = context;
    emit currentContextChanged(context);
}

void DatabaseEditorController::createContext()
{
    if(m_currentStorage){
        CreateContextDialog *d = new CreateContextDialog(m_databaseEditor);
        if(d->exec() == QDialog::Accepted) {
            m_currentStorage->addContext(d->contextName(),d->baseEntityTypeName());
        }
    }
}

void DatabaseEditorController::addEntityType()
{
    if(m_currentContext){
        AddEntityTypeDialog *d = new AddEntityTypeDialog(m_currentContext,m_databaseEditor);
        d->exec();
    }
}

void DatabaseEditorController::editEntityTypes(){
    if(m_currentContext){
        EditEntityTypesDialog *d = new EditEntityTypesDialog(m_currentContext,m_databaseEditor);
        d->exec();
    }
}

} // namespace LBGui
