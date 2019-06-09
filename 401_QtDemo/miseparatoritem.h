#ifndef MISEPARATORITEM_H
#define MISEPARATORITEM_H

#include "mibase.h"

#include <QPushButton>
#include <QLabel>

class MISeparatorItem : public MIBase
{
public:
    MISeparatorItem(QString name, QString info);
    QLabel *label;
};
#endif // MISEPARATORITEM_H
