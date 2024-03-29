QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    detectpoint.cpp \
    dialog_dpinfo.cpp \
    main.cpp \
    mainwindow.cpp \
    mapdisplay.cpp \
    qyolodetectthread.cpp \
    yolov5_detector.cpp

HEADERS += \
    detectpoint.h \
    dialog_dpinfo.h \
    mainwindow.h \
    mapdisplay.h \
    queue_xqqueue.h \
    qyolodetectthread.h \
    yolov5_detector.h

FORMS += \
    dialog_dpinfo.ui \
    mainwindow.ui \
    mapdisplay.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += E:\Coding\OpenCV\opencv-build\install\include
LIBS += E:\Coding\OpenCV\opencv-build\lib\libopencv_*.a

RESOURCES += \
    res.qrc
