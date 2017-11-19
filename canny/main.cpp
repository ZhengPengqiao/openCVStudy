/*
 * 文件名称：main.c
 * 创建时间：2017-11-19
 * 文件介绍：用来示例opencv的边沿检测的使用
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main (int argc, char **argv)
{
    Mat dstImage, grayImage, srcImage;

    //读取一张图片
    srcImage = imread(argv[1], CV_LOAD_IMAGE_COLOR );
    if (argc != 2 || !srcImage.data)
    {
        cout << "No image data\n";
        return -1;
    }

    //将原图转换为灰度图像
    cvtColor(srcImage, grayImage, CV_BGR2BGRA);

    //先使用3x3内核来滤波降噪
    blur(srcImage, dstImage, Size(3,3));

    //运行Canny算子
    Canny(dstImage,dstImage, 3, 9, 3);

    //显示效果图
    imshow("[效果图] Canny边缘检测", dstImage);

    waitKey(0);

    return 0;
}
