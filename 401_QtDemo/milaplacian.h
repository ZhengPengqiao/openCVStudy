#ifndef MILAPLACIAN_H
#define MILAPLACIAN_H


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

class MILaplacian : public MIBase
{
public:
    MILaplacian();
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
    // 当前模块的Area区域, 显示gray
    QLabel *label_gray;
    QLabel *imageLabel_gray;
    // 当前模块的Area区域, 显示效果图
    QLabel *label_abs;
    QLabel *imageLabel_abs;

    Mat g_srcImage;
    Mat g_dstImage;
    Mat g_grayImage, g_absImage;
public slots:
    void onSubmitClicked();
    void selectFile();
    void onImShowChechBoxClicked(bool status);
    void onSliderValueChange(int val);
};
#endif // MILAPLACIAN_H
