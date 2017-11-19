/*
 * 文件名称：main.c
 * 创建时间：2017-11-19
 * 文件介绍：用来示例opencv的视频操作的使用
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

#define VIDEO_CAMERA
//#define CANNY_FRAME

using namespace cv;
using namespace std;


int main (int argc, char **argv)
{
    Mat edges;
    //判断参数是否正确
    if (argc != 2)
    {
        cout << "No video data\n";
        return -1;
    }

    //读取视频
#ifdef VIDEO_CAMERA
    VideoCapture capture(0);
#else
    VideoCapture capture(argv[1]);
#endif

    //循环读取每一帧
    while(1)
    {
        Mat frame;          //定义一个Mat变量，用于存储每一帧的图像
        capture>>frame;     //读取当前帧

        //若视频播放完成，退出循环
        if(frame.empty())
        {
            break;
        }
#ifdef CANNY_FRAME
        //将原图像转换成灰度图像
        cvtColor(frame, edges, COLOR_RGB2GRAY);
        //使用3x3内核来降噪（2x3+1=7）
        blur(edges, edges, Size(7,7)); //进行模糊
        //进行Canny边缘检测
        Canny(edges, frame, 0, 30, 3);
#endif
        imshow("读取视频", frame);  //显示当前帧
        int key = waitKey(30);               //延时30ms
        if( key == 27 )
        {
            printf("key = %d\n", key);
            return 0;
        }
    }

    waitKey(0);

    return 0;
}
