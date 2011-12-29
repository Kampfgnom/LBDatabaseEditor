#include "databaseeditorcontroller.h"

#include "databaseeditor.h"
#include "databaseeditorsidebar.h"

#include <LBDatabase/LBDatabase.h>

#include <shared/global.h>
#include <shared/recentfilesmanager.h>

#include <QFileInfo>

namespace LBGui {

DatabaseEditorController::DatabaseEditorController(DatabaseEditor *databaseEditor) :
    QObject(databaseEditor),
    m_databasEditor(databaseEditor)
{
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

    LBDatabase::Database *database = LBDatabase::Database::instance(QFileInfo(fileName).fileName(), fileName);
    if(m_openDatabases.contains(database)) {
        return;
    }

    m_openDatabases.append(database);
    m_databasEditor->recentFilesManager()->addFile(fileName);
    m_databasEditor->dbeSidebar()->addDatabaseCategorie(database);
}

} // namespace LBGui
