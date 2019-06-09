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
    micanny.cpp



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
    micanny.h

FORMS    +=
