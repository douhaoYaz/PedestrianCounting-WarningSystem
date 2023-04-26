#include "detectpoint.h"

DetectPoint::DetectPoint(Net_config config):YOLOv5_Detector(config)
{
//    results(6);     // 初始化循环队列成员变量results
    results = new xq::xqQueue<int>(6);      // 初始化循环队列成员变量results
}
