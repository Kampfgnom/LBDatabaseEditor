#include "databaseeditoractions.h"

#include "databaseeditorcontroller.h"

#include <LBGui/LBGui.h>
#include <LBDatabase/LBDatabase.h>

#include <QFileInfo>

namespace LBGui {

DatabaseEditorActions::DatabaseEditorActions(DatabaseEditorController *controller) :
    QObject(controller),
    m_controller(controller)
{
    connect(controller, SIGNAL(currentDatabaseChanged(::LBDatabase::Database*)), this, SLOT(updateActions()));
    connect(controller, SIGNAL(currentTableChanged(::LBDatabase::Table*)), this, SLOT(updateActions()));

    m_openDatabaseAction = new Action(this);
    m_openDatabaseAction->setText(tr("&Open database"));
    m_openDatabaseAction->setShortcut(QKeySequence::Open);
    connect(m_openDatabaseAction, SIGNAL(triggered()), m_controller, SLOT(openDatabase()));

    m_closeDatabaseAction = new Action(this);
    m_closeDatabaseAction->setText(tr("C&lose database"));
    m_closeDatabaseAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_W);
    m_closeDatabaseAction->setEnabled(false);
    connect(m_closeDatabaseAction, SIGNAL(triggered()), m_controller, SLOT(closeDatabase()));

    m_saveDatabaseAction = new Action(this);
    m_saveDatabaseAction->setText(tr("&Save"));
    m_saveDatabaseAction->setShortcut(QKeySequence::Save);
    m_saveDatabaseAction->setEnabled(false);
    connect(m_saveDatabaseAction, SIGNAL(triggered()), m_controller, SLOT(saveDatabase()));

    m_insertRowAction = new Action(this);
    m_insertRowAction->setText(tr("&Insert Row..."));
    m_insertRowAction->setEnabled(false);
    connect(m_insertRowAction, SIGNAL(triggered()), m_controller, SLOT(appendRow()));

    m_createTableAction = new Action(this);
    m_createTableAction->setText(tr("&Create Table..."));
    m_createTableAction->setEnabled(false);
    connect(m_createTableAction, SIGNAL(triggered()), m_controller, SLOT(createTable()));

    m_editTableAction = new Action(this);
    m_editTableAction->setText(tr("&Edit Table..."));
    m_editTableAction->setEnabled(false);
    connect(m_editTableAction, SIGNAL(triggered()), m_controller, SLOT(editTable()));
}

Action *DatabaseEditorActions::openDatabaseAction() const
{
    return m_openDatabaseAction;
}

Action *DatabaseEditorActions::closeDatabaseAction() const
{
    return m_closeDatabaseAction;
}

Action *DatabaseEditorActions::saveDatabaseAction() const
{
    return m_saveDatabaseAction;
}

Action *DatabaseEditorActions::insertRowAction() const
{
    return m_insertRowAction;
}

Action *DatabaseEditorActions::createTableAction() const
{
    return m_createTableAction;
}

Action *DatabaseEditorActions::editTableAction() const
{
    return m_editTableAction;
}

void DatabaseEditorActions::updateActions()
{
    m_closeDatabaseAction->setEnabled(m_controller->currentDatabase() != 0);
    m_saveDatabaseAction->setEnabled(m_controller->currentDatabase() != 0 && m_controller->currentDatabase()->isDirty());
    m_createTableAction->setEnabled(m_controller->currentDatabase() != 0);
    m_insertRowAction->setEnabled(m_controller->currentTable() != 0);
    m_editTableAction->setEnabled(m_controller->currentTable() != 0);

    QString closeText = tr("Close Database");
    if(m_controller->currentDatabase()) {
        closeText = tr("C&lose \"")+QFileInfo(m_controller->currentDatabase()->fileName()).fileName()+tr("\"");
    }
    m_closeDatabaseAction->setText(closeText);
}

} // namespace LBGUI
