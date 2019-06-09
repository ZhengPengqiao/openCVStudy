#include "misobel.h"


#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QApplication>
#include <QSizePolicy>
#include <QMouseEvent>
#include <QComboBox>

#define MINAME "边沿检测Sobel"

MISobel::MISobel()
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

    sobelKernelLayout = new QHBoxLayout();
    sobelKernelLabel = new QLabel(subPage);
    sobelKernelLayout->addWidget(sobelKernelLabel);
    sobelKernelSlider = new QSlider(subPage);
    sobelKernelSlider->setOrientation(Qt::Horizontal);
    sobelKernelLayout->addWidget(sobelKernelSlider);
    vBoxLayout->addLayout(sobelKernelLayout);


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
    // 当前模块的Area区域, 显示sobelAbsX
    label_sobelAbsX = new QLabel(scrollAreaWidgetContents);
    label_sobelAbsX->setObjectName(QStringLiteral("label_sobelAbsX"));
    imageLabel_sobelAbsX = new QLabel(scrollAreaWidgetContents);
    imageLabel_sobelAbsX->setObjectName(QStringLiteral("imageLabel_sobelAbsX"));
    formLayout->insertRow(2, label_sobelAbsX, imageLabel_sobelAbsX);
    // 当前模块的Area区域, 显示sobelAbsY
    label_sobelAbsY = new QLabel(scrollAreaWidgetContents);
    label_sobelAbsY->setObjectName(QStringLiteral("label_sobelAbsY"));
    imageLabel_sobelAbsY = new QLabel(scrollAreaWidgetContents);
    imageLabel_sobelAbsY->setObjectName(QStringLiteral("imageLabel_sobelAbsY"));
    formLayout->insertRow(3, label_sobelAbsY, imageLabel_sobelAbsY);
    // 当前模块的Area区域, 显示效果图
    label_dst = new QLabel(scrollAreaWidgetContents);
    label_dst->setObjectName(QStringLiteral("label_dst"));
    imageLabel_dst = new QLabel(scrollAreaWidgetContents);
    imageLabel_dst->setObjectName(QStringLiteral("imageLabel_dst"));
    formLayout->insertRow(4, label_dst, imageLabel_dst);


    // 初始化当前模块控件的内容
    retranslateUi();

    // 初始化当前模块的signal,slot
    connect(fileSelectButton, &QPushButton::clicked, this, &MISobel::selectFile);
    connect(imShowChechBox, &QCheckBox::clicked, this, &MISobel::onImShowChechBoxClicked);
    connect(sobelKernelSlider, &QSlider::valueChanged, this, &MISobel::onSliderValueChange);

    this->addSubPage(subPage);
}


void MISobel::retranslateUi()
{
    QImage qimage;
    fileSelectLabel->setText("待处理图片:");
    fileSelectPath->setText("../assert/image21.jpg");
    fileSelectButton->setText("...");

    imShowChechBox->setText("使用OpenCV的imshow");

    sobelKernelSlider->setMinimum(0);
    sobelKernelSlider->setMaximum(3);
    sobelKernelSlider->setSingleStep(1);
    sobelKernelSlider->setValue(1);
    sobelKernelSlider->setTickPosition(QSlider::TicksAbove);
    sobelKernelLabel->setText("sobelKernel:" + QString("%1").arg(sobelKernelSlider->value()));
    g_sobelKernelSize = sobelKernelSlider->value();

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
        namedWindow( (QString(MINAME)+QString("【原图】")).toStdString() );
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
    }


    onSubmitClicked();

}


void MISobel::selectFile()
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


void MISobel::onSubmitClicked()
{
    QImage qimage;

    qDebug() << "onSubmitClicked:" << this->modelItemName;
    // 求 X方向梯度
    Sobel( g_srcImage, g_sobelGradient_X, CV_16S, 1, 0, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );
    convertScaleAbs( g_sobelGradient_X, g_sobelAbsGradient_X );//计算绝对值，并将结果转换成8位

    // 求Y方向梯度
    Sobel( g_srcImage, g_sobelGradient_Y, CV_16S, 0, 1, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );
    convertScaleAbs( g_sobelGradient_Y, g_sobelAbsGradient_Y );//计算绝对值，并将结果转换成8位

    // 合并梯度
    addWeighted( g_sobelAbsGradient_X, 0.5, g_sobelAbsGradient_Y, 0.5, 0, g_dstImage );

    qimage = cvMat2QImage(g_sobelAbsGradient_X);
    imageLabel_sobelAbsX->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_sobelAbsX->resize(QSize(qimage.width(),qimage.height()));
    label_sobelAbsX->setText(MINAME+QString("【sobelAbsX】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    qimage = cvMat2QImage(g_sobelAbsGradient_Y);
    imageLabel_sobelAbsY->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_sobelAbsY->resize(QSize(qimage.width(),qimage.height()));
    label_sobelAbsY->setText(MINAME+QString("【sobelAbsY】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    qimage = cvMat2QImage(g_dstImage);
    imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_dst->resize(QSize(qimage.width(),qimage.height()));
    label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    scrollAreaWidgetContents->resize(formLayout->sizeHint());

    //显示效果图
    if( this->imShow )
    {
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
        imshow( (QString(MINAME)+QString("【sobelAbsX】")).toStdString(), g_sobelAbsGradient_X );
        imshow( (QString(MINAME)+QString("【sobelAbsY】")).toStdString(), g_sobelAbsGradient_Y );
        imshow( (QString(MINAME)+QString("【效果图】")).toStdString(), g_dstImage );
    }
}



void MISobel::onImShowChechBoxClicked(bool status)
{
    imShow = status;
    if( this->imShow )
    {
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
        imshow( (QString(MINAME)+QString("【sobelAbsX】")).toStdString(), g_sobelAbsGradient_X );
        imshow( (QString(MINAME)+QString("【sobelAbsY】")).toStdString(), g_sobelAbsGradient_Y );
        imshow( (QString(MINAME)+QString("【效果图】")).toStdString(), g_dstImage );
    }
}


void MISobel::onSliderValueChange(int val)
{
    g_sobelKernelSize = sobelKernelSlider->value();

    sobelKernelLabel->setText("sobelKernel:" + QString("%1").arg(sobelKernelSlider->value()));

    onSubmitClicked();
}
