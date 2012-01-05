#ifndef LBGUI_CONTEXTWIDGET_H
#define LBGUI_CONTEXTWIDGET_H

#include <LBGui/LBGui.h>

namespace LBDatabase {
class Context;
}

namespace LBGui {

class ContextView;

class ContextWidget : public TabWidget
{
    Q_OBJECT
public:
    explicit ContextWidget(QWidget *parent = 0);

    void setContext(LBDatabase::Context *context);

private:
    LBDatabase::Context *m_context;
    ContextView *m_plainContentsContextView;
};

} // namespace LBGui

#endif // LBGUI_CONTEXTWIDGET_H
