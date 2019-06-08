#ifndef MIFLOODFILL_H
#define MIFLOODFILL_H

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
#include <QComboBox>

class MIFloodFill : public MIBase
{
public:
    MIFloodFill();
    void retranslateUi();

    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    QWidget *subPage;
    QLineEdit *imagePath;

    QPushButton *button;
    QLabel *label;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *gridLayoutWidget;
    QFormLayout *formLayout;

    QLabel *label_src;
    QLabel *imageLabel_src;
    QLabel *label_dst;
    QLabel *imageLabel_dst;
    QLabel *label_mask;
    QLabel *imageLabel_mask;
    QCheckBox *imShowChechBox;
    QCheckBox *isUseColorChechBox;
    QCheckBox *isUseMaskChechBox;
    QImage image;
    QHBoxLayout *lowDiffLayout;
    QSlider *lowDiffSlider;
    QLabel *lowDiffLabel;
    int lowDiffMax;
    QHBoxLayout *upDiffLayout;
    QSlider *upDiffSlider;
    QLabel *upDiffLabel;
    int upDiffMax;
    QPushButton *clearButton;
    QHBoxLayout *ctrlHBoxLayout;
    QComboBox *comboBox;

    int lowDifference;  // 负差最大值
    int upDifference;   // 正差最大值
    int isColor;
    Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;//定义原始图、目标图、灰度图、掩模图
    int fillMode;    //漫水填充的模式
    int connectivity;   //表示floodFill函数标识符低八位的连通值
    int newMaskVal;  //新的重新绘制的像素值
    bool isImShow;
    bool isUseColor;
    bool isUseMask;

public slots:
    void onSubmitClicked();
    void onLowDiffSliderValueChanged(int val);
    void onUpDiffSliderValueChanged(int val);
    void selectFile();
    bool eventFilter(QObject *obj, QEvent *event);
    void onComboBoxCurrentTextChanged(QString text);
    void onImShowChechBoxClicked(bool isImShow);
    void onIsUseColorChechBoxClicked(bool isUseColor);
    void onIsUseMaskChechBoxClicked(bool isUseMask);
    void onClearButtonClicked(bool isClear);
};
#endif // MIFLOODFILL_H
