//---------------------------------【头文件、命名空间包含部分】-------------------------------
//		描述：包含程序所使用的头文件和命名空间
//------------------------------------------------------------------------------------------------
#include "opencv2/opencv.hpp"
#include <time.h>
using namespace cv;
using namespace std;

//-----------------------------------【main( )函数】--------------------------------------------
//	描述：控制台应用程序的入口函数，我们的程序从这里开始
//-----------------------------------------------------------------------------------------------
int main( )
{
    //初始化
    FileStorage fs("test.yaml", FileStorage::WRITE);

    //开始文件写入
    fs << "frameCount" << 5;
    time_t rawtime; time(&rawtime);
    fs << "calibrationDate" << asctime(localtime(&rawtime));
    Mat cameraMatrix = (Mat_<double>(3,3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
    Mat distCoeffs = (Mat_<double>(5,1) << 0.1, 0.01, -0.001, 0, 0);
    fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
    fs << "features" << "[";
    for( int i = 0; i < 3; i++ )
    {
        int x = rand() % 640;
        int y = rand() % 480;
        uchar lbp = rand() % 256;

        fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";
        for( int j = 0; j < 8; j++ )
            fs << ((lbp >> j) & 1);
        fs << "]" << "}";
    }
    fs << "]";
    fs.release();

    printf("\n文件读写完毕，请在工程目录下查看生成的文件~\n");


    //初始化
    FileStorage fs2("test.yaml", FileStorage::READ);

    // 第一种方法，对FileNode操作
    int frameCount = (int)fs2["frameCount"];

    std::string date;
    // 第二种方法，使用FileNode运算符> >
    fs2["calibrationDate"] >> date;

    Mat cameraMatrix2, distCoeffs2;
    fs2["cameraMatrix"] >> cameraMatrix2;
    fs2["distCoeffs"] >> distCoeffs2;

    cout << "frameCount: " << frameCount << endl
        << "calibration date: " << date << endl
        << "camera matrix: " << cameraMatrix2 << endl
        << "distortion coeffs: " << distCoeffs2 << endl;

    FileNode features = fs2["features"];
    FileNodeIterator it = features.begin(), it_end = features.end();
    int idx = 0;
    std::vector<uchar> lbpval;

    //使用FileNodeIterator遍历序列
    for( ; it != it_end; ++it, idx++ )
    {
        cout << "feature #" << idx << ": ";
        cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";
        // 我们也可以使用使用filenode > > std::vector操作符很容易的读数值阵列
        (*it)["lbp"] >> lbpval;
        for( int i = 0; i < (int)lbpval.size(); i++ )
            cout << " " << (int)lbpval[i];
        cout << ")" << endl;
    }
    fs2.release();

    printf("\n文件读取完毕，请输入任意键结束程序~\n");

    waitKey(0);

    return 0;
}
