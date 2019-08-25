#-------------------------------------------------
#
# Project created by QtCreator 2019-06-04T00:39:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mibase.cpp \
    miboxfilter.cpp \
    miblur.cpp \
    migaussianblur.cpp \
    mimedianblur.cpp \
    mibilateralfilter.cpp \
    midilate.cpp \
    mierode.cpp \
    mierodedilate.cpp \
    miopenclose.cpp \
    mitopblackhat.cpp \
    mithreshold.cpp \
    mifloodfill.cpp \
    mipyrresize.cpp \
    miseparatoritem.cpp \
    micanny.cpp \
    misobel.cpp \
    mischarr.cpp \
    milaplacian.cpp




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


HEADERS  += mainwindow.h \
    mibase.h \
    miboxfilter.h \
    miblur.h \
    migaussianblur.h \
    mimedianblur.h \
    mibilateralfilter.h \
    midilate.h \
    mierode.h \
    mierodedilate.h \
    miopenclose.h \
    mitopblackhat.h \
    mithreshold.h \
    mifloodfill.h \
    mipyrresize.h \
    miseparatoritem.h \
    micanny.h \
    misobel.h \
    mischarr.h \
    milaplacian.h

FORMS    +=
