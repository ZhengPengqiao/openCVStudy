#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QByteArray>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Mat src_image; //保存文件读取数据
    Mat dst_image; //转换后显示用的变量
    QImage qimage;
    QByteArray m_data;

    QString fm_mode;
    int s_width;
    int s_height;
    float pixel_size;

    QString fileName;

    QImage cvMat2QImage(const cv::Mat& mat);
    Mat QImage2cvMat(QImage image);
    void showImage();
    float getFormatPixelSize(QString fm_mode);

public slots:
    void open_clicked();
    void exit_clicked();
    void format_IndexChanged(QString str);
    void size_IndexChanged(QString str);
    void spin_width_valChange(int val);
    void spin_height_valChange(int val);

protected:
    //拖动进入事件
    void dragEnterEvent(QDragEnterEvent*event);
    void dropEvent(QDropEvent*event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
