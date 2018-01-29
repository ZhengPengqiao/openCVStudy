TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

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