#include <QtGui/QApplication>

#include <LBDatabase/LBDatabase.h>
#include <LBGui/LBGui.h>

#include "databaseeditor.h"
#include "databaseeditorcontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LBGUI_INIT_RESOURCES;

    QApplication::setApplicationName(QLatin1String("LBDatabase Editor"));
    QApplication::setOrganizationName(QLatin1String("LBProductions"));
    
    LBGui::DatabaseEditor editor;
    editor.show();
    //editor.controller()->openEntityStorage("/Users/niklas/Documents/Programming/LBDatabaseTest/LBDatabaseEditor/examples/projectstats.lbstorage");

    return a.exec();
}
