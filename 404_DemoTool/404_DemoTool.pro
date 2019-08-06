#-------------------------------------------------
#
# Project created by QtCreator 2017-08-10T19:37:29
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemoTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


LIBS += -L$$PWD/../Doc/opencv-3.4.0_install/lib/

INCLUDEPATH += $$PWD/../Doc/opencv-3.4.0_install/include
DEPENDPATH += $$PWD/../Doc/opencv-3.4.0_install/include

LIBS += -lopencv_dnn
LIBS += -lopencv_ml
LIBS += -lopencv_objdetect
LIBS += -lopencv_shape
LIBS += -lopencv_stitching
LIBS += -lopencv_superres
LIBS += -lopencv_videostab
LIBS += -lopencv_calib3d
LIBS += -lopencv_features2d
LIBS += -lopencv_highgui
LIBS += -lopencv_videoio
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_video
LIBS += -lopencv_photo
LIBS += -lopencv_imgproc
LIBS += -lopencv_flann
LIBS += -lopencv_core


SOURCES += main.cpp \
    mainwindow.cpp \
    customtabstyle.cpp \
    numbercheckfrom.cpp

HEADERS  += \
    mainwindow.h \
    customtabstyle.h \
    numbercheckfrom.h

FORMS    += \
    mainwindow.ui \
    numbercheckfrom.ui

DISTFILES +=

RESOURCES += \
    assert.qrc
