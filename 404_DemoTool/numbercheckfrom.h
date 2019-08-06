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

public slots:
    void on_pusfbutton_check_click();
    void on_pusfbutton_templete_click();

private:
    Ui::NumberCheckFrom *ui;
};

#endif // NUMBERCHECKFROM_H
