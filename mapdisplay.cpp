#include "mapdisplay.h"
#include "ui_mapdisplay.h"
#include <QFileDialog>
#include <QPainter>
//#include "detectpoint.h"
#include <memory>
#include <QMouseEvent>
#include <iostream>
#include <QFont>
#include <QDebug>
#include <opencv2/videoio.hpp>
#include <QMessageBox>

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

// 实现按钮：1.导入地图 2.添加监测点（包括视频源、人流量上限、监测点名称） 3.显示/隐藏 监测点上方的实时人流量标签 4.显示监测点的历史人流量数据 5.编辑监测点 6.删除监测点 7.显示监测点实时行人检测效果（后处理图片） 8.开始检测
// 实现功能：1.每n秒截取视频一帧，然后输入到YOLOv5行人识别模型得到实时人流量  2.若某点的实时人流量超过该点的人流量上限，系统发出弹窗预警


void MapDisplay::on_pushButton_clicked()    // 导入地图
{
    QString temp = QFileDialog::getOpenFileName(this, "选择文件", "D:/", "图像文件(*.jpg *.jpeg *.bmg *.png *.gif)");
    if (temp != "") this->pic = temp;//传入图片存储路径
    update();
}

double MapDisplay::dist(QPoint a, QPoint b)//计算两点间距离的函数
{
    return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}

bool MapDisplay::isin(QPoint x, QPoint y, int n)//判断鼠标光标是否点击成功（半径n的圆域范围内）
{
    if (dist(x, y) <= n) return true;
    else return false;
}

void MapDisplay::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//画笔，this为当前窗口
    painter.drawPixmap(190, 70, 1000, 700, QPixmap(pic));// 载入背景图片并显示出来

    QFont font1("Microsoft YaHei", 12);     // 设置监测点标签的显示字体
    painter.drawRect(190, 70, 1000, 700);   //矩形大小，窗口大小

    painter.setPen(Qt::black);
    painter.setBrush(Qt::blue);
    painter.setFont(font1);
    for (int i = 1; i <= count_detectPoint; i++)
    {
        painter.drawEllipse(detectPoint_group[i-1]->pos, 4, 4);//把点画出来
        painter.drawText(QPoint(detectPoint_group[i-1]->pos.x() + 5, detectPoint_group[i-1]->pos.y() + 6), detectPoint_group[i-1]->label);//画出点的标签，pl[i]为标签
//        qDebug() << "监测点标签名：" << detectPoint_group[i-1]->label;
    }
}

void MapDisplay::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        switch (type_mouseEvent)
        {
        case 1:     // 添加监测点
            if(event->pos().x() >= 190 && event->pos().x() <= 1190 && event->pos().y()>70 && event->pos().y() <= 770){      // 判断所加的点是否在窗口范围内(本来不想加这个判断的，但是switch case语句里不能新建变量，而我需要新建一个变量flag，在新添加的监测点离某监测点距离太近时 取消添加，于是要用一个flag来帮助跳出swich case
                int flag=0;
                for(int i=0; i<count_detectPoint; i++){
                    if(isin(event->pos(), detectPoint_group[i]->pos, 20)){          // 鼠标事件坐标位于监测点i的半径之内，表示要新添加的监测点 离监测点i距离太近
                        QMessageBox::warning(this, "警告", "添加点离监测点_" + detectPoint_group[i]->label + "距离太近，请重新添加");
                        flag=1;
                        break;
                    }
                }
                if(flag==1) break;
                addDetectPoint(event->pos());       // 添加监测点，总监测点数+1
                setDetectPointInfo(count_detectPoint-1);    // 为新添加的监测点设置信息
                update();
            }
            break;
        case 2:     // 编辑监测点
            // TODO: 判断鼠标事件坐标是否位于某监测点半径之内，若是，则表示选中该监测点，然后弹窗对话框让用户输入该监测点的视频源、人流量上限
            for(int i=0; i<count_detectPoint; i++){
                if(isin(event->pos(), detectPoint_group[i]->pos, 20)){      // 鼠标事件坐标位于监测点i的半径之内，表示选中该监测点i
                    setDetectPointInfo(i);
                    return;
                }
//                else{       // 未选中监测点
//                    QMessageBox::warning(this, "警告", "未选中监测点");
//                }
            }
            QMessageBox::warning(this, "警告", "未选中监测点");
            break;
        case 3:     // 删除监测点
//            std::cout << "Test case 3";
            // TODO: 与case2类似
            break;
        case 4:     // 开始检测
            // 考虑是否使用多线程
            // 指定间隔截取视频帧作为模型输入
            // 用一个for循环使每个监测点相继进行推理？
            string imgpath = "F:/Work and Learn/Projects/QtProject/PedestrianCounting-WarningSystem/bus.jpg";
            Mat srcimg = imread(imgpath);
            detectPoint_group[0]->detect(srcimg);
            break;
        }
    }
}


void MapDisplay::on_pushButton_addDetectPoint_clicked()
{
    this->type_mouseEvent = 1;      // 用于鼠标事件函数中选择执行哪种处理函数
}

void MapDisplay::addDetectPoint(QPoint pos)             // 添加监测点
{
    Net_config yolo_nets = {0.5, 0.5, 0.5, "yolov5s"};
//    DetectPoint *detectPoint = new DetectPoint();
    std::shared_ptr<DetectPoint> dp(new DetectPoint(yolo_nets));
    dp->pos = pos;                                      // 将监测点坐标设置为 鼠标点击位置的坐标
    dp->label = QString::number(count_detectPoint+1);   // 将监测点显示的标签名默认设置为它的序号
    this->detectPoint_group.push_back(dp);              // 将新建的这个监测点智能指针添加到监测点智能指针vector容器中
    this->count_detectPoint++;                          // 已有监测点个数加1
    // 画一个dialog来接收用户输入的监测点的视频源、人流量上限

}

void MapDisplay::startDetect()
{
    // 如何添加多线程？
    // 两个任务：1. 对视频源间隔取帧  2.模型推理  3.检测结果显示（数据库）

//    for(int i=0; i<=count_detectPoint; i++){    // 遍历已有监测点
//    }
//    detectPoint_group[0]->sourcePath = "F:/Work and Learn/Projects/QtProject/PedestrianCounting-WarningSystem/CampusStreet.mp4";

    VideoCapture capture;
    Mat frame;
    frame = capture.open(detectPoint_group[0]->sourcePath.toStdString());       // 读取该监测点的视频源
    if(!capture.isOpened()){    // 无法打开视频
        QMessageBox::warning(this, "警告", "无法打开监测点视频源");
    }
    else{                       // 成功打开视频
        int count=0, frameRate=80, result;     // 计数、帧数截取间隔、检测结果
        while(true){
            if(capture.read(frame)){    // 视频帧流还未全部读取完
                count++;
                if(count % frameRate == 0){     // 够钟截取一帧
                    detectPoint_group[0]->frame = frame.clone();    // 将视频流当前帧 深拷贝给 该监测点作为模型输入的帧
                    qDebug() << "读取" << count / frameRate << "帧";
                    // TODO: 模型推理，存储检测结果
                    result = detectPoint_group[0]->detect(detectPoint_group[0]->frame);
                    // 优化：detect()里大部分时候不需要调用drawPred()，想办法把detect()改写成可以分离出drawPred()的形式
                    detectPoint_group[0]->results->insert(result);
                    ui->listWidget->addItem("监测点1："+ QString::number(result) + "人");
//                    ui->listWidget->repaint();
//                    update();
//                    ui->listWidget->viewport()->update();
                }
            }
            else{                       // 已全部读取完视频帧流
                QMessageBox::information(this, "监测点视频源状态", "已全部读取完视频帧流");
                break;
            }
        }
        detectPoint_group[0]->results->print_new2old();     // 把监测点的历史人流量数据按新到旧的顺序输出
        namedWindow("Pedestiran Detecting", cv::WINDOW_AUTOSIZE);
        imshow("Pedestiran Detecting", detectPoint_group[0]->frame);
        capture.release();
    }
}


void MapDisplay::on_pushButton_editDetectPoint_clicked()
{
    this->type_mouseEvent = 2;
}


void MapDisplay::on_pushButton_delDetectPoint_clicked()
{
    this->type_mouseEvent = 3;
}


void MapDisplay::on_pushButton_startDetect_clicked()
{
//    this->type_mouseEvent = 4;
    startDetect();
}

void MapDisplay::receiveData(QString sourcePath, QString pedestrianMaxium, QString label)
{
    this->sourcePath_temp = sourcePath;
    this->volume_detecting_temp = pedestrianMaxium.toInt();
    this->label_temp = label;
}


void MapDisplay::setDetectPointInfo(int index)
{
    dialog = new Dialog_dpInfo();
    // 待优化这个槽函数，如何使得槽函数接收到的值能直接赋给detectPoint_group[i]中
    connect(dialog, SIGNAL(sendData(QString,QString,QString)), this, SLOT(receiveData(QString,QString,QString)));
    if(dialog->exec() == QDialog::Accepted){
    }
    delete dialog;
    detectPoint_group[index]->sourcePath = this->sourcePath_temp;
    detectPoint_group[index]->volume_warning = this->volume_detecting_temp;
    detectPoint_group[index]->label = this->label_temp;
    qDebug() << "sourcePath:  " << detectPoint_group[index]->sourcePath;
    qDebug() << "pedestrian maxium:  " << detectPoint_group[index]->volume_warning;
    qDebug() << "label:  " << detectPoint_group[index]->label;
}
