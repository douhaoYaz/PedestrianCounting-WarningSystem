#include "mapdisplay.h"
#include "ui_mapdisplay.h"

MapDisplay::MapDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapDisplay)
{
    ui->setupUi(this);
}

MapDisplay::~MapDisplay()
{
    delete ui;
}

// 实现按钮：1.导入地图 2.添加监测点（包括视频源、人流量上限、监测点名称） 3.显示/隐藏 监测点上方的实时人流量标签 4.显示监测点的历史人流量数据 5.编辑监测点 6.删除监测点
// 实现功能：1.每n秒截取视频一帧，然后输入到YOLOv5行人识别模型得到实时人流量  2.若某点的实时人流量超过该点的人流量上限，系统发出弹窗预警

