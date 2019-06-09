#include "milaplacian.h"


#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QApplication>
#include <QSizePolicy>
#include <QMouseEvent>
#include <QComboBox>

#define MINAME "边沿检测Laplacian"

MILaplacian::MILaplacian()
{
    this->setModelItemName(MINAME);

    // 当前模块的顶级布局和控件
    subPage = new QWidget();
    vBoxLayout = new QVBoxLayout(subPage);
    vBoxLayout->setObjectName(QStringLiteral("vBoxLayout"));

    // 文件选择的UI布局
    fileSelectHBoxLayout = new QHBoxLayout();
    fileSelectHBoxLayout->setObjectName(QStringLiteral("hBoxLayout"));
    fileSelectLabel = new QLabel(subPage);
    fileSelectLabel->setObjectName(QStringLiteral("fileSelectLabel"));
    fileSelectPath = new QLineEdit(subPage);
    fileSelectPath->setObjectName(QStringLiteral("fileSelectPath"));
    fileSelectButton = new QPushButton(subPage);
    fileSelectButton->setObjectName(QStringLiteral("fileSelectButton"));
    fileSelectHBoxLayout->addWidget(fileSelectLabel);
    fileSelectHBoxLayout->addWidget(fileSelectPath);
    fileSelectHBoxLayout->addWidget(fileSelectButton);
    vBoxLayout->addLayout(fileSelectHBoxLayout);

    ctrlHBoxLayout = new QHBoxLayout();
    ctrlHBoxLayout->setObjectName(QStringLiteral("ctrlHBoxLayout"));
    imShowChechBox = new QCheckBox(subPage);
    imShowChechBox->setObjectName(QStringLiteral("imShowChechBox"));
    ctrlHBoxLayout->addWidget(imShowChechBox);
    vBoxLayout->addLayout(ctrlHBoxLayout);

    // 当前模块的Area区域
    scrollArea = new QScrollArea(subPage);
    scrollArea->setObjectName(QStringLiteral("scrollArea"));
    scrollArea->setWidgetResizable(false);
    scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
    scrollAreaWidgetContents->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    scrollArea->setWidget(scrollAreaWidgetContents);
    vBoxLayout->addWidget(scrollArea);

    // 当前模块的Area区域, 显示原图,效果图
    formLayout = new QFormLayout(scrollAreaWidgetContents);
    formLayout->setSpacing(6);
    formLayout->setContentsMargins(1, 1, 1, 1);
    formLayout->setObjectName(QStringLiteral("formLayout"));

    // 当前模块的Area区域, 显示原图
    label_src = new QLabel(scrollAreaWidgetContents);
    label_src->setObjectName(QStringLiteral("label_src"));
    imageLabel_src = new QLabel(scrollAreaWidgetContents);
    imageLabel_src->setObjectName(QStringLiteral("imageLabel_src"));
    formLayout->insertRow(1, label_src, imageLabel_src);
    // 当前模块的Area区域, 显示gray
    label_gray = new QLabel(scrollAreaWidgetContents);
    label_gray->setObjectName(QStringLiteral("label_gray"));
    imageLabel_gray = new QLabel(scrollAreaWidgetContents);
    imageLabel_gray->setObjectName(QStringLiteral("imageLabel_gray"));
    formLayout->insertRow(2, label_gray, imageLabel_gray);
    // 当前模块的Area区域, 显示效果图
    label_abs = new QLabel(scrollAreaWidgetContents);
    label_abs->setObjectName(QStringLiteral("label_abs"));
    imageLabel_abs = new QLabel(scrollAreaWidgetContents);
    imageLabel_abs->setObjectName(QStringLiteral("imageLabel_abs"));
    formLayout->insertRow(4, label_abs, imageLabel_abs);


    // 初始化当前模块控件的内容
    retranslateUi();

    // 初始化当前模块的signal,slot
    connect(fileSelectButton, &QPushButton::clicked, this, &MILaplacian::selectFile);
    connect(imShowChechBox, &QCheckBox::clicked, this, &MILaplacian::onImShowChechBoxClicked);

    this->addSubPage(subPage);
}


void MILaplacian::retranslateUi()
{
    QImage qimage;
    fileSelectLabel->setText("待处理图片:");
    fileSelectPath->setText("../assert/image21.jpg");
    fileSelectButton->setText("...");

    imShowChechBox->setText("使用OpenCV的imshow");

    g_srcImage  = imread(fileSelectPath->text().toStdString());
    if( !g_srcImage.data )
    {
        qDebug() << "imread: 读取图像错误, " << fileSelectPath->text();
    }

    imageLabel_src->setText("imageLabel_src");
    qimage = cvMat2QImage(g_srcImage);
    imageLabel_src->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_src->resize(QSize(qimage.width(),qimage.height()));
    label_src->setText(MINAME+QString("【原图】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    scrollAreaWidgetContents->resize(formLayout->sizeHint());


    imShow = imShowChechBox->isChecked();
    if( this->imShow )
    {
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
    }


    onSubmitClicked();

}


void MILaplacian::selectFile()
{
    QImage qimage;
    qDebug() << "selectFile: " << this->modelItemName;
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
        fileSelectPath->setText(fileNames[0]);
        g_srcImage  = imread(fileSelectPath->text().toStdString());
        if( !g_srcImage.data )
        {
            qDebug() << "imread: 读取图像错误, " << fileSelectPath->text();
        }


        imageLabel_src->setText("imageLabel_src");
        qimage = cvMat2QImage(g_srcImage);
        imageLabel_src->setPixmap(QPixmap::fromImage(qimage));
        imageLabel_src->resize(QSize(qimage.width(),qimage.height()));
        label_src->setText(MINAME+QString("【原图】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
        scrollAreaWidgetContents->resize(formLayout->sizeHint());

        onSubmitClicked();
    }
    else
    {
        qDebug() << " 未选择文件 ";
    }
}


void MILaplacian::onSubmitClicked()
{
    QImage qimage;

    qDebug() << "onSubmitClicked:" << this->modelItemName;

    GaussianBlur( g_srcImage, g_srcImage, Size(3,3), 0, 0, BORDER_DEFAULT );
    cvtColor( g_srcImage, g_grayImage, COLOR_RGB2GRAY );
    Laplacian( g_grayImage, g_dstImage, CV_16S, 3, 1, 0, BORDER_DEFAULT );
    // 计算绝对值，并将结果转换成8位
    convertScaleAbs( g_dstImage, g_absImage );

    qimage = cvMat2QImage(g_grayImage);
    imageLabel_gray->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_gray->resize(QSize(qimage.width(),qimage.height()));
    label_gray->setText(MINAME+QString("【grayImage】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    qimage = cvMat2QImage(g_absImage);
    imageLabel_abs->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_abs->resize(QSize(qimage.width(),qimage.height()));
    label_abs->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    scrollAreaWidgetContents->resize(formLayout->sizeHint());

    //显示效果图
    if( this->imShow )
    {
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
        imshow( (QString(MINAME)+QString("【grayImage】")).toStdString(), g_grayImage );
        imshow( (QString(MINAME)+QString("【效果图】")).toStdString(), g_absImage );
    }
}



void MILaplacian::onImShowChechBoxClicked(bool status)
{
    imShow = status;
    if( this->imShow )
    {
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
        imshow( (QString(MINAME)+QString("【grayImage】")).toStdString(), g_grayImage );
        imshow( (QString(MINAME)+QString("【效果图】")).toStdString(), g_absImage );
    }
}

