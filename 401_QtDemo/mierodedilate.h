#ifndef MIERODEDILATE_H
#define MIERODEDILATE_H

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

class MIErodeDilate : public MIBase
{
public:
    MIErodeDilate();
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    QWidget *subPage;
    QLineEdit *imagePath;

    QPushButton *button;
    QLabel *label;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;

    QLabel *imageLabel_src;
    QLabel *imageLabel_dst;
    QCheckBox *imShowChechBox;
    QImage image;
    QLabel *label_src;
    QLabel *label_dst;
    QHBoxLayout *hBoxLayoutSlider;
    QSlider *horizontalSlider;
    QLabel *labelSlider;
    int sliderMaxIterationNum;

public slots:
    void onSubmitClicked();
    void selectFile();
};
#endif // MIERODEDILATE_H
