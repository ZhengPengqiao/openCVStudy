#ifndef MISOBEL_H
#define MISOBEL_H

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

class MISobel : public MIBase
{
public:
    MISobel();
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
    QHBoxLayout *sobelKernelLayout;
    QSlider *sobelKernelSlider;
    QLabel *sobelKernelLabel;
    int g_sobelKernelSize;

    // 当前模块的Area区域
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    // 当前模块的Area区域, 显示原图,效果图
    QFormLayout *formLayout;

    // 当前模块的Area区域, 显示原图
    QLabel *label_src;
    QLabel *imageLabel_src;
    // 当前模块的Area区域, 显示sobelAbsX
    QLabel *label_sobelAbsX;
    QLabel *imageLabel_sobelAbsX;
    // 当前模块的Area区域, 显示sobelAbsY
    QLabel *label_sobelAbsY;
    QLabel *imageLabel_sobelAbsY;
    // 当前模块的Area区域, 显示效果图
    QLabel *label_dst;
    QLabel *imageLabel_dst;

    Mat g_srcImage;
    Mat g_dstImage;
    Mat g_sobelGradient_X, g_sobelGradient_Y;
    Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
public slots:
    void onSubmitClicked();
    void selectFile();
    void onImShowChechBoxClicked(bool status);
    void onSliderValueChange(int val);
};
#endif // MISOBEL_H
