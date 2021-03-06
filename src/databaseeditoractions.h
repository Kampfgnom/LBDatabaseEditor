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
    
    // Database
    Action *openDatabaseAction() const;
    Action *importDatabaseAction() const;
    Action *closeDatabaseAction() const;
    Action *saveDatabaseAction() const;
    Action *insertRowAction() const;
    Action *deleteRowAction() const;
    Action *createTableAction() const;
    Action *editTableAction() const;

    //Entity

    Action *createContextAction() const;
    Action *addEntityTypeAction() const;
    Action *editEntityTypesAction() const;

    Action *exportUmlGraphvizAction() const;
    Action *exportCppAction() const;

public slots:
    void updateActions();

private:
    DatabaseEditorController *m_controller;

    // Database
    Action *m_openDatabaseAction;
    Action *m_importDatabaseAction;
    Action *m_closeDatabaseAction;
    Action *m_saveDatabaseAction;
    Action *m_createTableAction;
    Action *m_insertRowAction;
    Action *m_deleteRowAction;
    Action *m_editTableAction;

    //Entity
    Action *m_createContextAction;
    Action *m_addEntityTypeAction;
    Action *m_editEntityTypesAction;

    Action *m_exportUmlGraphvizAction;

    Action *m_exportCppAction;

};

} // namespace LBGUI

#endif // LBGUI_DATABASEEDITORACTIONS_H
