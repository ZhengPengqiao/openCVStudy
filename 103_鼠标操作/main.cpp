#include <opencv2/opencv.hpp>

using namespace cv;

#define WINDOW_NAME "[程序窗口]"

//全局函数的声明
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(cv::Mat& img, cv::Rect box);
void ShowHelpText();

//全局变量的声明
static Rect g_rectangle;
static bool g_bDrawingBox = false; //是否进行绘制
static RNG g_rng(12345);

int main(int argc, char *argv[])
{
    //[1]准备参数
    g_rectangle = Rect(-1, -1, 0, 0);
    Mat srcImage(600, 800, CV_8UC3);
    Mat tempImage;
    srcImage.copyTo(tempImage);

    g_rectangle = Rect(-1, -1, 0, 0);
    srcImage = Scalar::all(0);

    //[2]设置鼠标操作回调函数
    namedWindow(WINDOW_NAME);
    setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);

    //[3]程序主循环,当绘制标志为真时,进行绘制

    while(1)
    {
        srcImage.copyTo(tempImage);

        if( g_bDrawingBox )
        {
            DrawRectangle(tempImage, g_rectangle);
        }

        imshow(WINDOW_NAME, tempImage);

        if(waitKey(10) == 27)
        {
            break;
        }
    }

    return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
    Mat & image = *(cv::Mat *)param;
    switch(event)
    {
        case EVENT_MOUSEMOVE:
        {
            printf("mousemove x=%d y=%d \n", x,y);
            if( g_bDrawingBox )
            {
                g_rectangle.width = x - g_rectangle.x;
                g_rectangle.height = y - g_rectangle.y;
            }
        }

        break;
        case EVENT_LBUTTONDOWN:
        {
            printf("mouse L Dn x=%d y=%d \n", x,y);
            g_bDrawingBox = true;
            g_rectangle = Rect(x, y, 0, 0);
        }
        break;
        case EVENT_LBUTTONUP:
        {
            printf("mouse L Up x=%d y=%d \n", x,y);
            g_bDrawingBox = false;

            if( g_rectangle.width < 0 )
            {
                g_rectangle.x += g_rectangle.width;
                g_rectangle.width *= -1;
            }

            if( g_rectangle.height < 0 )
            {
                g_rectangle.y += g_rectangle.height;
                g_rectangle.height *= -1;
            }

            //调用函数进行绘制
            DrawRectangle(image, g_rectangle);
        }
        break;
    }
}

void DrawRectangle(cv::Mat &img, cv::Rect box)
{
    rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0,255),
              g_rng.uniform(0,255), g_rng.uniform(0,255))); //随机颜色
}


