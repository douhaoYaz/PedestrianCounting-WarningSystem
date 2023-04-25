#include "mainwindow.h"

#include <QApplication>

#include "yolov5_detector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Net_config yolo_nets[4] = {
        {0.5, 0.5, 0.5, "yolov5s"},
        {0.5, 0.5, 0.5,  "yolov5m"},
        {0.5, 0.5, 0.5, "yolov5l"},
        {0.5, 0.5, 0.5, "yolov5x"}
    };

    YOLOv5_Detector yolo_model(yolo_nets[0]);
    string imgpath = "F:/Work and Learn/Projects/QtProject/PedestrianCounting-WarningSystem/bus.jpg";
    Mat srcimg = imread(imgpath);
    yolo_model.detect(srcimg);

    static const string kWinName = "Deep learning object detection in OpenCV";
    namedWindow(kWinName, WINDOW_NORMAL);
    imshow(kWinName, srcimg);
    waitKey(0);
    destroyAllWindows();

    return a.exec();
}
