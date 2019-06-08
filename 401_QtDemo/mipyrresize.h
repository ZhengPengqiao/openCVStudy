#ifndef MIPYRRESIZE_H
#define MIPYRRESIZE_H

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

class MIPyrResize : public MIBase
{
public:
    MIPyrResize();
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
    QImage image;

    QComboBox *operComboBox;
    QComboBox *valComboBox;
    QCheckBox *imShowChechBox;

    QHBoxLayout *ctrlHBoxLayout;
    QPushButton *PyrUp;
    QPushButton *PyrDown;
    QPushButton *ResizeUp;
    QPushButton *ResizeDown;


    int operType;
    int operVal;

    Mat g_srcImage, g_dstImage, g_tmpImage;

public slots:
    void onSubmitClicked();
    void selectFile();
    void dealPyrUp();
    void dealPyrDown();
    void dealResizeUp();
    void dealResizeDown();
    void onComboBoxCurrentTextChanged(QString text);
};
#endif // MIPYRRESIZE_H
