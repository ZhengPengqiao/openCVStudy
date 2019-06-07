#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "imageopera.h"

using namespace cv;
using namespace std;

//-----------------------------------【宏定义部分】--------------------------------------------
//		描述：定义一些辅助宏
//------------------------------------------------------------------------------------------------
#define WINDOW_NAME1 "【原始图】"        //为窗口标题定义的宏
#define WINDOW_NAME2 "【缩减图】"        //为窗口标题定义的宏
#define NTESTS 14
#define NITERATIONS 20


int WIDTH=600; //定义窗口宽的宏
int HEIGHT=300; //定义窗口高的宏
//---------------------------------------【main( )函数】--------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始执行
//-----------------------------------------------------------------------------------------------
int main( void )
{
    int64 t[NTESTS],tinit;
    Mat image0;
    Mat image1;
    Mat image2;

    image0= imread("../assert/saber.jpg");
    if (!image0.data)
        return 0;

    //时间值设为0
    for (int i=0; i<NTESTS; i++)
        t[i]= 0;


    // 多次重复测试
    int n=NITERATIONS;
    for (int k=0; k<n; k++)
    {
        cout << k << " of " << n << endl;

        image1= imread("../assert/saber.jpg");
        //【方法一】利用.ptr 和 []
        tinit= getTickCount();
        ImageOpera::colorReduce0(image1);
        t[0]+= getTickCount()-tinit;

        //【方法二】利用 .ptr 和 * ++
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        ImageOpera::colorReduce1(image1);
        t[1]+= getTickCount()-tinit;

        //【方法三】利用.ptr 和 * ++ 以及模操作
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        ImageOpera::colorReduce2(image1);
        t[2]+= getTickCount()-tinit;

        //【方法四】 利用.ptr 和 * ++ 以及位操作
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        ImageOpera::colorReduce3(image1);
        t[3]+= getTickCount()-tinit;

        //【方法五】 利用指针的算术运算
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        ImageOpera::colorReduce4(image1);
        t[4]+= getTickCount()-tinit;

        //【方法六】利用 .ptr 和 * ++以及位运算、image.cols * image.channels()
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        ImageOpera::colorReduce5(image1);
        t[5]+= getTickCount()-tinit;

        //【方法七】利用.ptr 和 * ++ 以及位运算(continuous)
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        ImageOpera::colorReduce6(image1);
        t[6]+= getTickCount()-tinit;

        //【方法八】利用 .ptr 和 * ++ 以及位运算 (continuous+channels)
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        ImageOpera::colorReduce7(image1);
        t[7]+= getTickCount()-tinit;

        //【方法九】 利用Mat_ iterator
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        ImageOpera::colorReduce8(image1);
        t[8]+= getTickCount()-tinit;

        //【方法十】 利用Mat_ iterator以及位运算
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        ImageOpera::colorReduce9(image1);
        t[9]+= getTickCount()-tinit;

        //【方法十一】利用Mat Iterator_
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        ImageOpera::colorReduce10(image1);
        t[10]+= getTickCount()-tinit;

        //【方法十二】 利用动态地址计算配合at
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        ImageOpera::colorReduce11(image1);
        t[11]+= getTickCount()-tinit;

        //【方法十三】 利用图像的输入与输出
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        Mat result;
        ImageOpera::colorReduce12(image1, result);
        t[12]+= getTickCount()-tinit;
        image2= result;

        //【方法十四】 利用操作符重载
        image1= imread("../assert/saber.jpg");
        tinit= getTickCount();
        ImageOpera::colorReduce13(image1);
        t[13]+= getTickCount()-tinit;

        //------------------------------
    }
     //输出图像
    imshow("原始图像",image0);
    imshow("结果",image2);
    imshow("图像结果",image1);

    // 输出平均执行时间
    cout << endl << "-------------------------------------------" << endl << endl;
    cout << "\n【方法一】利用.ptr 和 []的方法所用时间为 " << 1000.*t[0]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法二】利用 .ptr 和 * ++ 的方法所用时间为" << 1000.*t[1]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法三】利用.ptr 和 * ++ 以及模操作的方法所用时间为" << 1000.*t[2]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法四】利用.ptr 和 * ++ 以及位操作的方法所用时间为" << 1000.*t[3]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法五】利用指针算术运算的方法所用时间为" << 1000.*t[4]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法六】利用 .ptr 和 * ++以及位运算、channels()的方法所用时间为" << 1000.*t[5]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法七】利用.ptr 和 * ++ 以及位运算(continuous)的方法所用时间为" << 1000.*t[6]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法八】利用 .ptr 和 * ++ 以及位运算 (continuous+channels)的方法所用时间为" << 1000.*t[7]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法九】利用Mat_ iterator 的方法所用时间为" << 1000.*t[8]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法十】利用Mat_ iterator以及位运算的方法所用时间为" << 1000.*t[9]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法十一】利用Mat Iterator_的方法所用时间为" << 1000.*t[10]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法十二】利用动态地址计算配合at 的方法所用时间为" << 1000.*t[11]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法十三】利用图像的输入与输出的方法所用时间为" << 1000.*t[12]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法十四】利用操作符重载的方法所用时间为" << 1000.*t[13]/getTickFrequency()/n << "ms" << endl;

    waitKey();
    return 0;
}

