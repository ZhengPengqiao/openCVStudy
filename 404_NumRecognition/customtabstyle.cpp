#include "customtabstyle.h"
#include <QDebug>
#include <QPainter>
#include <QProxyStyle>


CustomTabStyle::CustomTabStyle()
{

}

QSize CustomTabStyle::sizeFromContents(ContentsType type, const QStyleOption *option,
   const QSize &size, const QWidget *widget) const
{
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == QStyle::CT_TabBarTab) {
        s.transpose();
        s.rwidth() = 100; // 设置每个tabBar中item的大小
        s.rheight() = 60;   //如果这里太小,可能造成text文字显示成"..."
    }
    return s;
}

void CustomTabStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    if (element == CE_TabBarTabLabel) {
        if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
            QRect allRect = tab->rect;

            if (tab->state & QStyle::State_Selected) {

                QPixmap result(":/assert/buttonback_active.png");
                painter->save();
                painter->setPen(0xf8fcff);
                painter->drawPixmap(allRect, result);
                painter->restore();
            } else if (tab->state & QStyle::State_MouseOver) {
                    QPixmap result(":/assert/buttonback_hover.png");
                    painter->save();
                    painter->setPen(0xf8fcff);
                    painter->drawPixmap(allRect, result);
                    painter->restore();
            } else if (tab->state & QStyle::State_Active) {
                    QPixmap result(":/assert/buttonback.png");
                    painter->save();
                    painter->setPen(0xf8fcff);
                    painter->drawPixmap(allRect, result);
                    painter->restore();
            } else {
                painter->setPen(0x5d5d5d);
            }

            QTextOption option;
            option.setAlignment(Qt::AlignCenter);


            painter->drawText(allRect, tab->text, option);
            return;
        }
    }

    if (element == CE_TabBarTab) {
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}
