#include "mipyrresize.h"

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QApplication>
#include <QSizePolicy>
#include <QMouseEvent>
#include <QComboBox>

#define MINAME "图像金字塔与图像缩放PyrResize"

MIPyrResize::MIPyrResize()
{
    this->setModelItemName(MINAME);

    subPage = new QWidget();


    vBoxLayout = new QVBoxLayout(subPage);
    vBoxLayout->setObjectName(QStringLiteral("vBoxLayout"));

    hBoxLayout = new QHBoxLayout();
    hBoxLayout->setObjectName(QStringLiteral("hBoxLayout"));
    label = new QLabel(subPage);
    label->setObjectName(QStringLiteral("label"));
    hBoxLayout->addWidget(label);

    imagePath = new QLineEdit(subPage);
    imagePath->setObjectName(QStringLiteral("imagePath"));
    hBoxLayout->addWidget(imagePath);

    button = new QPushButton(subPage);
    button->setObjectName(QStringLiteral("button"));
    hBoxLayout->addWidget(button);
    vBoxLayout->addLayout(hBoxLayout);

    ctrlHBoxLayout = new QHBoxLayout();
    ctrlHBoxLayout->setObjectName(QStringLiteral("ctrlHBoxLayout"));
    imShowChechBox = new QCheckBox(subPage);
    imShowChechBox->setObjectName(QStringLiteral("imShowChechBox"));
    ctrlHBoxLayout->addWidget(imShowChechBox);

    PyrUp = new QPushButton(subPage);
    PyrUp->setObjectName(QStringLiteral("PyrUp"));
    ctrlHBoxLayout->addWidget(PyrUp);
    PyrDown = new QPushButton(subPage);
    PyrDown->setObjectName(QStringLiteral("PyrDown"));
    ctrlHBoxLayout->addWidget(PyrDown);
    ResizeUp = new QPushButton(subPage);
    ResizeUp->setObjectName(QStringLiteral("ResizeUp"));
    ctrlHBoxLayout->addWidget(ResizeUp);
    ResizeDown = new QPushButton(subPage);
    ResizeDown->setObjectName(QStringLiteral("ResizeDown"));
    ctrlHBoxLayout->addWidget(ResizeDown);

    operComboBox = new QComboBox(subPage);
    operComboBox->setObjectName(QStringLiteral("operComboBox"));
    ctrlHBoxLayout->addWidget(operComboBox);
    valComboBox = new QComboBox(subPage);
    valComboBox->setObjectName(QStringLiteral("valComboBox"));
    ctrlHBoxLayout->addWidget(valComboBox);
    vBoxLayout->addLayout(ctrlHBoxLayout);

    scrollArea = new QScrollArea(subPage);
    scrollArea->setObjectName(QStringLiteral("scrollArea"));
    scrollArea->setWidgetResizable(false);
    scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
    scrollAreaWidgetContents->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    scrollArea->setWidget(scrollAreaWidgetContents);

    formLayout = new QFormLayout(scrollAreaWidgetContents);
    formLayout->setSpacing(6);
    formLayout->setContentsMargins(1, 1, 1, 1);
    formLayout->setObjectName(QStringLiteral("formLayout"));

    label_src = new QLabel(scrollAreaWidgetContents);
    label_src->setObjectName(QStringLiteral("label_src"));
    imageLabel_src = new QLabel(scrollAreaWidgetContents);
    imageLabel_src->setObjectName(QStringLiteral("imageLabel_src"));
    formLayout->setWidget(1, QFormLayout::LabelRole, label_src);
    formLayout->setWidget(1, QFormLayout::FieldRole, imageLabel_src);


    label_dst = new QLabel(scrollAreaWidgetContents);
    label_dst->setObjectName(QStringLiteral("label_dst"));
    imageLabel_dst = new QLabel(scrollAreaWidgetContents);
    imageLabel_dst->setObjectName(QStringLiteral("imageLabel_dst"));
    formLayout->setWidget(2, QFormLayout::LabelRole, label_dst);
    formLayout->setWidget(2, QFormLayout::FieldRole, imageLabel_dst);


    scrollAreaWidgetContents->resize(formLayout->sizeHint());

    vBoxLayout->addWidget(scrollArea);

    retranslateUi();

    connect(button, &QPushButton::clicked, this, &MIPyrResize::selectFile);
    connect(PyrUp, &QPushButton::clicked, this, &MIPyrResize::dealPyrUp);
    connect(PyrDown, &QPushButton::clicked, this, &MIPyrResize::dealPyrDown);
    connect(ResizeUp, &QPushButton::clicked, this, &MIPyrResize::dealResizeUp);
    connect(ResizeDown, &QPushButton::clicked, this, &MIPyrResize::dealResizeDown);
    connect(operComboBox, &QComboBox::currentTextChanged, this, &MIPyrResize::onComboBoxCurrentTextChanged);
    connect(valComboBox, &QComboBox::currentTextChanged, this, &MIPyrResize::onComboBoxCurrentTextChanged);
    this->addSubPage(subPage);

}


void MIPyrResize::retranslateUi()
{
    QImage qimage;
    label->setText("待处理图片:");
    imagePath->setText("../assert/image23.jpg");
    button->setText("...");

    g_srcImage  = imread(imagePath->text().toStdString());
    if( !g_srcImage.data )
    {
        qDebug() << "imread: 读取图像错误, " << imagePath->text();
    }

    g_srcImage.copyTo(g_tmpImage);//拷贝源图到目标图
    g_srcImage.copyTo(g_dstImage);//拷贝源图到目标图
    imageLabel_src->setText("imageLabel_src");
    qimage = cvMat2QImage(g_srcImage);
    imageLabel_src->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_src->resize(QSize(qimage.width(),qimage.height()));
    imageLabel_src->setScaledContents(true);
    label_src->setText(MINAME+QString("【原图】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    imageLabel_dst->setText("imageLabel_dst");
    qimage = cvMat2QImage(g_dstImage);
    imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_dst->resize(QSize(qimage.width(),qimage.height()));
    imageLabel_dst->setScaledContents(true);
    imageLabel_dst->installEventFilter(this);//安装事件过滤器
    label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    scrollAreaWidgetContents->resize(formLayout->sizeHint());
    imShowChechBox->setText("使用OpenCV的imshow");
    operComboBox->clear();
    operComboBox->insertItems(0, QStringList()
     << QApplication::translate("MIPyrResize", "PyrUp", 0)
     << QApplication::translate("MIPyrResize", "PyrDown", 0)
     << QApplication::translate("MIPyrResize", "Resize 放大", 0)
     << QApplication::translate("MIPyrResize", "Resize 缩小", 0)
    );
    operType = operComboBox->currentIndex();
    valComboBox->clear();
    valComboBox->insertItems(0, QStringList()
     << QApplication::translate("MIPyrResize", "x2", 0)
    );
    operVal = valComboBox->currentIndex();

    PyrUp->setText("PyrUp");
    PyrDown->setText("PyrDown");
    ResizeUp->setText("ResizeUp");
    ResizeDown->setText("ResizeDown");
}


void MIPyrResize::selectFile()
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
        imagePath->setText(fileNames[0]);

        g_srcImage  = imread(fileNames[0].toStdString());
        if( !g_srcImage.data )
        {
            qDebug() << "imread: 读取图像错误, " << fileNames[0];
        }


        qimage = cvMat2QImage(g_srcImage);
        imageLabel_src->setPixmap(QPixmap::fromImage(qimage));
        imageLabel_src->resize(QSize(image.width(),image.height()));
        label_src->setText(MINAME+QString("【原图】\n width:%1 \n height:%2")
                           .arg(image.width()).arg(image.height()));


        qDebug() << "image: path=" << imagePath->text();
        qDebug() << "image: rows=" << g_srcImage.rows;
        qDebug() << "image: cols=" << g_srcImage.cols;

        g_srcImage.copyTo(g_tmpImage);//拷贝源图到目标图
        g_srcImage.copyTo(g_dstImage);//拷贝源图到目标图
        qimage = cvMat2QImage(g_dstImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));
        imageLabel_dst->resize(QSize(image.width(),image.height()));
        label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                           .arg(image.width()).arg(image.height()));

        scrollAreaWidgetContents->resize(formLayout->sizeHint());
    }
    else
    {
        qDebug() << " 未选择文件 ";
    }
}


void MIPyrResize::onSubmitClicked()
{
    QImage qimage;
    //获取自定义核
    switch( operType )
    {
        case 0: //PyrUp
            pyrUp( g_tmpImage, g_dstImage, Size( g_tmpImage.cols*operVal, g_tmpImage.rows*operVal ) );
        break;
        case 1: //PyrDown
            pyrDown( g_tmpImage, g_dstImage, Size( g_tmpImage.cols/operVal, g_tmpImage.rows/operVal ));
        break;
        case 2: //Resize 放大
            resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols*operVal, g_tmpImage.rows*operVal ));
        break;
        case 3: //Resize 缩小
            resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols/operVal, g_tmpImage.rows/operVal ));
        break;
    }
    //创建窗口
    if( imShowChechBox->isChecked() == true )
    {
        namedWindow( (QString(MINAME)+QString("【原图】")).toStdString() );
        namedWindow( (QString(MINAME)+QString("【效果图】")).toStdString() );
    }

    //显示原图
    if( imShowChechBox->isChecked() == true )
    {
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
    }
    //显示效果图
    if( imShowChechBox->isChecked() == true )
    {
        imshow( (QString(MINAME)+QString("【效果图】")).toStdString() ,g_dstImage );
    }


    qimage = cvMat2QImage(g_srcImage);
    imageLabel_src->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_src->setText(MINAME+QString("【原图】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));
    qimage = cvMat2QImage(g_dstImage);
    imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));
    g_tmpImage = g_dstImage;
    scrollAreaWidgetContents->resize(formLayout->sizeHint());
}


void MIPyrResize::onComboBoxCurrentTextChanged(QString text)
{
    operType = operComboBox->currentIndex();

    switch( valComboBox->currentIndex() )
    {
        case 0:
            operVal = 2;
        break;
    }

    qDebug() << "operType:" << operType << " operVal:" << operVal;
}


void MIPyrResize::dealPyrUp()
{
    QImage qimage;
    //获取自定义核

    pyrUp( g_tmpImage, g_dstImage, Size( g_tmpImage.cols*operVal, g_tmpImage.rows*operVal ) );

    //创建窗口
    if( imShowChechBox->isChecked() == true )
    {
        namedWindow( (QString(MINAME)+QString("【原图】")).toStdString() );
        namedWindow( (QString(MINAME)+QString("【效果图】")).toStdString() );
    }

    //显示原图
    if( imShowChechBox->isChecked() == true )
    {
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
    }
    //显示效果图
    if( imShowChechBox->isChecked() == true )
    {
        imshow( (QString(MINAME)+QString("【效果图】")).toStdString() ,g_dstImage );
    }


    qimage = cvMat2QImage(g_srcImage);
    imageLabel_src->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_src->setText(MINAME+QString("【原图】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));
    qimage = cvMat2QImage(g_dstImage);
    imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));
    g_tmpImage = g_dstImage;
    scrollAreaWidgetContents->resize(formLayout->sizeHint());
}



void MIPyrResize::dealPyrDown()
{
    QImage qimage;
    //获取自定义核

    pyrDown( g_tmpImage, g_dstImage, Size( g_tmpImage.cols/operVal, g_tmpImage.rows/operVal ) );

    //创建窗口
    if( imShowChechBox->isChecked() == true )
    {
        namedWindow( (QString(MINAME)+QString("【原图】")).toStdString() );
        namedWindow( (QString(MINAME)+QString("【效果图】")).toStdString() );
    }

    //显示原图
    if( imShowChechBox->isChecked() == true )
    {
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
    }
    //显示效果图
    if( imShowChechBox->isChecked() == true )
    {
        imshow( (QString(MINAME)+QString("【效果图】")).toStdString() ,g_dstImage );
    }


    qimage = cvMat2QImage(g_srcImage);
    imageLabel_src->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_src->setText(MINAME+QString("【原图】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));
    qimage = cvMat2QImage(g_dstImage);
    imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));
    g_tmpImage = g_dstImage;
    scrollAreaWidgetContents->resize(formLayout->sizeHint());
}



void MIPyrResize::dealResizeUp()
{
    QImage qimage;
    //获取自定义核

    resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols*operVal, g_tmpImage.rows*operVal ));
    //创建窗口
    if( imShowChechBox->isChecked() == true )
    {
        namedWindow( (QString(MINAME)+QString("【原图】")).toStdString() );
        namedWindow( (QString(MINAME)+QString("【效果图】")).toStdString() );
    }

    //显示原图
    if( imShowChechBox->isChecked() == true )
    {
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
    }
    //显示效果图
    if( imShowChechBox->isChecked() == true )
    {
        imshow( (QString(MINAME)+QString("【效果图】")).toStdString() ,g_dstImage );
    }


    qimage = cvMat2QImage(g_srcImage);
    imageLabel_src->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_src->setText(MINAME+QString("【原图】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));
    qimage = cvMat2QImage(g_dstImage);
    imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));
    g_tmpImage = g_dstImage;
    scrollAreaWidgetContents->resize(formLayout->sizeHint());
}



void MIPyrResize::dealResizeDown()
{
    QImage qimage;
    //获取自定义核

    resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols/operVal, g_tmpImage.rows/operVal ));

    //创建窗口
    if( imShowChechBox->isChecked() == true )
    {
        namedWindow( (QString(MINAME)+QString("【原图】")).toStdString() );
        namedWindow( (QString(MINAME)+QString("【效果图】")).toStdString() );
    }

    //显示原图
    if( imShowChechBox->isChecked() == true )
    {
        imshow( (QString(MINAME)+QString("【原图】")).toStdString(), g_srcImage );
    }
    //显示效果图
    if( imShowChechBox->isChecked() == true )
    {
        imshow( (QString(MINAME)+QString("【效果图】")).toStdString() ,g_dstImage );
    }


    qimage = cvMat2QImage(g_srcImage);
    imageLabel_src->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_src->setText(MINAME+QString("【原图】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));
    qimage = cvMat2QImage(g_dstImage);
    imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));
    g_tmpImage = g_dstImage;
    scrollAreaWidgetContents->resize(formLayout->sizeHint());
}
