#ifndef IMAGEOPERA_H
#define IMAGEOPERA_H
//---------------------------------【头文件、命名空间包含部分】-----------------------------
//		描述：包含程序所使用的头文件和命名空间
//-------------------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class ImageOpera
{
public:
    ImageOpera();
    static void colorReduce0(Mat &image, int div=64);
    static void colorReduce1(Mat &image, int div=64);
    static void colorReduce2(Mat &image, int div=64);
    static void colorReduce3(Mat &image, int div=64);
    static void colorReduce4(Mat &image, int div=64);
    static void colorReduce5(Mat &image, int div=64);
    static void colorReduce6(Mat &image, int div=64);
    static void colorReduce7(Mat &image, int div=64);
    static void colorReduce8(Mat &image, int div=64);
    static void colorReduce9(Mat &image, int div=64);
    static void colorReduce10(Mat &image, int div=64);
    static void colorReduce11(Mat &image, int div=64);
    static void colorReduce12(const Mat &image, Mat &result, int div=64);
    static void colorReduce13(Mat &image, int div=64);
};

#endif // IMAGEOPERA_H
