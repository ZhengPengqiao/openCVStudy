/*
 * 文件名称：main.c
 * 创建时间：2017-11-19
 * 文件介绍：用来示例opencv的腐蚀效果的使用
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


char *imageName = "../assert/image1.png";

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        imageName = argv[1];
    }

    cout << "image path:" << imageName << endl;
    //读取一张图片
    Mat srcImage = imread(imageName, CV_LOAD_IMAGE_COLOR );
    if (!srcImage.data)
    {
        cout << "No image data\n";
        return -1;
    }

    //显示原始图
    imshow("[原图] 腐蚀操作", srcImage);

    //获取常用的结构元素的形状：矩形（包括线形）;
    Mat element = getStructuringElement(MORPH_RECT, Size(15,15));
    Mat dstImage;
    erode(srcImage, dstImage, element);

    //显示效果图
    imshow("[效果图] 腐蚀操作", dstImage);

    waitKey(0);

    return 0;
}
