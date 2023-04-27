#ifndef DETECTPOINT_H
#define DETECTPOINT_H

#include <fstream>
//#include <sstream>
//#include <iostream>
#include <QPoint>
#include <QString>
#include "yolov5_detector.h"
#include "queue_xqqueue.h"

using namespace std;

class DetectPoint : public YOLOv5_Detector
{
public:
    DetectPoint(Net_config config);
//    YOLOv5_Detector detector(Net_config config);           // 把YOLOv5_Detector作为基类

    QString sourcePath;         // 视频源
    bool lable_visible;             // 监测点上方的实时人流量标签是否可见
    int volume_warning;             // 监测点的人流量上限
    int volume_detecting;           // 检测出的人数
    QPoint pos;                     // 监测点坐标
    QString label;              // 监测点的显示标签名
    Mat frame;                  // 要输入到YOLO推理的帧
//    int results[5] = {0, 0, 0, 0, 0};    // 临时存储检测结果（人流量数据）
    xq::xqQueue<int> *results;   // 临时存储检测结果（人流量数据）

};

#endif // DETECTPOINT_H
