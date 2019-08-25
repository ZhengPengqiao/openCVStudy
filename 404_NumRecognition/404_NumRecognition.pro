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

unix: LIBS += -L$$PWD/../Doc/opencv-3.4.0_install/lib/
unix: INCLUDEPATH += $$PWD/../Doc/opencv-3.4.0_install/include
unix: DEPENDPATH += $$PWD/../Doc/opencv-3.4.0_install/include

unix: LIBS += -lopencv_dnn
unix: LIBS += -lopencv_ml
unix: LIBS += -lopencv_objdetect
unix: LIBS += -lopencv_shape
unix: LIBS += -lopencv_stitching
unix: LIBS += -lopencv_superres
unix: LIBS += -lopencv_videostab
unix: LIBS += -lopencv_calib3d
unix: LIBS += -lopencv_features2d
unix: LIBS += -lopencv_highgui
unix: LIBS += -lopencv_videoio
unix: LIBS += -lopencv_imgcodecs
unix: LIBS += -lopencv_video
unix: LIBS += -lopencv_photo
unix: LIBS += -lopencv_imgproc
unix: LIBS += -lopencv_flann
unix: LIBS += -lopencv_core


win32: LIBS += -L$$PWD/../Doc/opencv-3.4.1_install_win_mingw32/lib/
win32: INCLUDEPATH += $$PWD/../Doc/opencv-3.4.1_install_win_mingw32/include
win32: DEPENDPATH += $$PWD/../Doc/opencv-3.4.1_install_win_mingw32/include

win32: LIBS += -llibopencv_dnn341
win32: LIBS += -llibopencv_ml341
win32: LIBS += -llibopencv_objdetect341
win32: LIBS += -llibopencv_shape341
win32: LIBS += -llibopencv_stitching341
win32: LIBS += -llibopencv_superres341
win32: LIBS += -llibopencv_videostab341
win32: LIBS += -llibopencv_calib3d341
win32: LIBS += -llibopencv_features2d341
win32: LIBS += -llibopencv_highgui341
win32: LIBS += -llibopencv_videoio341
win32: LIBS += -llibopencv_imgcodecs341
win32: LIBS += -llibopencv_video341
win32: LIBS += -llibopencv_photo341
win32: LIBS += -llibopencv_imgproc341
win32: LIBS += -llibopencv_flann341
win32: LIBS += -llibopencv_core341


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
