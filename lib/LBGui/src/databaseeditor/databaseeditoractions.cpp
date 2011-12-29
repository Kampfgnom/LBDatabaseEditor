#include "databaseeditoractions.h"

#include "databaseeditorcontroller.h"

#include <shared/action.h>

namespace LBGui {

DatabaseEditorActions::DatabaseEditorActions(DatabaseEditorController *controller) :
    QObject(controller),
    m_controller(controller)
{
    m_openDatabaseAction = new Action(this);
    m_openDatabaseAction->setText(tr("&Open database"));
    m_openDatabaseAction->setShortcut(QKeySequence::Open);
    connect(m_openDatabaseAction, SIGNAL(triggered()), m_controller, SLOT(openDatabase()));
}

Action *DatabaseEditorActions::openDatabaseAction() const
{
    return m_openDatabaseAction;
}


} // namespace LBGUI
