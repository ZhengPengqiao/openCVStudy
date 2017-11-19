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
    //读取一张图片
    Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR );
    if (argc != 2 || !image.data)
    {
        cout << "No image data\n";
        return -1;
    }

    //在窗口中显示载入的图片
    imshow("显示图片", image);

    //等待窗口退出
    waitKey(0);
    return 0;
}
