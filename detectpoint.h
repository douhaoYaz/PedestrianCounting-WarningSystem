#ifndef DETECTPOINT_H
#define DETECTPOINT_H

#include <fstream>
//#include <sstream>
//#include <iostream>
#include <QPoint>
#include <QString>

using namespace std;

class DetectPoint
{
public:
    DetectPoint();
    QString sourcePath;         // 视频源
    bool lable_visible;             // 监测点上方的实时人流量标签是否可见
    int volume_warning;             // 监测点的人流量上限
    int volume_detecting;           // 检测出的人数
    QPoint pos;                     // 监测点坐标
    QString label;              // 监测点的显示标签名
};

#endif // DETECTPOINT_H
