#include "numbercheckfrom.h"
#include "ui_numbercheckfrom.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

NumberCheckFrom::NumberCheckFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumberCheckFrom)
{
    ui->setupUi(this);

    template_image = "../assert/num_recognition/sans/template.jpg";
    recongition_image = "../assert/num_recognition/sans/template.jpg";
    ui->lineEdit_imagePath->setText(template_image);
    ui->lineEdit_recongitionPath->setText(recongition_image);
    ui->label_template_image->setPixmap(QPixmap(template_image).scaled(200,50));
    ui->label_reconition_image->setPixmap(QPixmap(recongition_image).scaled(200,50));

}

NumberCheckFrom::~NumberCheckFrom()
{
    delete ui;
}


void NumberCheckFrom::pushButton_create_complate_onclick()
{
    //输入要识别的图片，并显示
    Mat srcImage = imread(template_image.toStdString().c_str());

    // 对图像进行处理，转化为灰度图然后再转为二值图
    Mat grayImage;
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    Mat binImage;
    //第4个参数为CV_THRESH_BINARY_INV是因为我的输入原图为白底黑字
    //若为黑底白字则选择CV_THRESH_BINARY即可
    threshold(grayImage, binImage, 100, 255, CV_THRESH_BINARY_INV);

    //寻找轮廓，必须指定为寻找外部轮廓，不然一个数字可能有多个轮廓组成，比如4,6,8,9等数字
    Mat conImage = Mat::zeros(binImage.size(), binImage.type());
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    //指定CV_RETR_EXTERNAL寻找数字的外轮廓
    findContours(binImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //绘制轮廓
    drawContours(conImage, contours, -1, 255);
    //将每个数字，分离开，保存到容器中
    vector<myRect> sort_rect;
    for (int i = 0; i < contours.size(); i++)
    {
        //boundingRect返回轮廓的外接矩阵
        Rect tempRect = boundingRect(contours[i]);
        sort_rect.push_back(tempRect);
    }

    //对矩形进行排序，因为轮廓的顺序不一定是数字真正的顺序
    for (int  i = 0; i < sort_rect.size(); i++)
    {
        for (int j = i + 1; j < sort_rect.size(); j++)
        {
            if (sort_rect[j] < sort_rect[i])
            {
                myRect temp = sort_rect[j];
                sort_rect[j] = sort_rect[i];
                sort_rect[i] = temp;
            }
        }
    }


    /*加载模板，若没有则需自己新建一个*/
    // 新建,运行一次就好，不过制作模板的材料为0-9十个数字的图像
    for (int i = 0; i < 10; i++)
    {
        Mat ROI = conImage(sort_rect[i].getRect());
        Mat dstROI;
        cv::resize(ROI, dstROI, Size(40, 50),0, 0, INTER_NEAREST);
        char name[64];
        sprintf(name, "../assert/num_recognition/image/%d.jpg", i);
        imwrite(name, dstROI);
    }
}



void NumberCheckFrom::pushButton_recognition_onclick()
{
    int i,j;
    qDebug() << recongition_image.toStdString().c_str();
    //输入要识别的图片，并显示
    Mat srcImage = imread(recongition_image.toStdString().c_str());

    // 对图像进行处理，转化为灰度图然后再转为二值图
    Mat grayImage;
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    Mat binImage;
    //第4个参数为CV_THRESH_BINARY_INV是因为我的输入原图为白底黑字
    //若为黑底白字则选择CV_THRESH_BINARY即可
    threshold(grayImage, binImage, 100, 255, CV_THRESH_BINARY_INV);

    //寻找轮廓，必须指定为寻找外部轮廓，不然一个数字可能有多个轮廓组成，比如4,6,8,9等数字
    Mat conImage = Mat::zeros(binImage.size(), binImage.type());
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    //指定CV_RETR_EXTERNAL寻找数字的外轮廓
    findContours(binImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //绘制轮廓
    drawContours(conImage, contours, -1, 255);

    //将每个数字，分离开，保存到容器中
    vector<myRect> sort_rect;
    for (int i = 0; i < contours.size(); i++)
    {
        //boundingRect返回轮廓的外接矩阵
        Rect tempRect = boundingRect(contours[i]);
        sort_rect.push_back(tempRect);
    }

    //对矩形进行排序，因为轮廓的顺序不一定是数字真正的顺序
    for (int  i = 0; i < sort_rect.size(); i++)
    {
        for (int j = i + 1; j < sort_rect.size(); j++)
        {
            if (sort_rect[j] < sort_rect[i])
            {
                myRect temp = sort_rect[j];
                sort_rect[j] = sort_rect[i];
                sort_rect[i] = temp;
            }
        }
    }


    /*加载模板，若没有则需自己新建一个*/
    vector<Mat> myTemplate;
    for (int i = 0; i < 10; i++)
    {
        char name[64];
        sprintf(name, "../assert/num_recognition/image/%d.jpg", i);
        Mat temp = imread(name, 0);
        myTemplate.push_back(temp);
    }

    clearLayout(ui->gridLayout_num_image->layout());

    //按顺序取出和分割数字
    vector<Mat> myROI;
    for (int i = 0; i < sort_rect.size(); i++)
    {
        Mat ROI;
        ROI = conImage(sort_rect[i].getRect());
        Mat dstROI = Mat::zeros(myTemplate[0].size(),myTemplate[0].type());
        cv::resize(ROI, dstROI, myTemplate[0].size(), 0, 0, INTER_NEAREST);
        myROI.push_back(dstROI);
    }

    //进行比较,将图片与模板相减，然后求全部像素和，和最小表示越相似，进而完成匹配
    vector<int> seq;//顺序存放识别结果
    for (i = 0; i < myROI.size(); i++)
    {
        Mat subImage_ret;
        int sum = 0;
        int min = 100000;
        int min_seq = 0;//记录最小的和对应的数字
        for (j = 0; j < 10; j++)
        {
            Mat subImage;
            //计算两个图片的差值
            absdiff(myROI[i], myTemplate[j], subImage);
            sum = getPiexSum(subImage);
            if (sum < min)
            {
                min = sum;
                min_seq = j;
                subImage_ret = subImage;
            }
            sum = 0;
        }
        seq.push_back(min_seq);

        QLabel *label_1 = new QLabel();
        QLabel *label_2 = new QLabel();
        QLabel *label_3 = new QLabel();
        QLabel *label_4 = new QLabel();
        label_1->setText(QString("absdiff %1").arg(min_seq));
        label_2->setPixmap(QPixmap::fromImage(cvMat2QImage(myROI[i])));
        label_3->setPixmap(QPixmap::fromImage(cvMat2QImage(myTemplate[min_seq])));
        label_4->setPixmap(QPixmap::fromImage(cvMat2QImage(subImage_ret)));
        ui->gridLayout_num_image->addWidget(label_1,i,0);
        ui->gridLayout_num_image->addWidget(label_2,i,1);
        ui->gridLayout_num_image->addWidget(label_3,i,2);
        ui->gridLayout_num_image->addWidget(label_4,i,3);
    }

    //输出结果
    QString str;
    for (int i = 0; i < seq.size(); i++)
    {
        str += QString("%1").arg(seq[i]);
    }

    ui->lineEdit_resut->setText(str);
}

//求图片的像素和
int NumberCheckFrom::getPiexSum(Mat &image)
{
    int sum = 0;
    for (int i = 0; i < image.cols; i++)
    {
        for (int j = 0; j < image.rows; j++)
        {
            sum += image.at<uchar>(j, i);
        }
    }
    return sum;
}



void NumberCheckFrom::pushButton_select_template_onclick()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog();
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开图片"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
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
        template_image = fileNames[0];
        ui->lineEdit_imagePath->setText(fileNames[0]);
        ui->label_template_image->setPixmap(QPixmap(fileNames[0]).scaled(200,50));
    }
    else
    {
        qDebug() << " 未选择文件 ";
    }
}



void NumberCheckFrom::pushButton_select_recognition_onclick()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog();
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开图片"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
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
        recongition_image = fileNames[0];
        ui->label_reconition_image->setPixmap(QPixmap(fileNames[0]).scaled(200,50));
        ui->lineEdit_recongitionPath->setText(recongition_image);
    }
    else
    {
        qDebug() << " 未选择文件 ";
    }
}


QImage NumberCheckFrom::cvMat2QImage(const cv::Mat& mat)
{
    if(mat.type() == CV_8UC1)
    {
        qDebug() << "CV_8UC1";
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
        qDebug() << "CV_8UC2";
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB16);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC3)
    {
        qDebug() << "CV_8UC3";
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << mat.type() << "ERROR: Mat could not be converted to QImage.";
        qDebug() << "CV_8UC1:" << CV_8UC1 << "CV_8UC2:" << CV_8UC2 << "CV_8UC3:" << CV_8UC3 << "CV_8UC3:" << CV_8UC4;
        return QImage();
    }
}

cv::Mat NumberCheckFrom::QImage2cvMat(QImage image)
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


void NumberCheckFrom::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0)) != 0){
        //删除widget
        if(item->widget()){
            delete item->widget();
            //item->widget()->deleteLater();
        }
        //删除子布局
        QLayout *childLayout = item->layout();
        if(childLayout){
            clearLayout(childLayout);
        }
        delete item;
    }
}
