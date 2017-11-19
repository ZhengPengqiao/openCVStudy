TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

LIBS += -lopencv_calib3d
LIBS += -lopencv_highgui
LIBS += -lopencv_photo
LIBS += -lopencv_contrib
LIBS += -lopencv_imgproc
LIBS += -lopencv_stitching
LIBS += -lopencv_core
LIBS += -lopencv_legacy
LIBS += -lopencv_superres
LIBS += -lopencv_features2d
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_flann
LIBS += -lopencv_objdetect
LIBS += -lopencv_videostab
LIBS += -lopencv_gpu
LIBS += -lopencv_ocl


DISTFILES += \
    saber.jpg
