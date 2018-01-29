/*
 * 文件名称：main.c
 * 创建时间：2017-11-19
 * 文件介绍：用来示例opencv的读取显示图像的使用
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "No image data\n";
        return -1;
    }

    //读取一张图片
    //CV_LOAD_IMAGE_UNCHANGED : 8bit, color or not
    Mat imageUnchanged = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED );
    //CV_LOAD_IMAGE_GRAYSCALE : 将图片转换成灰度再返回
    Mat imageGrayScale = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE );
    //CV_LOAD_IMAGE_COLOR : 总是转换为彩色再返回
    Mat imageColor = imread(argv[1], CV_LOAD_IMAGE_COLOR );
    //CV_LOAD_IMAGE_ANYDEPTH : 如果深度为16/32,就返回对应的图片，否则转换为8位
    Mat imageAnyDepth = imread(argv[1], CV_LOAD_IMAGE_ANYDEPTH );
    //
    Mat imageAnyColor = imread(argv[1], CV_LOAD_IMAGE_ANYCOLOR );

    //在窗口中显示载入的图片
    imshow("显示图片(CV_LOAD_IMAGE_UNCHANGED)", imageUnchanged);
    imshow("显示图片(CV_LOAD_IMAGE_GRAYSCALE)", imageGrayScale);
    imshow("显示图片(CV_LOAD_IMAGE_COLOR)", imageColor);
    imshow("显示图片(CV_LOAD_IMAGE_ANYDEPTH)", imageAnyDepth);
    imshow("显示图片(CV_LOAD_IMAGE_ANYCOLOR)", imageAnyColor);

    //等待窗口退出
    waitKey(0);
    return 0;
}
