#include "micanny.h"

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QApplication>
#include <QSizePolicy>
#include <QMouseEvent>
#include <QComboBox>

#define MINAME "边沿检测Canny"

MICanny::MICanny()
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

    threshold1Layout = new QHBoxLayout();
    threshold1Label = new QLabel(subPage);
    threshold1Layout->addWidget(threshold1Label);
    threshold1Slider = new QSlider(subPage);
    threshold1Slider->setOrientation(Qt::Horizontal);
    threshold1Layout->addWidget(threshold1Slider);
    vBoxLayout->addLayout(threshold1Layout);
    threshold2Layout = new QHBoxLayout();
    threshold2Label = new QLabel(subPage);
    threshold2Layout->addWidget(threshold2Label);
    threshold2Slider = new QSlider(subPage);
    threshold2Slider->setOrientation(Qt::Horizontal);
    threshold2Layout->addWidget(threshold2Slider);
    vBoxLayout->addLayout(threshold2Layout);


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
    // 当前模块的Area区域, 显示灰度图
    label_gray = new QLabel(scrollAreaWidgetContents);
    label_gray->setObjectName(QStringLiteral("label_gray"));
    imageLabel_gray = new QLabel(scrollAreaWidgetContents);
    imageLabel_gray->setObjectName(QStringLiteral("imageLabel_gray"));
    formLayout->insertRow(2, label_gray, imageLabel_gray);
    // 当前模块的Area区域, 显示灰度图的边沿检测
    label_grayEdges = new QLabel(scrollAreaWidgetContents);
    label_grayEdges->setObjectName(QStringLiteral("label_grayEdges"));
    imageLabel_grayEdges = new QLabel(scrollAreaWidgetContents);
    imageLabel_grayEdges->setObjectName(QStringLiteral("imageLabel_grayEdges"));
    formLayout->insertRow(3, label_grayEdges, imageLabel_grayEdges);
    // 当前模块的Area区域, 显示效果图
    label_dst = new QLabel(scrollAreaWidgetContents);
    label_dst->setObjectName(QStringLiteral("label_dst"));
    imageLabel_dst = new QLabel(scrollAreaWidgetContents);
    imageLabel_dst->setObjectName(QStringLiteral("imageLabel_dst"));
    formLayout->insertRow(4, label_dst, imageLabel_dst);


    // 初始化当前模块控件的内容
    retranslateUi();

    // 初始化当前模块的signal,slot
    connect(fileSelectButton, &QPushButton::clicked, this, &MICanny::selectFile);
    connect(imShowChechBox, &QCheckBox::clicked, this, &MICanny::onImShowChechBoxClicked);
    connect(threshold1Slider, &QSlider::valueChanged, this, &MICanny::onSliderValueChange);
    connect(threshold2Slider, &QSlider::valueChanged, this, &MICanny::onSliderValueChange);

    this->addSubPage(subPage);
}


void MICanny::retranslateUi()
{
    QImage qimage;
    fileSelectLabel->setText("待处理图片:");
    fileSelectPath->setText("../assert/image21.jpg");
    fileSelectButton->setText("...");

    imShowChechBox->setText("使用OpenCV的imshow");

    threshold1Slider->setMinimum(0);
    threshold1Slider->setMaximum(255);
    threshold1Slider->setSingleStep(1);
    threshold1Slider->setValue(20);
    threshold1Slider->setTickPosition(QSlider::TicksAbove);
    threshold1Label->setText("threshold1:" + QString("%1").arg(threshold1Slider->value()));
    threshold1Val = threshold1Slider->value();

    threshold2Label->setText("threshold2:6");
    threshold2Slider->setMinimum(0);
    threshold2Slider->setMaximum(255);
    threshold2Slider->setSingleStep(1);
    threshold2Slider->setValue(20);
    threshold2Slider->setTickPosition(QSlider::TicksAbove);
    threshold2Label->setText("threshold1:" + QString("%1").arg(threshold2Slider->value()));
    threshold2Val = threshold2Slider->value();

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


    // 将原图像转换为灰度图像
    cvtColor( g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY );


    imShow = imShowChechBox->isChecked();
    if( this->imShow )
    {
        namedWindow( (QString(MINAME)+QString("【原图】")).toStdString() );
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
    }


    onSubmitClicked();

}


void MICanny::selectFile()
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

        // 将原图像转换为灰度图像
        cvtColor( g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY );

        onSubmitClicked();
    }
    else
    {
        qDebug() << " 未选择文件 ";
    }
}


void MICanny::onSubmitClicked()
{
    QImage qimage;
    // 先使用 3x3内核来降噪
    blur( g_srcGrayImage, g_GrayDetectedEdges, Size(3,3) );

    // 运行我们的Canny算子
    Canny( g_GrayDetectedEdges, g_cannyDetectedEdges, threshold1Val, threshold2Val*3, 3 );

    //先将g_dstImage内的所有元素设置为0
    g_dstImage = Scalar::all(0);

    //使用Canny算子输出的边缘图g_cannyDetectedEdges作为掩码，来将原图g_srcImage拷到目标图g_dstImage中
    g_srcImage.copyTo( g_dstImage, g_cannyDetectedEdges);

    qimage = cvMat2QImage(g_GrayDetectedEdges);
    imageLabel_gray->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_gray->resize(QSize(qimage.width(),qimage.height()));
    label_gray->setText(MINAME+QString("【灰度图】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    qimage = cvMat2QImage(g_cannyDetectedEdges);
    imageLabel_grayEdges->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_grayEdges->resize(QSize(qimage.width(),qimage.height()));
    label_grayEdges->setText(MINAME+QString("【灰度边沿】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    qimage = cvMat2QImage(g_dstImage);
    imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_dst->resize(QSize(qimage.width(),qimage.height()));
    label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    scrollAreaWidgetContents->resize(formLayout->sizeHint());

    //显示效果图
    if( this->imShow )
    {
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
        imshow( (QString(MINAME)+QString("【灰度图】")).toStdString(), g_GrayDetectedEdges );
        imshow( (QString(MINAME)+QString("【灰度边沿】")).toStdString(), g_cannyDetectedEdges );
        imshow( (QString(MINAME)+QString("【效果图】")).toStdString(), g_dstImage );
    }
}



void MICanny::onImShowChechBoxClicked(bool status)
{
    imShow = status;
    if( this->imShow )
    {
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
        imshow( (QString(MINAME)+QString("【灰度图】")).toStdString(), g_GrayDetectedEdges );
        imshow( (QString(MINAME)+QString("【灰度边沿】")).toStdString(), g_cannyDetectedEdges );
        imshow( (QString(MINAME)+QString("【效果图】")).toStdString(), g_dstImage );
    }
}


void MICanny::onSliderValueChange(int val)
{
    threshold1Val = threshold1Slider->value();
    threshold2Val = threshold2Slider->value();

    threshold1Label->setText("threshold1:" + QString("%1").arg(threshold1Slider->value()));
    threshold2Label->setText("threshold1:" + QString("%1").arg(threshold2Slider->value()));

    onSubmitClicked();
}
