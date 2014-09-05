#-------------------------------------------------
#
# Project created by QtCreator 2014-08-25T23:57:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoEnroll
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    my_qlabel.cpp \
    video_reader.cpp \
    video_data.cpp

HEADERS  += mainwindow.h \
    video_reader.h \
    my_qlabel.h \
    video_data.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv2
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
