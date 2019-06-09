#include "mifloodfill.h"

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QApplication>
#include <QSizePolicy>
#include <QMouseEvent>
#include <QComboBox>

#define MINAME "漫水填充FloodFill"

MIFloodFill::MIFloodFill()
{
    this->setModelItemName(MINAME);

    lowDiffMax = 255;
    upDiffMax = 255;
    fillMode = 1;//漫水填充的模式
    isColor = 0;
    lowDifference = 20;  // 负差最大值
    upDifference = 20;   // 正差最大值
    connectivity = 4;//表示floodFill函数标识符低八位的连通值
    newMaskVal = 255;//新的重新绘制的像素值
    isImShow = false;
    isUseColor = true;
    isUseMask = false;

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
    comboBox = new QComboBox(subPage);
    comboBox->setObjectName(QStringLiteral("comboBox"));
    ctrlHBoxLayout->addWidget(comboBox);
    isUseColorChechBox = new QCheckBox(subPage);
    isUseColorChechBox->setObjectName(QStringLiteral("isUseColorChechBox"));
    ctrlHBoxLayout->addWidget(isUseColorChechBox);
    isUseMaskChechBox = new QCheckBox(subPage);
    isUseMaskChechBox->setObjectName(QStringLiteral("isUseMaskChechBox"));
    ctrlHBoxLayout->addWidget(isUseMaskChechBox);
    clearButton = new QPushButton(subPage);
    clearButton->setObjectName(QStringLiteral("clearButton"));
    ctrlHBoxLayout->addWidget(clearButton);
    vBoxLayout->addLayout(ctrlHBoxLayout);


    lowDiffLayout = new QHBoxLayout();
    lowDiffLayout->setObjectName(QStringLiteral("lowDiffLayout"));
    lowDiffLabel = new QLabel(subPage);
    lowDiffLabel->setObjectName(QStringLiteral("lowDiffLabel"));
    lowDiffLayout->addWidget(lowDiffLabel);
    lowDiffSlider = new QSlider(subPage);
    lowDiffSlider->setObjectName(QStringLiteral("lowDiffSlider"));
    lowDiffLayout->addWidget(lowDiffSlider);
    vBoxLayout->addLayout(lowDiffLayout);

    upDiffLayout = new QHBoxLayout();
    upDiffLayout->setObjectName(QStringLiteral("upDiffLayout"));
    upDiffLabel = new QLabel(subPage);
    upDiffLabel->setObjectName(QStringLiteral("upDiffLabel"));
    upDiffLayout->addWidget(upDiffLabel);
    upDiffSlider = new QSlider(subPage);
    upDiffSlider->setObjectName(QStringLiteral("upDiffSlider"));
    upDiffLayout->addWidget(upDiffSlider);
    vBoxLayout->addLayout(upDiffLayout);


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

    label_mask = new QLabel(scrollAreaWidgetContents);
    label_mask->setObjectName(QStringLiteral("label_mask"));
    label_mask->setText("label_mask");
    imageLabel_mask = new QLabel(scrollAreaWidgetContents);
    imageLabel_mask->setObjectName(QStringLiteral("imageLabel_mask"));
    imageLabel_mask->setText("imageLabel_mask");
    formLayout->setWidget(3, QFormLayout::LabelRole, label_mask);
    formLayout->setWidget(3, QFormLayout::FieldRole, imageLabel_mask);


    scrollAreaWidgetContents->resize(formLayout->sizeHint());

    vBoxLayout->addWidget(scrollArea);

    retranslateUi();

    connect(comboBox, &QComboBox::currentTextChanged, this, &MIFloodFill::onComboBoxCurrentTextChanged);
    connect(button, &QPushButton::clicked, this, &MIFloodFill::selectFile);
    connect(lowDiffSlider, &QSlider::valueChanged, this, &MIFloodFill::onLowDiffSliderValueChanged);
    connect(upDiffSlider, &QSlider::valueChanged, this, &MIFloodFill::onUpDiffSliderValueChanged);
    connect(imShowChechBox, &QCheckBox::clicked, this, &MIFloodFill::onImShowChechBoxClicked);
    connect(isUseColorChechBox, &QCheckBox::clicked, this, &MIFloodFill::onIsUseColorChechBoxClicked);
    connect(isUseMaskChechBox, &QCheckBox::clicked, this, &MIFloodFill::onIsUseMaskChechBoxClicked);
    connect(clearButton, &QPushButton::clicked, this, &MIFloodFill::onClearButtonClicked);

    this->addSubPage(subPage);

}


void MIFloodFill::retranslateUi()
{
    QImage qimage;
    label->setText("待处理图片:");
    imagePath->setText("../assert/image23.jpg");
    button->setText("...");
    clearButton->setText("清除图片");
    imShowChechBox->setText("使用OpenCV的imshow");
    imShowChechBox->setChecked(isImShow);
    isUseMaskChechBox->setText("使用掩膜图");
    isUseMaskChechBox->setChecked(isUseMask);
    isUseColorChechBox->setText("使用彩色图");
    isUseColorChechBox->setChecked(isUseColor);
    lowDiffSlider->setOrientation(Qt::Horizontal);
    lowDiffSlider->setMinimum(0);
    lowDiffSlider->setMaximum(upDiffMax);
    lowDiffSlider->setSingleStep(1);
    lowDiffSlider->setTickPosition(QSlider::TicksAbove);
    lowDiffSlider->setValue(upDiffMax);
    lowDiffLabel->setText("负差最大值:" + QString("%1").arg(upDiffMax));
    upDiffSlider->setOrientation(Qt::Horizontal);
    upDiffSlider->setMinimum(0);
    upDiffSlider->setMaximum(upDiffMax);
    upDiffSlider->setSingleStep(1);
    upDiffSlider->setTickPosition(QSlider::TicksAbove);
    upDiffSlider->setValue(upDiffMax);
    upDiffLabel->setText("正差最大值:" + QString("%1").arg(upDiffMax));

    g_srcImage  = imread(imagePath->text().toStdString());
    if( !g_srcImage.data )
    {
        qDebug() << "imread: 读取图像错误, " << imagePath->text();
    }
    g_srcImage.copyTo(g_dstImage);//拷贝源图到目标图
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//转换三通道的image0到灰度图
    g_maskImage.create(g_srcImage.rows+2, g_srcImage.cols+2, CV_8UC1);//利用image0的尺寸来初始化掩膜mask
    g_maskImage = Scalar::all(0);	//将mask所有元素设置为0
    imageLabel_src->setText("imageLabel_src");
    qimage = cvMat2QImage(g_srcImage);
    imageLabel_src->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_src->resize(QSize(qimage.width(),qimage.height()));
    label_src->setText(MINAME+QString("【原图】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    imageLabel_dst->setText("imageLabel_dst");
    qimage = cvMat2QImage(g_srcImage);
    imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_dst->resize(QSize(qimage.width(),qimage.height()));
    imageLabel_dst->installEventFilter(this);//安装事件过滤器
    label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    imageLabel_mask->setText("imageLabel_mask");
    qimage = cvMat2QImage(g_maskImage);
    imageLabel_mask->setPixmap(QPixmap::fromImage(qimage));
    imageLabel_mask->resize(QSize(qimage.width(),qimage.height()));
    label_mask->setText(MINAME+QString("【Mask】\n width:%1 \n height:%2").arg(qimage.width()).arg(qimage.height()));
    scrollAreaWidgetContents->resize(formLayout->sizeHint());

    comboBox->clear();
    comboBox->insertItems(0, QStringList()
     << QApplication::translate("FloodFill", "使用空范围的漫水填充", 0)
     << QApplication::translate("FloodFill", "使用渐变、固定范围的漫水填充", 0)
     << QApplication::translate("FloodFill", "使用渐变、浮动范围的漫水填充", 0)
     << QApplication::translate("FloodFill", "操作标志符的低八位使用4位的连接模式", 0)
     << QApplication::translate("FloodFill", "操作标志符的低八位使用8位的连接模式", 0)
    );
    fillMode = comboBox->currentIndex();
}


void MIFloodFill::selectFile()
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

        g_srcImage.copyTo(g_dstImage);//拷贝源图到目标图
        cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//转换三通道的image0到灰度图
        g_maskImage.create(g_srcImage.rows+2, g_srcImage.cols+2, CV_8UC1);//利用image0的尺寸来初始化掩膜mask
        g_maskImage = Scalar::all(0);	//将mask所有元素设置为0
        qimage = cvMat2QImage(g_dstImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));
        imageLabel_dst->resize(QSize(qimage.width(),qimage.height()));
        label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));

        qimage = cvMat2QImage(g_maskImage);
        imageLabel_mask->setPixmap(QPixmap::fromImage(qimage));
        imageLabel_mask->resize(QSize(qimage.width(),qimage.height()));
        label_mask->setText(MINAME+QString("【Mask】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));
        scrollAreaWidgetContents->resize(formLayout->sizeHint());
    }
    else
    {
        qDebug() << " 未选择文件 ";
    }
}


void MIFloodFill::onSubmitClicked()
{
    QMessageBox::information(NULL,"点击" ,"不需要进行处理",
                              QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
}


void MIFloodFill::onLowDiffSliderValueChanged(int val)
{
    QImage qimage;
    lowDifference = val;
    lowDiffLabel->setText("负差最大值:" + QString("%1").arg(lowDifference));
    g_maskImage = Scalar::all(0);	//将mask所有元素设置为0
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//转换三通道的image0到灰度图
    g_srcImage.copyTo(g_dstImage);
    if( this->isUseColor )
    {
        qimage = cvMat2QImage(g_dstImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
        label_dst->setText(MINAME+QString("【原图】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));
    }
    else
    {
        qimage = cvMat2QImage(g_grayImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
        label_dst->setText(MINAME+QString("【原图】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));
    }

    qimage = cvMat2QImage(g_maskImage);
    imageLabel_mask->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_mask->setText(MINAME+QString("【Mask】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));
}


void MIFloodFill::onUpDiffSliderValueChanged(int val)
{
    QImage qimage;
    upDifference = val;
    upDiffLabel->setText("正差最大值:" + QString("%1").arg(upDifference));
    g_maskImage = Scalar::all(0);	//将mask所有元素设置为0
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//转换三通道的image0到灰度图
    g_srcImage.copyTo(g_dstImage);
    if( this->isUseColor )
    {
        qimage = cvMat2QImage(g_dstImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
        label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));
    }
    else
    {
        qimage = cvMat2QImage(g_grayImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
        label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));
    }
    qimage = cvMat2QImage(g_maskImage);
    imageLabel_mask->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_mask->setText(MINAME+QString("【Mask】\n width:%1 \n height:%2")
                       .arg(qimage.width()).arg(qimage.height()));
}


bool MIFloodFill::eventFilter(QObject *obj, QEvent *event)
{
    qDebug() << obj;
    if (obj == imageLabel_dst)//指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress)//mouse button pressed
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                qDebug() << "x: " << mouseEvent->x() << " y:" << mouseEvent->y();
                qDebug() << "lowDifference: " << lowDifference << " UpDifference:" << upDifference;
                qDebug() << "fillMode: " << fillMode;

                //-------------------【<1>调用floodFill函数之前的参数准备部分】---------------
                Point seed = Point(mouseEvent->x(), mouseEvent->y());
                // 空范围的漫水填充，此值设为0，否则设为全局的lowDifference
                int lowDiff = (fillMode == 0) ? 0 : lowDifference;
                // 空范围的漫水填充，此值设为0，否则设为全局的UpDifference
                int upDiff = (fillMode == 0) ? 0 : upDifference;

                //标识符的0~7位为connectivity，8~15位为g_n左移8位的值，16~23位为FLOODFILL_FIXED_RANGE或者0
                int flags = connectivity + (newMaskVal << 8) +(fillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

                //随机生成bgr值
                int b = (unsigned)theRNG() & 255;//随机返回一个0~255之间的值
                int g = (unsigned)theRNG() & 255;//随机返回一个0~255之间的值
                int r = (unsigned)theRNG() & 255;//随机返回一个0~255之间的值
                Rect ccomp;//定义重绘区域的最小边界矩形区域
                //创建窗口
                if( this->isImShow )
                {
                    namedWindow( (QString(MINAME)+QString("【效果图】")).toStdString() );
                    if( this->isUseMask )
                    {
                        namedWindow( "mask" );
                    }
                }
                // 在重绘区域像素的新值，若是彩色图模式，取Scalar(b, g, r)；若是灰度图模式，取Scalar(r*0.299 + g*0.587 + b*0.114)
                Scalar newVal = isUseColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);

                Mat dst;
                if( isUseColor )
                {
                    dst = g_dstImage;
                }
                else
                {
                    dst = g_grayImage;
                }
                int area;

                //--------------------【<2>正式调用floodFill函数】-----------------------------
                if( this->isUseMask )
                {
                    threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);
                    area = floodFill(dst, g_maskImage, seed, newVal, &ccomp, Scalar(lowDiff, lowDiff, lowDiff),
                        Scalar(upDiff, upDiff, upDiff), flags);
                    //显示掩码图
                    if( this->isImShow && this->isUseMask )
                    {
                        imshow( "mask", g_maskImage );
                    }
                }
                else
                {
                    area = floodFill(dst, seed, newVal, &ccomp, Scalar(lowDiff, lowDiff, lowDiff),
                        Scalar(upDiff, upDiff, upDiff), flags);
                }

                //显示效果图
                if( this->isImShow )
                {
                    imshow((QString(MINAME)+QString("【效果图】")).toStdString(), dst);
                }
                qDebug() << area << " 个像素被重绘\n";
                QImage qimage = cvMat2QImage(dst);
                imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
                label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                                   .arg(qimage.width()).arg(qimage.height()));
                if( this->isUseMask )
                {
                    qimage = cvMat2QImage(g_maskImage);
                    imageLabel_mask->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
                    label_mask->setText(MINAME+QString("【Mask】\n width:%1 \n height:%2")
                                   .arg(qimage.width()).arg(qimage.height()));
                }
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

void MIFloodFill::onComboBoxCurrentTextChanged(QString text)
{
    QImage qimage;
    qDebug() << "index:" << comboBox->currentIndex() << " Name:" << text;
    fillMode = comboBox->currentIndex();
    switch(fillMode)
    {
    case '0':
        qDebug() << "使用空范围的漫水填充\n";
        fillMode = 0;
        break;
        //如果键盘按键“5”被按下，使用渐变、固定范围的漫水填充
    case '1':
        qDebug() << "使用渐变、固定范围的漫水填充\n";
        fillMode = 1;
        break;
        //如果键盘按键“6”被按下，使用渐变、浮动范围的漫水填充
    case '2':
        qDebug() << "使用渐变、浮动范围的漫水填充\n";
        fillMode = 2;
        break;
        //如果键盘按键“7”被按下，操作标志符的低八位使用4位的连接模式
    case '3':
        qDebug() << "操作标志符的低八位使用4位的连接模式\n";
        connectivity = 4;
        break;
        //如果键盘按键“8”被按下，操作标志符的低八位使用8位的连接模式
    case '4':
        qDebug() << "操作标志符的低八位使用8位的连接模式\n";
        connectivity = 8;
        break;
    }
    g_maskImage = Scalar::all(0);	//将mask所有元素设置为0
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//转换三通道的image0到灰度图
    g_srcImage.copyTo(g_dstImage);
    if( this->isUseColor )
    {
        qimage = cvMat2QImage(g_dstImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
        label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));
    }
    else
    {
        qimage = cvMat2QImage(g_grayImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
        label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));
    }
    qimage = cvMat2QImage(g_maskImage);
    imageLabel_mask->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_mask->setText(MINAME+QString("【Mask】\n width:%1 \n height:%2")
                   .arg(qimage.width()).arg(qimage.height()));
}


void MIFloodFill::onImShowChechBoxClicked(bool isImShow)
{
    this->isImShow = isImShow;
}


void MIFloodFill::onIsUseColorChechBoxClicked(bool isUseColor)
{
    QImage qimage;
    this->isUseColor = isUseColor;
    g_maskImage = Scalar::all(0);	//将mask所有元素设置为0
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//转换三通道的image0到灰度图
    g_srcImage.copyTo(g_dstImage);
    if( this->isUseColor )
    {
        qimage = cvMat2QImage(g_dstImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
        label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));
    }
    else
    {
        qimage = cvMat2QImage(g_grayImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
        label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));
    }
    qimage = cvMat2QImage(g_maskImage);
    imageLabel_mask->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_mask->setText(MINAME+QString("【Mask】\n width:%1 \n height:%2")
                   .arg(qimage.width()).arg(qimage.height()));
}


void MIFloodFill::onIsUseMaskChechBoxClicked(bool isUseMask)
{
    this->isUseMask = isUseMask;
    g_maskImage = Scalar::all(0);

    //显示掩码图
    if( this->isImShow && this->isUseMask)
    {
        imshow("mask", g_maskImage);
    }
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//转换三通道的image0到灰度图
}

void MIFloodFill::onClearButtonClicked(bool isClear)
{
    QImage qimage;
    cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
    g_maskImage = Scalar::all(0);
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//转换三通道的image0到灰度图
    g_srcImage.copyTo(g_dstImage);
    if( this->isUseColor )
    {
        qimage = cvMat2QImage(g_dstImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
        label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));
    }
    else
    {
        qimage = cvMat2QImage(g_grayImage);
        imageLabel_dst->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
        label_dst->setText(MINAME+QString("【效果图】\n width:%1 \n height:%2")
                           .arg(qimage.width()).arg(qimage.height()));
    }
    qimage = cvMat2QImage(g_maskImage);
    imageLabel_mask->setPixmap(QPixmap::fromImage(qimage));  // 将图片显示到label上
    label_mask->setText(MINAME+QString("【Mask】\n width:%1 \n height:%2")
                   .arg(qimage.width()).arg(qimage.height()));
}
