#ifndef LBGUI_H
#define LBGUI_H

#include <LBGui/databaseeditor/databaseeditor.h>

#define LBGUI_INIT_RESOURCES \
    Q_INIT_RESOURCE(tabwidget); \
    Q_INIT_RESOURCE(sidebar); \
    Q_INIT_RESOURCE(databaseeditor); \
    Q_INIT_RESOURCE(groupbox); \
    Q_INIT_RESOURCE(pushbutton); \
    Q_INIT_RESOURCE(listwidget); \
    Q_INIT_RESOURCE(treeview)

#endif // LBGUI_H
