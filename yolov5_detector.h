#ifndef YOLOV5_DETECTOR_H
#define YOLOV5_DETECTOR_H

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace cv;
using namespace dnn;
using namespace std;


struct Net_config
{
    float confThreshold; // class Confidence threshold
    float nmsThreshold;  // Non-maximum suppression threshold
    float objThreshold;  //Object Confidence threshold
    string netname;
};


class YOLOv5_Detector
{
public:
    YOLOv5_Detector(Net_config config);
    int detect(Mat& frame);

private:
    Net net;
    float confThreshold;
    float nmsThreshold;
    float objThreshold;
    char netname[20];
    vector<string> classes;
    const string classesFile = "F:/Work and Learn/Projects/QtProject/PedestrianCounting-WarningSystem/coco.names";
    const int inpWidth = 640;
    const int inpHeight = 640;
    const float anchors[3][6] = {{10.0, 13.0, 16.0, 30.0, 33.0, 23.0}, {30.0, 61.0, 62.0, 45.0, 59.0, 119.0},{116.0, 90.0, 156.0, 198.0, 373.0, 326.0}};
    const float stride[3] = { 8.0, 16.0, 32.0 };

    void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame);
    void sigmoid(Mat* out, int length);
};

//Net_config yolo_nets[4] = {
//    {0.5, 0.5, 0.5, "yolov5s"},
//    {0.5, 0.5, 0.5,  "yolov5m"},
//    {0.5, 0.5, 0.5, "yolov5l"},
//    {0.5, 0.5, 0.5, "yolov5x"}
//};

#endif // YOLOV5_DETECTOR_H
