#ifndef LBGUI_DATABASEEDITORACTIONS_H
#define LBGUI_DATABASEEDITORACTIONS_H

#include <QObject>

namespace LBGui {

class Action;
class DatabaseEditorController;

class DatabaseEditorActions : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseEditorActions(DatabaseEditorController *controller);
    
    Action *openDatabaseAction() const;
    Action *closeDatabaseAction() const;
    Action *saveDatabaseAction() const;
    Action *insertRowAction() const;
    Action *createTableAction() const;
    Action *editTableAction() const;

public slots:
    void updateActions();

private:
    DatabaseEditorController *m_controller;

    Action *m_openDatabaseAction;
    Action *m_closeDatabaseAction;
    Action *m_saveDatabaseAction;
    Action *m_createTableAction;
    Action *m_insertRowAction;
    Action *m_editTableAction;
    
};

} // namespace LBGUI

#endif // LBGUI_DATABASEEDITORACTIONS_H
