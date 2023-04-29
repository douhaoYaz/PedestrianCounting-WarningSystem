#ifndef MAPDISPLAY_H
#define MAPDISPLAY_H

#include <QMainWindow>
#include <vector>
#include "detectpoint.h"
#include <memory>
#include <cmath>
#include "dialog_dpinfo.h"
#include "qyolodetectthread.h"
#include <QTimer>

namespace Ui {
class MapDisplay;
}

class MapDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapDisplay(QWidget *parent = nullptr);
    ~MapDisplay();

    int count_detectPoint = 0;          // 已有监测点个数

private slots:
    void on_pushButton_clicked();

    void on_pushButton_addDetectPoint_clicked();

    void on_pushButton_editDetectPoint_clicked();

    void on_pushButton_delDetectPoint_clicked();

    void on_pushButton_startDetect_clicked();

    void on_pushButton_endDetect_clicked();

    void on_mTimer_timeout();       // 定时器响应槽函数，connect写在了构造函数中

    void on_pushButton_continueDetect_clicked();

    void on_pushButton_pauseDetect_clicked();

    void on_pushButton_editTitle_clicked();

    void on_pushButton_displayHistory_clicked();

    void on_pushButton_dispalyLast_clicked();

public slots:
    void receiveData(QString sourcePath, QString pedestrianMaxium, QString label);

//    void warning_handler(std::shared_ptr<DetectPoint> dp);        // 人流量预警槽函数
    void warning_handler(QVariant data);        // 人流量预警槽函数

private:
    Ui::MapDisplay *ui;
    QString pic;
    int type_mouseEvent=0;                // 用于鼠标事件函数中选择执行哪种处理函数，以后可优化为枚举变量，暂时先用整型
    std::vector<std::shared_ptr<DetectPoint>> detectPoint_group;    // 存储 指向监测点的智能指针 的vector容器
    Dialog_dpInfo *dialog;
//    QString sourcePath_temp;            // 临时存放 接收到对话框dialog的视频源路径
//    int volume_detecting_temp;               // 临时存放 接收到对话框dialog的人流量上限
//    QString label_temp;                 // 临时存放 接收到对话框dialog的标签名
    int checked_detectPoint = -1;            // 表示当前被选中的监测点序号
    std::vector<QYoloDetectThread*> yoloDetectThreads;   // 用于YOLO检测的多线程vector容器
    QTimer mTimer;                          //定时器

    void addDetectPoint(QPoint pos);    // 添加监测点
    void startDetect();                 // 开始检测
    bool isin(QPoint x, QPoint y, int n = 10);
    double dist(QPoint a, QPoint b);
    void setDetectPointInfo(int checked_detectPoint);     // 设置监测点信息
    void updateCheckedDetectPoint(QPoint mousePos);   // 根据鼠标点击坐标确定当前被选中的监测点序号

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *) override;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // MAPDISPLAY_H
