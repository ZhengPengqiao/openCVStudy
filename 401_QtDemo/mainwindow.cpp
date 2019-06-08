#include "mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <QSpacerItem>

#include "miboxfilter.h"
#include "miblur.h"
#include "migaussianblur.h"
#include "mimedianblur.h"
#include "mibilateralfilter.h"
#include "midilate.h"
#include "mierode.h"
#include "mierodedilate.h"
#include "miopenclose.h"
#include "mitopblackhat.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initBaseUI();

    addModelItem(new MIBoxFilter());
    addModelItem(new MIBlur());
    addModelItem(new MIGaussianBlur());
    addModelItem(new MIMedianBlur());
    addModelItem(new MIBilateralFilter());
    addModelItem(new MIDilate());
    addModelItem(new MIErode());
    addModelItem(new MIErodeDilate());
    addModelItem(new MIOpenClose());
    addModelItem(new MITopBlackHat());
}


void MainWindow::initBaseUI()
{
    this->resize(646, 454);

    // Root Widget
    centralWidget = new QWidget(this);
    centralWidget->setGeometry(this->rect());

    // Horizontal Layout
    horizontalLayout = new QHBoxLayout(centralWidget);
    horizontalLayout->setSpacing(3);

    // add rightVBoxLayout, listWidget
    leftVBoxLayout = new QVBoxLayout();
    leftVBoxLayout->setSpacing(6);
    listWidget = new QListWidget(centralWidget);
    connect(listWidget, &QListWidget::clicked, this, &MainWindow::listWidget_clicked);

    leftVBoxLayout->addWidget(listWidget);
    horizontalLayout->addLayout(leftVBoxLayout);

    // add Line
    line = new QFrame(centralWidget);
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    horizontalLayout->addWidget(line);

    rightVBoxLayout = new QVBoxLayout();
    rightVBoxLayout->setSpacing(6);
    stackedWidget = new QStackedWidget(centralWidget);

    rightVBoxLayout->addWidget(stackedWidget);
    horizontalLayout->addLayout(rightVBoxLayout);

    horizontalLayout->setStretch(0, 2);
    horizontalLayout->setStretch(2, 6);
    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}

// 添加ModelItem
void MainWindow::addModelItem(MIBase *item)
{
    listWidget->addItem(item->modelItemName);
    stackedWidget->addWidget(item->page);
}


void MainWindow::listWidget_clicked(QModelIndex index)
{
    qDebug() << "index: " << index.row();
    stackedWidget->setCurrentIndex(index.row());
}
