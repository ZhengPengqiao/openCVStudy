
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->scrollArea->setWidgetResizable(false);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    ui->scrollArea->setAlignment(Qt::AlignCenter);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(ReadFrame()));

    getVideoMode(ui->combo_Video->currentText());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadFrame()
{
    if(capture.isOpened())
    {
        capture >> frame;
        if(!frame.empty())
        {
            cvtColor(frame, result_frame, CV_BGR2RGB);     //  OpenCV中Mat读入的图像是BGR格式，要转换为RGB格式
            cv::resize(result_frame, result_frame, Size(640, 480));

            // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
            QImage image((const uchar*)result_frame.data, result_frame.cols, result_frame.rows, QImage::Format_RGB888);
            ui->label->setPixmap(QPixmap::fromImage(image));    //  将图片显示到label上
            ui->label->resize( ui->label->pixmap()->size());    //  将label控件resize到fame的尺寸
            ui->label->setGeometry(0,0,ui->label->sizeHint().width(),ui->label->sizeHint().height());
            ui->scrollAreaWidgetContents->resize(ui->label->sizeHint());
        }
    }
}

void MainWindow::on_button_OpenVideo_clicked()
{
    if( video_mode == 1 )
    {
        if( file_name.isEmpty() )
        {
            file_name = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video File(*.avi *.mp4 *.h264)"));
            ui->statusBar->showMessage("file_name :" + file_name, 0);
        }
        capture.open(file_name.toStdString());
        qDebug() << "on_button_OpenVideo_clicked FileName:" << file_name;
    }
    else
    {
        capture.open(video_number);
        qDebug() << "on_button_OpenVideo_clicked VideoNum:" << video_number;
    }

}


void MainWindow::on_button_CloseVideo_clicked()
{
    //  释放内存；
    capture.release();
    frame.release();

    ui->statusBar->showMessage("CloseVideo", 0);
    qDebug() << "on_button_CloseVideo_clicked";
}

void MainWindow::on_button_StartVideo_clicked()
{
    timer->start(25);   //  开始计时，每隔25毫秒更新一次，超时则发出timeout()信号

    ui->statusBar->showMessage("StartVideo", 0);
    qDebug() << "on_button_StartVideo_clicked";
}

void MainWindow::on_button_StopVideo_clicked()
{
    timer->stop();      //  停止读取数据。

    ui->statusBar->showMessage("StopVideo", 0);
    qDebug() << "on_button_StopVideo_clicked";
}

void MainWindow::on_combo_Video_Change(QString str)
{
    ui->statusBar->showMessage(str, 0);
    getVideoMode(str);
    qDebug() << "on_combo_Video_Change" << str;
}

void MainWindow::getVideoMode(QString str)
{
    if( str == "Camera Video0" )
    {
        video_mode = 0;
        video_number = 0;
        ui->statusBar->showMessage("Camera Video0", 0);
    }
    else if( str == "Camera Video1" )
    {
        video_mode = 0;
        video_number = 1;
        ui->statusBar->showMessage("Camera Video1", 0);
    }
    else if( str == "Camera Video2" )
    {
        video_mode = 0;
        video_number = 2;
        ui->statusBar->showMessage("Camera Video2", 0);
    }
    else if( str == "File Video" )
    {
        video_mode = 1;
        file_name = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video File(*.avi *.mp4 *.h264)"));
        ui->statusBar->showMessage("File Video file_name :" + file_name, 0);
    }

}
