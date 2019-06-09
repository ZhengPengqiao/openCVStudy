#include "mibase.h"
#include <QMessageBox>
#include <QWidget>
#include <QPushButton>
#include <QFrame>
#include <QSpacerItem>

MIBase::MIBase()
{
    modelItemName = "this text";
    page = new QWidget();
    vboxlayout = new QVBoxLayout(page);

    submit = new QPushButton("进行效果处理");
    connect(submit, &QPushButton::clicked, this, &MIBase::onSubmitClicked);
    vboxlayout->addWidget(submit);

    QFrame *line = new QFrame(page);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    vboxlayout->addWidget(line);
}


/**
 * @brief MIBase::getModelItemName : 获取模块名字
 * @return  : 返回模块名字
 */
QString MIBase::getModelItemName() const
{
    return modelItemName;
}


/**
 * @brief MIBase::setModelItemName : 设置模块名字
 * @param value : 模块的名字
 */
void MIBase::setModelItemName(const QString &value)
{
    modelItemName = value;
}


/**
 * @brief MIBase::addSubPage : 添加子页面到当前页面
 * @param widget : 需要添加的子页面
 */
void MIBase::addSubPage(QWidget *widget)
{
     vboxlayout->addWidget(widget);
}


/**
 * @brief MIBase::onSubmitClicked : 点击submit会调用的函数
 */
void MIBase::onSubmitClicked()
{
    qDebug() << "base onSubmitClicked: " << this->modelItemName;
}



QImage MIBase::cvMat2QImage(const cv::Mat& mat)
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

cv::Mat MIBase::QImage2cvMat(QImage image)
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

