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

private:
    DatabaseEditorController *m_controller;

    Action *m_openDatabaseAction;
    
};

} // namespace LBGUI

#endif // LBGUI_DATABASEEDITORACTIONS_H
