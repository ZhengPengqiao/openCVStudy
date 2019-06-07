/*
 * 文件名称：main.c
 * 创建时间：2017-11-19
 * 文件介绍：用来示例opencv的灰度效果的使用
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

char *imageName = "../assert/image1.png";

int main (int argc, char **argv)
{
    if (argc == 2)
    {
        imageName = argv[1];
    }

    cout << "image path:" << imageName << endl;

    Mat image, image_gray, aa;

    //读取一张图片
    image = imread(imageName, CV_LOAD_IMAGE_COLOR );
    if (!image.data)
    {
        cout << "No image data\n";
        return -1;
    }

    //将图片转为灰度图片
    cvtColor(image, image_gray, CV_RGB2GRAY);

    //创建并显示窗口
    namedWindow("image", CV_WINDOW_AUTOSIZE);
    namedWindow("image gray", CV_WINDOW_AUTOSIZE);
    imshow("image", image);
    imshow("image gray", image_gray);

    waitKey(0);
    return 0;
}
