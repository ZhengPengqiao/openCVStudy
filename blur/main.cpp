/*
 * 文件名称：main.c
 * 创建时间：2017-11-19
 * 文件介绍：用来示例opencv的模糊效果的使用
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
    //读取一张图片
    Mat srcImage = imread(argv[1], CV_LOAD_IMAGE_COLOR );
    if (argc != 2 || !srcImage.data)
    {
        cout << "No image data\n";
        return -1;
    }

    //显示原始图
    imshow("[原图] 均值滤波", srcImage);

    //进行均值滤波操作
    Mat dstImage;
    blur(srcImage, dstImage, Size(7,7));

    //显示效果图
    imshow("[效果图] 均值滤波", dstImage);

    waitKey(0);

    return 0;
}
