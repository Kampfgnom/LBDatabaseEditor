#ifndef LBGUI_CONTEXTVIEW_H
#define LBGUI_CONTEXTVIEW_H

#include <LBGui/LBGui.h>

namespace LBDatabase {
class Entity;
class Context;
}

namespace LBGui {

class ContextViewPrivate;
class ContextView : public LBGui::TreeView
{
public:
    ContextView(QWidget *parent = 0);
    ~ContextView();

    void setContext(LBDatabase::Context *Context);
    LBDatabase::Context *context() const;

    LBDatabase::Entity *firstSelectedEntity() const;
    QList<LBDatabase::Entity *> selectedEntities() const;

private:
    ContextViewPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(ContextView)
};

} // namespace LBGui

#endif // LBGUI_CONTEXTVIEW_H
