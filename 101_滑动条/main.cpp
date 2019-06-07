#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

#define WINDOW_NAME "[线性混合示例]"

const int g_nMaxAlphaValue = 100; //Alpha默认是最大值
static int g_nAlphaValueSlider; //滑块对应的值
static double g_dAlphaValue;
static double g_dBetaValue;
static char TrackbarName[50];

//声明存储图像的变量
static Mat g_srcImage1;
static Mat g_srcImage2;
static Mat g_dstImage;


void on_Trackbar(int , void *)
{
    //两种获取滑块值的方法
    //printf("TrackBar val(getTrackbarPos): %d \n", getTrackbarPos(TrackbarName, WINDOW_NAME));
    printf("TrackBar val(g_nAlphaValueSlider): %d \n", g_nAlphaValueSlider);

    //求出当前alpha值相对于最大值的比例
    g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue;
    //beta的值为1-alpha
    g_dBetaValue = 1-g_dAlphaValue;

    //根据alpha,beta进行线性混合
    addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

    //显示图片
    imshow(WINDOW_NAME, g_dstImage);
}


int main(int argc, char *argv[])
{
    //加载图片
    g_srcImage1 = imread("../assert/image6.jpg");
    g_srcImage2 = imread("../assert/image7.jpg");

    if( !g_srcImage1.data )
    {
        printf("读取第一张图片错误,请确认是否存在../assert/dota.jpg图片");
    }

    if( !g_srcImage2.data )
    {
        printf("读取第二张图片错误,请确认是否存在../assert/saber.jpg图片");
    }


    //设置滑动条初始值
    g_nAlphaValueSlider = 70;

    //创建窗口
    namedWindow(WINDOW_NAME, 1);

    //在创建的窗口中创建一个滑动控件
    sprintf(TrackbarName,"透明度: %d", g_nMaxAlphaValue);

    createTrackbar(TrackbarName, WINDOW_NAME,  &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

    //结果在回调函数中显示
    on_Trackbar(g_nAlphaValueSlider, 0);


    //按任意键退出
    waitKey(0);

    return 0;
}
