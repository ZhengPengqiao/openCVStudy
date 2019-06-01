#include "imageopera.h"

ImageOpera::ImageOpera()
{

}


/**
 * @brief ImageOpera::colorReduce0 : 利用.ptr 和 []
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce0(Mat &image, int div) {

    int nl= image.rows; //行数
    int nc= image.cols * image.channels(); //每行元素的总元素数量

    for (int j=0; j<nl; j++)
    {

        uchar* data= image.ptr<uchar>(j);

        for (int i=0; i<nc; i++)
        {
            data[i]= data[i]/div*div + div/2;
        } //单行处理结束
    }
}


/**
 * @brief ImageOpera::colorReduce0 : 利用 .ptr 和 * ++
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce1(Mat &image, int div) {

    int nl= image.rows; //行数
    int nc= image.cols * image.channels(); //每行元素的总元素数量

    for (int j=0; j<nl; j++)
    {

        uchar* data= image.ptr<uchar>(j);

        for (int i=0; i<nc; i++)
        {
            *data++= *data/div*div + div/2;
        } //单行处理结束
    }
}

/**
 * @brief ImageOpera::colorReduce0 : 利用.ptr 和 * ++ 以及模操作
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce2(Mat &image, int div) {

    int nl= image.rows; //行数
    int nc= image.cols * image.channels(); //每行元素的总元素数量

    for (int j=0; j<nl; j++)
    {

        uchar* data= image.ptr<uchar>(j);

        for (int i=0; i<nc; i++)
        {
            int v= *data;
            *data++= v - v%div + div/2;
        } //单行处理结束
    }
}


/**
 * @brief ImageOpera::colorReduce0 : 利用.ptr 和 * ++ 以及位操作
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce3(Mat &image, int div) {

    int nl= image.rows; //行数
    int nc= image.cols * image.channels(); //每行元素的总元素数量
    int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
    //掩码值
    uchar mask= 0xFF<<n; // e.g. 对于 div=16, mask= 0xF0

    for (int j=0; j<nl; j++) {

        uchar* data= image.ptr<uchar>(j);

        for (int i=0; i<nc; i++) {
            *data++= *data&mask + div/2;
        }  //单行处理结束
    }
}


/**
 * @brief ImageOpera::colorReduce0 : 利用指针算术运算
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce4(Mat &image, int div) {

    int nl= image.rows; //行数
    int nc= image.cols * image.channels(); //每行元素的总元素数量
    int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
    int step= image.step; //有效宽度
    //掩码值
    uchar mask= 0xFF<<n; // e.g. 对于 div=16, mask= 0xF0

    //获取指向图像缓冲区的指针
    uchar *data= image.data;

    for (int j=0; j<nl; j++)
    {

        for (int i=0; i<nc; i++)
        {
            *(data+i)= *data&mask + div/2;
        } //单行处理结束

        data+= step;  // next line
    }
}

/**
 * @brief ImageOpera::colorReduce0 : 利用 .ptr 和 * ++以及位运算、image.cols * image.channels()
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce5(Mat &image, int div) {

    int nl= image.rows; //行数
    int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
    //掩码值
    uchar mask= 0xFF<<n; // e.g. 例如div=16, mask= 0xF0

    for (int j=0; j<nl; j++)
    {

        uchar* data= image.ptr<uchar>(j);

        for (int i=0; i<image.cols * image.channels(); i++)
        {
            *data++= *data&mask + div/2;
        } //单行处理结束
    }
}


/**
 * @brief ImageOpera::colorReduce0 : 利用.ptr 和 * ++ 以及位运算(continuous)
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce6(Mat &image, int div) {

    int nl= image.rows; //行数
    int nc= image.cols * image.channels(); //每行元素的总元素数量

    if (image.isContinuous())
    {
        //无填充像素
        nc= nc*nl;
        nl= 1;  // 为一维数列
    }

    int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
    //掩码值
    uchar mask= 0xFF<<n; // e.g. 比如div=16, mask= 0xF0

    for (int j=0; j<nl; j++) {

        uchar* data= image.ptr<uchar>(j);

        for (int i=0; i<nc; i++) {
            *data++= *data&mask + div/2;
        } //单行处理结束
    }
}


/**
 * @brief ImageOpera::colorReduce0 : 利用 .ptr 和 * ++ 以及位运算 (continuous+channels)
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce7(Mat &image, int div) {

    int nl= image.rows; //行数
    int nc= image.cols ; //列数

    if (image.isContinuous())
    {
        //无填充像素
        nc= nc*nl;
        nl= 1;  // 为一维数组
    }

    int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
    //掩码值
    uchar mask= 0xFF<<n; // e.g. 比如div=16, mask= 0xF0

    for (int j=0; j<nl; j++) {

        uchar* data= image.ptr<uchar>(j);

        for (int i=0; i<nc; i++) {
            *data++= *data&mask + div/2;
            *data++= *data&mask + div/2;
            *data++= *data&mask + div/2;
        } //单行处理结束
    }
}


/**
 * @brief ImageOpera::colorReduce0 : 利用Mat_ iterator
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce8(Mat &image, int div) {

    //获取迭代器
    Mat_<Vec3b>::iterator it= image.begin<Vec3b>();
    Mat_<Vec3b>::iterator itend= image.end<Vec3b>();

    for ( ; it!= itend; ++it) {
        (*it)[0]= (*it)[0]/div*div + div/2;
        (*it)[1]= (*it)[1]/div*div + div/2;
        (*it)[2]= (*it)[2]/div*div + div/2;
    }//单行处理结束
}


/**
 * @brief ImageOpera::colorReduce0 : 利用Mat_ iterator以及位运算
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce9(Mat &image, int div) {

    // div必须是2的幂
    int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
    //掩码值
    uchar mask= 0xFF<<n; // e.g. 比如 div=16, mask= 0xF0

    // 获取迭代器
    Mat_<Vec3b>::iterator it= image.begin<Vec3b>();
    Mat_<Vec3b>::iterator itend= image.end<Vec3b>();

    //扫描所有元素
    for ( ; it!= itend; ++it)
    {
        (*it)[0]= (*it)[0]&mask + div/2;
        (*it)[1]= (*it)[1]&mask + div/2;
        (*it)[2]= (*it)[2]&mask + div/2;
    }//单行处理结束
}


/**
 * @brief ImageOpera::colorReduce0 : 利用Mat Iterator_
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce10(Mat &image, int div) {

    //获取迭代器
    Mat_<Vec3b> cimage= image;
    Mat_<Vec3b>::iterator it=cimage.begin();
    Mat_<Vec3b>::iterator itend=cimage.end();

    for ( ; it!= itend; it++) {
        (*it)[0]= (*it)[0]/div*div + div/2;
        (*it)[1]= (*it)[1]/div*div + div/2;
        (*it)[2]= (*it)[2]/div*div + div/2;
    }
}


/**
 * @brief ImageOpera::colorReduce0 : 利用动态地址计算配合at
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce11(Mat &image, int div) {

    int nl= image.rows; //行数
    int nc= image.cols; //列数

    for (int j=0; j<nl; j++)
    {
        for (int i=0; i<nc; i++)
        {
            image.at<Vec3b>(j,i)[0]=	 image.at<Vec3b>(j,i)[0]/div*div + div/2;
            image.at<Vec3b>(j,i)[1]=	 image.at<Vec3b>(j,i)[1]/div*div + div/2;
            image.at<Vec3b>(j,i)[2]=	 image.at<Vec3b>(j,i)[2]/div*div + div/2;
        } //单行处理结束
    }
}


/**
 * @brief ImageOpera::colorReduce0 : 利用图像的输入与输出
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce12(const Mat &image, Mat &result, int div) {

    int nl= image.rows; //行数
    int nc= image.cols ; //列数

    //准备好初始化后的Mat给输出图像
    result.create(image.rows,image.cols,image.type());

    //创建无像素填充的图像
    nc= nc*nl;
    nl= 1;  //单维数组

    int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
    //掩码值
    uchar mask= 0xFF<<n; // e.g.比如div=16, mask= 0xF0

    for (int j=0; j<nl; j++) {

        uchar* data= result.ptr<uchar>(j);
        const uchar* idata= image.ptr<uchar>(j);

        for (int i=0; i<nc; i++) {
            *data++= (*idata++)&mask + div/2;
            *data++= (*idata++)&mask + div/2;
            *data++= (*idata++)&mask + div/2;
        } //单行处理结束
    }
}


/**
 * @brief ImageOpera::colorReduce0 : 利用操作符重载
 * @param image : 待处理的图片
 * @param div : 需要缩减颜色的等级
 */
void ImageOpera::colorReduce13(Mat &image, int div) {

    int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
    //掩码值
    uchar mask= 0xFF<<n; // e.g. 比如div=16, mask= 0xF0

    //进行色彩还原
    image=(image&Scalar(mask,mask,mask))+Scalar(div/2,div/2,div/2);
}
