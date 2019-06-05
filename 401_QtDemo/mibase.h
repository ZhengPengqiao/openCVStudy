#ifndef MIBASE_H
#define MIBASE_H

#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QObject>
#include <QVBoxLayout>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class MIBase : public QObject
{

public:
    MIBase();
    QString modelItemName;  // 记录当前模块的名字
    QWidget *page;          // 当前模块的页界面
    QPushButton *submit;        // page中的提交按钮

    QString getModelItemName() const;
    void setModelItemName(const QString &value);
    void addSubPage(QWidget *widget);


    QImage cvMat2QImage(const cv::Mat& mat);
    cv::Mat QImage2cvMat(QImage image);
private:
    QVBoxLayout *vboxlayout;    // page的顶层布局

public slots:
    virtual void onSubmitClicked();
};

#endif // MIBASE_H
