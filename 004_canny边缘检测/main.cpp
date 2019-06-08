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


char *imageName = "../assert/image1.png";

int main (int argc, char **argv)
{
    if (argc == 2)
    {
        imageName = argv[1];
    }

    cout << "image path:" << imageName << endl;

    Mat dstImage, grayImage, srcImage, edge;
    
    //读取一张图片
    srcImage = imread(imageName, CV_LOAD_IMAGE_COLOR );
    if (!srcImage.data)
    {
        cout << "No image data\n";
        return -1;
    }

	//【1】创建与src同类型和大小的矩阵(dst)
	dstImage.create( srcImage.size(), srcImage.type() );

	//【2】将原图像转换为灰度图像
	//此句代码的OpenCV2版为：
	//cvtColor( srcImage, grayImage, CV_BGR2GRAY );
	//此句代码的OpenCV3版为：
	cvtColor( srcImage, grayImage, COLOR_BGR2GRAY );

	//【3】先用使用 3x3内核来降噪
	blur( grayImage, edge, Size(3,3) );

	//【4】运行Canny算子
	Canny( edge, edge, 3, 9,3 );

	//【5】显示效果图 
	imshow("【效果图】Canny边缘检测", edge); 

	waitKey(0); 
    return 0;
}
