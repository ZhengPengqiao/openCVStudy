#ifndef NUMBERCHECKFROM_H
#define NUMBERCHECKFROM_H

#include <QWidget>

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class myRect
{
public:
    myRect(){}
    ~myRect(){}
    myRect(Rect &temp):myRc(temp){}
    //比较矩形左上角的横坐标，以便排序
    bool operator<(myRect &rect)
    {
        if (this->myRc.x < rect.myRc.x)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //重载赋值运算符
    myRect operator=(myRect &rect)
    {
        this->myRc = rect.myRc;
        return *this;
    }
    //获取矩形
    Rect getRect()
    {
        return myRc;
    }
private:
    Rect myRc;//存放矩形
};


namespace Ui {
class NumberCheckFrom;
}

class NumberCheckFrom : public QWidget
{
    Q_OBJECT

public:
    explicit NumberCheckFrom(QWidget *parent = 0);
    ~NumberCheckFrom();
    int getPiexSum(Mat &image);
    QString template_image;
    QString recongition_image;
    cv::Mat QImage2cvMat(QImage image);
    QImage cvMat2QImage(const cv::Mat& mat);
    void clearLayout(QLayout *layout);

public slots:
    void pushButton_recognition_onclick();
    void pushButton_create_complate_onclick();
    void pushButton_select_template_onclick();
    void pushButton_select_recognition_onclick();

private:
    Ui::NumberCheckFrom *ui;
};

#endif // NUMBERCHECKFROM_H
