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

    interComboBox = new QComboBox(subPage);
    interComboBox->setObjectName(QStringLiteral("interComboBox"));
    ctrlHBoxLayout->addWidget(interComboBox);
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
    formLayout->insertRow(1, label_src, imageLabel_src);

    label_dst = new QLabel(scrollAreaWidgetContents);
    label_dst->setObjectName(QStringLiteral("label_dst"));
    imageLabel_dst = new QLabel(scrollAreaWidgetContents);
    imageLabel_dst->setObjectName(QStringLiteral("imageLabel_dst"));
    formLayout->insertRow(2, label_dst, imageLabel_dst);

    scrollAreaWidgetContents->resize(formLayout->sizeHint());

    vBoxLayout->addWidget(scrollArea);

    retranslateUi();

    connect(button, &QPushButton::clicked, this, &MIPyrResize::selectFile);
    connect(PyrUp, &QPushButton::clicked, this, &MIPyrResize::dealPyrUp);
    connect(PyrDown, &QPushButton::clicked, this, &MIPyrResize::dealPyrDown);
    connect(ResizeUp, &QPushButton::clicked, this, &MIPyrResize::dealResizeUp);
    connect(ResizeDown, &QPushButton::clicked, this, &MIPyrResize::dealResizeDown);
    connect(interComboBox, &QComboBox::currentTextChanged, this, &MIPyrResize::onComboBoxCurrentTextChanged);
    connect(valComboBox, &QComboBox::currentTextChanged, this, &MIPyrResize::onComboBoxCurrentTextChanged);
    this->addSubPage(subPage);

}


void MIPyrResize::retranslateUi()
{
    QImage qimage;
    label->setText("待处理图片:");
    imagePath->setText("../assert/image21.jpg");
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
    label_src->setText(MINAME+QString("【原图】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    imageLabel_dst->setText("imageLabel_dst");
    qimage = cvMat2QImage(g_dstImage);
    imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_dst->resize(QSize(qimage.width(),qimage.height()));
    imageLabel_dst->installEventFilter(this);//安装事件过滤器
    label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    scrollAreaWidgetContents->resize(formLayout->sizeHint());
    imShowChechBox->setText("使用OpenCV的imshow");
    interComboBox->clear();
    interComboBox->insertItems(0, QStringList()
     << QApplication::translate("MIPyrResize", "Resize-最近邻插值", 0)
     << QApplication::translate("MIPyrResize", "Resize-线性插值", 0)
     << QApplication::translate("MIPyrResize", "Resize-区域插值", 0)
     << QApplication::translate("MIPyrResize", "Resize-三次样条插值", 0)
     << QApplication::translate("MIPyrResize", "Resize-Lanczos插值", 0)
    );
    operInter = interComboBox->currentIndex();
    valComboBox->clear();
    valComboBox->insertItems(0, QStringList()
     << QApplication::translate("MIPyrResize", "x1", 0)
     << QApplication::translate("MIPyrResize", "x2", 0)
     << QApplication::translate("MIPyrResize", "x3", 0)
     << QApplication::translate("MIPyrResize", "x4", 0)
    );

    operVal = valComboBox->currentIndex()+1;

    qDebug() << "operInter:" << operInter << " operVal:" << operVal;

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
                           .arg(qimage.width()).arg(qimage.height()));


        qDebug() << "image: path=" << imagePath->text();
        qDebug() << "image: rows=" << g_srcImage.rows;
        qDebug() << "image: cols=" << g_srcImage.cols;

        g_srcImage.copyTo(g_tmpImage);//拷贝源图到目标图
        g_srcImage.copyTo(g_dstImage);//拷贝源图到目标图
        qimage = cvMat2QImage(g_dstImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));
        imageLabel_dst->resize(QSize(image.width(),image.height()));
        label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));

        scrollAreaWidgetContents->resize(formLayout->sizeHint());
    }
    else
    {
        qDebug() << " 未选择文件 ";
    }
}


void MIPyrResize::onSubmitClicked()
{
    qDebug() << "onSubmitClicked, 不做处理";
}


void MIPyrResize::onComboBoxCurrentTextChanged(QString text)
{
    operInter = interComboBox->currentIndex();
    operVal = valComboBox->currentIndex()+1;
    qDebug() << "operType:" << operInter << " operVal:" << operVal;
}


void MIPyrResize::dealPyrUp()
{
    QImage qimage;
    //获取自定义核

    qDebug() << "dealPyrUp" << "cols:" << g_tmpImage.cols << "rows:" << g_tmpImage.rows << "operVal:" << 2;

    pyrUp( g_tmpImage, g_dstImage, Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ) );

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

    qDebug() << "dealPyrUp" << "OK";
}



void MIPyrResize::dealPyrDown()
{
    QImage qimage;
    //获取自定义核

    qDebug() << "dealPyrDown" << "cols:" << g_tmpImage.cols << "rows:" << g_tmpImage.rows << "operVal:" << 2;
    pyrDown( g_tmpImage, g_dstImage, Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ) );

    qDebug() << "dealPyrDown" << "111";
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


    qDebug() << "dealPyrDown" << "222";

    qimage = cvMat2QImage(g_srcImage);
    imageLabel_src->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    imageLabel_src->resize(qimage.size());
    label_src->setText(MINAME+QString("【原图】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));

    qDebug() << "dealPyrDown" << "333";
    qimage = cvMat2QImage(g_dstImage);
    imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    imageLabel_dst->resize(qimage.size());
    label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));

    g_tmpImage = g_dstImage;
    scrollAreaWidgetContents->resize(formLayout->sizeHint());

    qDebug() << "dealResizeDown" << "OK";
}



void MIPyrResize::dealResizeUp()
{
    QImage qimage;
    //获取自定义核

    qDebug() << "dealResizeUp" << "cols:" << g_tmpImage.cols << "rows:" << g_tmpImage.rows << "operVal:" << operVal;
    switch( operInter )
    {
        case 0:
            resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols*operVal, g_tmpImage.rows*operVal ), (0,0), (0,0), INTER_NEAREST);
        break;
        case 1:
            resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols*operVal, g_tmpImage.rows*operVal ), (0,0), (0,0), INTER_LINEAR);
        break;
        case 2:
            resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols*operVal, g_tmpImage.rows*operVal ), (0,0), (0,0), INTER_AREA);
        break;
        case 3:
            resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols*operVal, g_tmpImage.rows*operVal ), (0,0), (0,0), INTER_CUBIC);
        break;
        case 4:
            resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols*operVal, g_tmpImage.rows*operVal ), (0,0), (0,0), INTER_LANCZOS4);
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

    qDebug() << "dealPyrDown" << "OK";
}



void MIPyrResize::dealResizeDown()
{
    QImage qimage;
    //获取自定义核

    qDebug() << "dealResizeDown" << "cols:" << g_tmpImage.cols << "rows:" << g_tmpImage.rows << "operVal:" << operVal;

    switch( operInter )
    {
        case 0:
            resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols/operVal, g_tmpImage.rows/operVal ), (0,0), (0,0), INTER_NEAREST);
        break;
        case 1:
            resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols/operVal, g_tmpImage.rows/operVal ), (0,0), (0,0), INTER_LINEAR);
        break;
        case 2:
            resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols/operVal, g_tmpImage.rows/operVal ), (0,0), (0,0), INTER_AREA);
        break;
        case 3:
            resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols/operVal, g_tmpImage.rows/operVal ), (0,0), (0,0), INTER_CUBIC);
        break;
        case 4:
            resize(g_tmpImage, g_dstImage,Size( g_tmpImage.cols/operVal, g_tmpImage.rows/operVal ), (0,0), (0,0), INTER_LANCZOS4);
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

    qDebug() << "dealResizeDown" << "OK";
}
