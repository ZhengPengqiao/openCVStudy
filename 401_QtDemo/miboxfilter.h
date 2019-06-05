#ifndef MIBOXFILTER_H
#define MIBOXFILTER_H

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

class MIBoxFilter : public MIBase
{
public:
    MIBoxFilter();
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

public slots:
    void onSubmitClicked();
    void selectFile();
};

#endif // MIBOXFILTER_H
