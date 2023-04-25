#ifndef DETECTPOINT_H
#define DETECTPOINT_H

#include <fstream>
//#include <sstream>
//#include <iostream>

using namespace std;

class DetectPoint
{
public:
    DetectPoint();
    std::string sourcePath;         // 视频源
    bool lable_visible;             // 监测点上方的实时人流量标签是否可见
    int volume_warning;             // 监测点的人流量上限
    int volume_detecting;           // 检测出的人数
};

#endif // DETECTPOINT_H
