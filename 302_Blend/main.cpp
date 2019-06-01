#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

//-----------------------------------【宏定义部分】--------------------------------------------
//		描述：定义一些辅助宏
//------------------------------------------------------------------------------------------------
#define WINDOW_NAME1 "【原始图-srcImage 】"        //为窗口标题定义的宏
#define WINDOW_NAME2 "【原始图-logoImage】"        //为窗口标题定义的宏
#define WINDOW_NAME3 "【原始图-maskImage】"        //为窗口标题定义的宏
#define WINDOW_NAME4 "【效果图】"        //为窗口标题定义的宏


//----------------------------------【ROI_AddImage( )函数】----------------------------------
// 函数名：ROI_AddImage（）
//	描述：利用感兴趣区域ROI实现图像叠加
//----------------------------------------------------------------------------------------------
bool  ROI_AddImage()
{

    // 【1】读入图像
    Mat srcImage1= imread("../assert/dota_pa.jpg");
    Mat logoImage= imread("../assert/dota_logo.jpg");
    if( !srcImage1.data ) { printf("读取srcImage1错误~！ \n"); return false; }
    if( !logoImage.data ) { printf("读取logoImage错误~！ \n"); return false; }

    // 【2】定义一个Mat类型并给其设定ROI区域
    Mat imageROI= srcImage1(Rect(200,250,logoImage.cols,logoImage.rows));

    // 【3】加载掩模（必须是灰度图）
    Mat mask= imread("../assert/dota_logo.jpg",0);

    //【4】将掩膜拷贝到ROI
    logoImage.copyTo(imageROI,mask);

    // 【5】显示结果
    namedWindow("<1>利用ROI实现图像叠加示例窗口");
    imshow("<1>利用ROI实现图像叠加示例窗口",srcImage1);

    return true;
}


//---------------------------------【LinearBlending（）函数】-------------------------------------
// 函数名：LinearBlending（）
// 描述：利用cv::addWeighted（）函数实现图像线性混合
//--------------------------------------------------------------------------------------------
bool  LinearBlending()
{
    //【0】定义一些局部变量
    double alphaValue = 0.5;
    double betaValue;
    Mat srcImage2, srcImage3, dstImage;

    // 【1】读取图像 ( 两幅图片需为同样的类型和尺寸 )
    srcImage2 = imread("../assert/mogu.jpg");
    srcImage3 = imread("../assert/rain.jpg");

    if( !srcImage2.data ) { printf("读取srcImage2错误！ \n"); return false; }
    if( !srcImage3.data ) { printf("读取srcImage3错误！ \n"); return false; }

    // 【2】进行图像混合加权操作
    betaValue = ( 1.0 - alphaValue );
    addWeighted( srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

    // 【3】显示原图窗口
    imshow( "<2>线性混合示例窗口【原图】", srcImage2 );
    imshow( "<3>线性混合示例窗口【效果图】", dstImage );

    return true;

}

//---------------------------------【ROI_LinearBlending（）】-------------------------------------
// 函数名：ROI_LinearBlending（）
// 描述：线性混合实现函数,指定区域线性图像混合.利用cv::addWeighted（）函数结合定义
//			  感兴趣区域ROI，实现自定义区域的线性混合
//--------------------------------------------------------------------------------------------
bool  ROI_LinearBlending()
{

    //【1】读取图像
    Mat srcImage4= imread("../assert/mogu.jpg",1);
    Mat logoImage= imread("../assert/dota_logo.jpg");

    if( !srcImage4.data ) { printf("读取srcImage4错误~！ \n"); return false; }
    if( !logoImage.data ) { printf("读取logoImage错误~！ \n"); return false; }

    //【2】定义一个Mat类型并给其设定ROI区域
    Mat imageROI;
    //方法一
    imageROI= srcImage4(Rect(200,250,logoImage.cols,logoImage.rows));
    //方法二
    //imageROI= srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));

    //【3】将logo加到原图上
    addWeighted(imageROI,0.5,logoImage,0.3,0.,imageROI);

    //【4】显示结果
    imshow("<4>区域线性图像混合示例窗口",srcImage4);

    return true;
}


//---------------------------------------【main( )函数】--------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始执行
//-----------------------------------------------------------------------------------------------
int main( void )
{
    if(ROI_AddImage()&& LinearBlending()&& ROI_LinearBlending())
    {
        cout<<endl<<"\n运行成功，得出了需要的图像";
    }

    waitKey(0);
    return(0);
}

