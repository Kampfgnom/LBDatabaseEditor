#include "sidebaritemdelegatemac.h"

#include "sidebartreeview.h"

#include <QPainter>
#include <QLineEdit>
#include <QDebug>
#include <QStandardItem>

namespace LBGui {

SidebarItemDelegateMac::SidebarItemDelegateMac(SidebarTreeView *parent) :
    QStyledItemDelegate(parent),
    m_view(parent)
{
}

void SidebarItemDelegateMac::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.parent().isValid()) {
        static QColor shadow(255,255,255,200);
        static QColor foreground(114,126,140,255);

        QFont font = index.data(Qt::FontRole).value<QFont>();

        painter->setFont(font);
        painter->setPen(shadow);
        painter->drawText(  option.rect.x(),option.rect.y()+16,
                            index.data().toString());

        painter->setPen(foreground);
        painter->drawText(  option.rect.x(),option.rect.y()+15,
                            index.data().toString());
        return;
    }
    else {
        QStyledItemDelegate::paint(painter,option,index);

        QString text = index.data(Qt::UserRole + 2).toString();
        if(text.isEmpty()) {
            text = index.data().toString();
        }

        QFont font = index.data(Qt::FontRole).value<QFont>();

        if(m_view->selectionModel()->selectedIndexes().contains(index)) {
            static QColor shadow(113,125,150,255);
            font.setBold(true);


            painter->setFont(font);
            painter->setPen(shadow);
            painter->drawText(  option.rect.x()+28,option.rect.y()+18,
                                text);
            painter->setPen(Qt::white);
            painter->drawText(  option.rect.x()+28,option.rect.y()+17,
                                text);
        }
        else {
            painter->setFont(font);
            painter->setPen(Qt::black);
            painter->drawText(  option.rect.x()+28,option.rect.y()+17,
                                text);
        }

        return;
    }

    QStyledItemDelegate::paint(painter,option,index);
}

} // namespace LBGui
