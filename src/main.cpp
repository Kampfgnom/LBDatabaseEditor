#include <QtGui/QApplication>

#include <LBDatabase/LBDatabase.h>
#include <LBGui/LBGui.h>

#include "database/company.h"

#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LBGUI_INIT_RESOURCES;

    QApplication::setApplicationName(QLatin1String("LBDatabase Editor"));
    QApplication::setOrganizationName(QLatin1String("LBProductions"));
    
    LBGui::DatabaseEditor editor;
    editor.show();

    return a.exec();
}
