TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui

DISTFILES += \
    saber.jpg
