#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollArea>
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QDataStream>
#include <QFile>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->scrollArea->setObjectName(QStringLiteral("scrollArea"));
    ui->scrollArea->setWidgetResizable(false);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    ui->scrollArea->setAlignment(Qt::AlignCenter);
    p_data = 0;
    frame_num = 0;

    fm_mode = "FM_UYVY";
    pixel_size = 2;
    s_width = 320;
    s_height = 240;
    m_data.resize(s_height*s_width*pixel_size);

    showImage();


    ui->combo_fm->setCurrentText(fm_mode);
    ui->combo_size->setCurrentText(QString("%1x%2").arg(s_width).arg(s_height));
    ui->statusbar->showMessage(fileName + QString(" FM_Mode:%1 %2x%3 pix_size=%4 data_size=%5")
                               .arg(fm_mode)
                               .arg(s_width).arg(s_height)
                               .arg(pixel_size)
                               .arg(s_width*s_height*pixel_size));
    ui->spin_width->setValue(s_width);
    ui->spin_height->setValue(s_height);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showYuvStream()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showYuvStream()
{
    frame_num++;
    ui->spinBox_frame_num->setValue(frame_num);
    showImage();
}


void MainWindow::showImage()
{

    qDebug() << "mdata count: " << m_data.count();
    if( fm_mode == "FM_ForFileFormat" ) {
        ui->label->setPixmap(QPixmap(fileName));
        ui->label->setGeometry(0,0,ui->label->sizeHint().width(),ui->label->sizeHint().height());
        ui->scrollAreaWidgetContents->resize(ui->label->sizeHint());
        ui->statusbar->showMessage(fileName + QString(" FM_Mode:%1 (%2x%3)")
                                   .arg(fm_mode)
                                   .arg(ui->label->width())
                                   .arg(ui->label->height())
                                   );
        return;
    }


    if( pixel_size < 2 )
    {
        src_image.release();
        src_image.create(s_height*pixel_size, s_width, CV_8UC1);
    }
    else if( pixel_size == 2 )
    {
        src_image.release();
        src_image.create(s_height, s_width, CV_8UC2);
    }
    else if( pixel_size == 3 )
    {
        src_image.release();
        src_image.create(s_height, s_width, CV_8UC3);
    }
    else
    {
        qDebug() << "showImage cvtColor not Support " << pixel_size << " pixel_size";
        return;
    }

    src_image = Scalar(0, 0, 0);

    p_data = m_data.data();
    int offset = (frame_num*s_height*s_width*pixel_size);

    if( offset >= m_data.size() )
    {
        offset = 0;
        frame_num = 0;
        ui->spinBox_frame_num->setValue(frame_num);
    }

    qDebug() << "offset" << offset << frame_num << s_height << s_width << pixel_size;

    memcpy(src_image.data, p_data+offset,
           ((m_data.size()-offset)<(s_height*s_width*pixel_size)?m_data.size():(s_height*s_width*pixel_size)));

    qDebug() << "showImage" << "src w:" << src_image.cols << "h:" << src_image.rows << "type :" << src_image.type() << "pixel_size:" << pixel_size;

    if( fm_mode == "FM_BGRA" ) {
        cvtColor(src_image, dst_image, CV_BGRA2BGR, 3);
    } else if( fm_mode == "FM_RGBA" ) {
        cvtColor(src_image, dst_image, CV_RGBA2BGR, 3);
    } else if( fm_mode == "FM_GRAY" ) {
        cvtColor(src_image, dst_image, CV_GRAY2BGR, 3);
    } else if( fm_mode == "FM_BGR565" ) {
        cvtColor(src_image, dst_image, CV_BGR5652BGR, 3);
    } else if( fm_mode == "FM_BGR555" ) {
        cvtColor(src_image, dst_image, CV_BGR5552BGR, 3);
    } else if( fm_mode == "FM_XYZ" ) {
        cvtColor(src_image, dst_image, CV_XYZ2BGR, 3);
    } else if( fm_mode == "FM_YCrCb" ) {
        cvtColor(src_image, dst_image, CV_YCrCb2BGR, 3);
    } else if( fm_mode == "FM_BayerBG" ) {
        cvtColor(src_image, dst_image, CV_BayerBG2BGR, 3);
    } else if( fm_mode == "FM_BayerGB" ) {
        cvtColor(src_image, dst_image, CV_BayerGB2BGR, 3);
    } else if( fm_mode == "FM_BayerGR" ) {
        cvtColor(src_image, dst_image, CV_BayerGR2BGR, 3);
    } else if( fm_mode == "FM_HSV" ) {
        cvtColor(src_image, dst_image, CV_HSV2BGR, 3);
    } else if( fm_mode == "FM_Lab" ) {
        cvtColor(src_image, dst_image, CV_Lab2BGR, 3);
    } else if( fm_mode == "FM_Luv" ) {
        cvtColor(src_image, dst_image, CV_Luv2BGR, 3);
    } else if( fm_mode == "FM_YUV" ) {
        cvtColor(src_image, dst_image, CV_YUV2BGR, 3);
    } else if( fm_mode == "FM_NV12" ) {
        cvtColor(src_image, dst_image, CV_YUV2BGR_NV12, 3);
    } else if( fm_mode == "FM_NV21" ) {
        cvtColor(src_image, dst_image, CV_YUV2BGR_NV21, 3);
    } else if( fm_mode == "FM_YUV420sp" ) {
        cvtColor(src_image, dst_image, CV_YUV420sp2BGR, 3);
    } else if( fm_mode == "FM_YV12" ) {
        cvtColor(src_image, dst_image, CV_YUV2BGR_YV12, 3);
    } else if( fm_mode == "FM_IYUV" ) {
        cvtColor(src_image, dst_image, CV_YUV2BGR_IYUV, 3);
    } else if( fm_mode == "FM_I420" ) {
        cvtColor(src_image, dst_image, CV_YUV2BGR_I420, 3);
    } else if( fm_mode == "FM_YUV420p" ) {
        cvtColor(src_image, dst_image, CV_YUV420p2BGR, 3);
    } else if( fm_mode == "FM_UYVY" ) {
        cvtColor(src_image, dst_image, CV_YUV2BGR_UYVY, 3);
    } else if( fm_mode == "FM_Y422" ) {
        cvtColor(src_image, dst_image, CV_YUV2BGR_Y422, 3);
    } else if( fm_mode == "FM_UYNV" ) {
        cvtColor(src_image, dst_image, CV_YUV2BGR_UYNV, 3);
    } else if( fm_mode == "FM_YVYU" ) {
        cvtColor(src_image, dst_image, CV_YUV2BGR_YVYU, 3);
    } else if( fm_mode == "FM_YUYV" ) {
        cvtColor(src_image, dst_image, CV_YUV2BGR_YUYV, 3);
    } else if( fm_mode == "FM_YUNV" ) {
        cvtColor(src_image, dst_image, CV_YUV2BGR_YUNV, 3);
    }
    else
    {
        qDebug() << "showImage cvtColor not Support " << fm_mode << " format";
        return;
    }

    qDebug() << "showImage" <<  "dst w:" << dst_image.cols << "h:" << dst_image.rows << "type :" << dst_image.type();

    qimage = cvMat2QImage(dst_image);
    ui->label->setPixmap(QPixmap::fromImage(qimage));
    ui->label->setGeometry(0,0,ui->label->sizeHint().width(),ui->label->sizeHint().height());
    ui->scrollAreaWidgetContents->resize(ui->label->sizeHint());
    ui->statusbar->showMessage(fileName + QString(" FM_Mode:%1 (%2x%3) pix_size=%4 data_size=%5  "
                                       "--> dst (%6x%7)")
                               .arg(fm_mode)
                               .arg(s_width).arg(s_height)
                               .arg(pixel_size)
                               .arg(s_width*s_height*pixel_size)
                               .arg(dst_image.cols).arg(dst_image.rows));

}


void MainWindow::open_clicked()
{
    QImage qimage;
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog();
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开图片"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("Images(*.*)"));
    // 设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    //fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }

    if( fileNames.length() > 0 )
    {
        ui->statusbar->showMessage("Open: " + fileNames[0], 0);
        fileName = fileNames[0];

        //读文件
        QFile file(fileNames[0]);
        file.open(QIODevice::ReadOnly);
        qDebug() << "file name: " << fileNames[0];
        qDebug() << "file size: " << file.size();
        m_data = file.readAll();
        file.close();
    }
    else
    {
        qDebug() << " 未选择文件 ";
    }

    showImage();

}


void MainWindow::exit_clicked()
{
    exit(0);
}

void MainWindow::format_IndexChanged(QString str)
{
    fm_mode = str;
    pixel_size = getFormatPixelSize(str);
    qDebug() << "Format_Change:" << "fm_mode:" << fm_mode << "pixel_size:" << pixel_size;

    showImage();

}


void MainWindow::size_IndexChanged(QString str)
{
    if( str == "320x240" ) {
        s_width = 320; s_height = 240;
    }
    else if( str == "640x480" ) {
        s_width = 640; s_height = 480;
    }
    else if( str == "720x480" ) {
        s_width = 720; s_height = 480;
    }
    else if( str == "720x576" ) {
        s_width = 720; s_height = 576;
    }
    else if( str == "800x480" ) {
        s_width = 800; s_height = 480;
    }
    else if( str == "800x576" ) {
        s_width = 800; s_height = 576;
    }
    else if( str == "800x720" ) {
        s_width = 800; s_height = 720;
    }
    else if( str == "1024x600" ) {
        s_width = 1024; s_height = 600;
    }
    else if( str == "1280x720" ) {
        s_width = 1280; s_height = 720;
    }
    else if( str == "1440x960" ) {
        s_width = 1440; s_height = 960;
    }
    else if( str == "2560x1440" ) {
        s_width = 2560; s_height = 1440;
    }

    qDebug() << "Size_Change:" << "s_width:" << s_width << "s_height:" << s_height;

    ui->spin_width->setValue(s_width);
    ui->spin_height->setValue(s_height);

    showImage();

}

float MainWindow::getFormatPixelSize(QString fm_mode)
{
    float p_size = 1.5;

    if( fm_mode == "FM_BGRA" ) {
        p_size = 4;
    } else if( fm_mode == "FM_RGBA" ) {
        p_size = 4;
    } else if( fm_mode == "FM_GRAY" ) {
        p_size = 1;
    } else if( fm_mode == "FM_BGR565" ) {
        p_size = 2;
    } else if( fm_mode == "FM_BGR555" ) {
        p_size = 2;
    } else if( fm_mode == "FM_XYZ" ) {
        p_size = 3;
    } else if( fm_mode == "FM_YCrCb" ) {
        p_size = 3;
    } else if( fm_mode == "FM_BayerBG" ) {
        p_size = 1;
    } else if( fm_mode == "FM_BayerGB" ) {
        p_size = 1;
    } else if( fm_mode == "FM_BayerGR" ) {
        p_size = 1;
    } else if( fm_mode == "FM_HSV" ) {
        p_size = 3;
    } else if( fm_mode == "FM_Lab" ) {
        p_size = 3;
    } else if( fm_mode == "FM_Luv" ) {
        p_size = 3;
    } else if( fm_mode == "FM_YUV" ) {
        p_size = 3;
    } else if( fm_mode == "FM_NV12" ) {
        p_size = 1.5;
    } else if( fm_mode == "FM_NV21" ) {
        p_size = 1.5;
    } else if( fm_mode == "FM_YUV420sp" ) {
        p_size = 1.5;
    } else if( fm_mode == "FM_YV12" ) {
        p_size = 1.5;
    } else if( fm_mode == "FM_IYUV" ) {
        p_size = 1.5;
    } else if( fm_mode == "FM_I420" ) {
        p_size = 1.5;
    } else if( fm_mode == "FM_YUV420p" ) {
        p_size = 1.5;
    } else if( fm_mode == "FM_UYVY" ) {
        p_size = 2;
    } else if( fm_mode == "FM_Y422" ) {
        p_size = 2;
    } else if( fm_mode == "FM_UYNV" ) {
        p_size = 2;
    } else if( fm_mode == "FM_YVYU" ) {
        p_size = 2;
    } else if( fm_mode == "FM_YUYV" ) {
        p_size = 2;
    } else if( fm_mode == "FM_YUNV" ) {
        p_size = 2;
    }
    else
    {
        qDebug() << "showImage cvtColor not Support " << fm_mode << " format";
    }

    return p_size;
}


QImage MainWindow::cvMat2QImage(const cv::Mat& mat)
{
    if(mat.type() == CV_8UC1)
    {
        qDebug() << "cvMat2QImage CV_8UC1";
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    else if(mat.type() == CV_8UC2)
    {
        qDebug() << "cvMat2QImage CV_8UC2";
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB16);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC3)
    {
        qDebug() << "cvMat2QImage CV_8UC3";
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "cvMat2QImage CV_8UC4";
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << mat.type() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

cv::Mat MainWindow::QImage2cvMat(QImage image)
{
    cv::Mat mat;
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    default:
        QMessageBox::warning(NULL,"warning","format is not right");
        exit(0);
    }
    return mat;
}


// 当用户放下这个文件后，就会触发dropEvent事件
void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;

    fileName = event->mimeData()->urls()[0].toLocalFile();
    ui->statusbar->showMessage("Open: " + fileName, 0);

    //读文件
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    qDebug() << "file name: " << fileName;
    qDebug() << "file size: " << file.size();
    m_data = file.readAll();
    file.close();

    showImage();
}

void MainWindow::dragEnterEvent(QDragEnterEvent*event)
{
    QFileInfo fileinfo(event->mimeData()->urls()[0].toLocalFile());
    if( fileinfo.isFile() )
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();//否则不接受鼠标事件
    }
}


void MainWindow::spin_width_valChange(int val)
{
    s_width = val;

    qDebug() << "s_width:" << s_width << "s_height:" << s_height;

    showImage();
}


void MainWindow::spin_frame_num_valChange(int val)
{
    frame_num = val;

    qDebug() << "frame_num:" << frame_num;

    showImage();
}


void MainWindow::spin_height_valChange(int val)
{
    s_height = val;

    qDebug() << "s_width:" << s_width << "s_height:" << s_height;

    showImage();
}



void MainWindow::pushButton_stream_ctrl_onclick(bool val)
{
    if( val )
    {
        ui->pushButton_stream_ctrl->setText("播放(点击关闭)");
        timer->start(1000/ui->spinBox_fps->value());      //  停止读取数据。
    }
    else
    {
        ui->pushButton_stream_ctrl->setText("播放(点击开始)");
        timer->stop();      //  停止读取数据。
    }
}
