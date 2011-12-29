#ifndef LBGUI_DATABASEEDITORCONTROLLER_H
#define LBGUI_DATABASEEDITORCONTROLLER_H

#include <QObject>

#include <QFile>

namespace LBDatabase {
class Database;
}

namespace LBGui {

class DatabaseEditor;

class DatabaseEditorController : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseEditorController(DatabaseEditor *databaseEditor);

public slots:
    void openDatabase();
    void openDatabase(const QString &fileName);

private:
    DatabaseEditor *m_databasEditor;

    QList<LBDatabase::Database *> m_openDatabases;
    
};

} // namespace LBGui

#endif // LBGUI_DATABASEEDITORCONTROLLER_H
