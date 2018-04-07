#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
    //-------------------------[图片的载入]---------------------------------------
    Mat saber = imread("../assert/saber.jpg"); //载入到Mat
    namedWindow("[1]动漫图");  //创建一个名为"[1]动漫图"的窗口
    imshow("[1]动漫图",saber);  //显示名为"[1]动漫图"的窗口

    //-------------------------[初级图像混合]---------------------------------------
    Mat image = imread("../assert/dota2.jpg");
    Mat logo1 = imread("../assert/dota2-logo1.jpg");
    Mat logo2 = imread("../assert/dota2-logo2.jpg");

    //先显示载入的图片
    namedWindow("[2]原图片");
    imshow("[2]原图片",image);
    namedWindow("[2]logo1图");
    imshow("[2]logo1图", logo1);
    namedWindow("[2]logo2图");
    imshow("[2]logo2图", logo2);

    //定义一个Mat类型,用于存放,图像的ROI,改变这里Mat,原图也会跟随着改变
    Mat imageROI1;
    Mat imageROI2;
    //方法一
    imageROI1 = image(Rect(50,50, logo1.cols, logo1.rows));
    //方法二
    imageROI2 = image(Range(100,100+logo2.rows), Range(50,50+logo2.cols));


    //将logo加载到原图上
    addWeighted(imageROI1, 0.3, logo1, 0.7, 0, imageROI1);
    addWeighted(imageROI2, 0.3, logo2, 0.7, 0, imageROI2);

    namedWindow("[3]image-Rect-logo1");
    imshow("[3]image-Rect-logo1", imageROI1);
    namedWindow("[3]image-Rect-logo2");
    imshow("[3]image-Rect-logo2", imageROI2);

    //显示结构
    namedWindow("[4]原图+logo图");
    imshow("[4]原图+logo图", image);

    //-------------------------[图像输出]---------------------------------------
    //输出一张jpg图像到../assert/tmp/下
    imwrite("../assert/tmp/原图+logo图.jpg",image);

    waitKey();
}
