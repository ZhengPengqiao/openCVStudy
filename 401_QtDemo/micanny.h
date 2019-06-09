#ifndef MICANNY_H
#define MICANNY_H


#include "mibase.h"

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>
#include <QGridLayout>
#include <QMessageBox>
#include <QCheckBox>
#include <QSlider>
#include <QFormLayout>

class MICanny : public MIBase
{
public:
    MICanny();
    void retranslateUi();

    // 当前模块的顶级布局和控件
    QVBoxLayout *vBoxLayout;
    QWidget *subPage;

    // 文件选择UI布局
    QHBoxLayout *fileSelectHBoxLayout;
    QPushButton *fileSelectButton;
    QLabel *fileSelectLabel;
    QLineEdit *fileSelectPath;

    // 参数控制UI布局
    QHBoxLayout *ctrlHBoxLayout;
    QCheckBox *imShowChechBox;
    int imShow;
    // 参数控制UI布局,滑动条
    QHBoxLayout *threshold1Layout;
    QSlider *threshold1Slider;
    QLabel *threshold1Label;
    int threshold1Val;
    QHBoxLayout *threshold2Layout;
    QSlider *threshold2Slider;
    QLabel *threshold2Label;
    int threshold2Val;

    // 当前模块的Area区域
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    // 当前模块的Area区域, 显示原图,效果图
    QFormLayout *formLayout;

    // 当前模块的Area区域, 显示原图
    QLabel *label_src;
    QLabel *imageLabel_src;
    // 当前模块的Area区域, 显示灰度图
    QLabel *label_gray;
    QLabel *imageLabel_gray;
    // 当前模块的Area区域, 显示灰度图的边沿检测
    QLabel *label_grayEdges;
    QLabel *imageLabel_grayEdges;
    // 当前模块的Area区域, 显示效果图
    QLabel *label_dst;
    QLabel *imageLabel_dst;

    Mat g_srcImage, g_srcGrayImage, g_GrayDetectedEdges, g_cannyDetectedEdges;
    Mat g_dstImage;

public slots:
    void onSubmitClicked();
    void selectFile();
    void onImShowChechBoxClicked(bool status);
    void onSliderValueChange(int val);
};
#endif // MICANNY_H
