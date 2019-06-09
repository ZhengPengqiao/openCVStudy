#include "miseparatoritem.h"

MISeparatorItem::MISeparatorItem(QString name, QString info)
{
    this->setModelItemName(name);
    label = new QLabel();
    label->setText(info);
    this->addSubPage(label);
}
