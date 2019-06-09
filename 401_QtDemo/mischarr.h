#ifndef MISCHARR_H
#define MISCHARR_H

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

class MIScharr : public MIBase
{
public:
    MIScharr();
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

    // 当前模块的Area区域
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    // 当前模块的Area区域, 显示原图,效果图
    QFormLayout *formLayout;

    // 当前模块的Area区域, 显示原图
    QLabel *label_src;
    QLabel *imageLabel_src;
    // 当前模块的Area区域, 显示scharrAbsX
    QLabel *label_scharrAbsX;
    QLabel *imageLabel_scharrAbsX;
    // 当前模块的Area区域, 显示scharrAbsY
    QLabel *label_scharrAbsY;
    QLabel *imageLabel_scharrAbsY;
    // 当前模块的Area区域, 显示效果图
    QLabel *label_dst;
    QLabel *imageLabel_dst;

    Mat g_srcImage;
    Mat g_dstImage;
    Mat g_scharrGradient_X, g_scharrGradient_Y;
    Mat g_scharrAbsGradient_X, g_scharrAbsGradient_Y;
public slots:
    void onSubmitClicked();
    void selectFile();
    void onImShowChechBoxClicked(bool status);
    void onSliderValueChange(int val);
};
#endif // MISCHARR_H
