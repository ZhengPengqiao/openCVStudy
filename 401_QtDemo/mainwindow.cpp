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
#include "mithreshold.h"
#include "mifloodfill.h"
#include "mipyrresize.h"
#include "miseparatoritem.h"
#include "micanny.h"
#include "misobel.h"
#include "mischarr.h"
#include "milaplacian.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initBaseUI();
    QString str1 = "三种线性滤波:方框滤波,均值滤波,高斯滤波\n"
                  "两种非线性滤波: 中值滤波,双边滤波\n"
                  "七种图像处理形态学:腐蚀,膨胀,开运算,闭运算,形态学梯度,顶帽,黑帽\n"
                  "漫水填充\n"
                  "图像缩放\n"
                  "图像金字塔\n"
                  "阈值化";

    addModelItem(new MISeparatorItem("---->滤波,缩放,阈值化", str1));
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
    addModelItem(new MIThreshold());
    addModelItem(new MIFloodFill());
    addModelItem(new MIPyrResize());

    QString str2 = "基于OpenCV的边沿检测\n"
                   "霍夫变换\n"
                   "重映射\n"
                   "仿射变换\n"
                   "直方图均衡化";
    addModelItem(new MISeparatorItem("---->图像变换", str2));
    addModelItem(new MICanny());
    addModelItem(new MISobel());
    addModelItem(new MIScharr());
    addModelItem(new MILaplacian());
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
