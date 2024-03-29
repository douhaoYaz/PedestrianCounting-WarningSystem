#include "qyolodetectthread.h"
#include <QDebug>

QYoloDetectThread::QYoloDetectThread(QObject *parent) : QThread(parent)
{

}

QYoloDetectThread::QYoloDetectThread(std::shared_ptr<DetectPoint> dp)
{
    this->dp = dp;
    //    qRegisterMetaType<std::shared_ptr<DetectPoint>>("std::shared_ptr<DetectPoint>");
}

void QYoloDetectThread::stopThread()
{
    m_stop = true;
}

void QYoloDetectThread::startDetect()
{
    m_paused = false;
}

void QYoloDetectThread::endDetect()
{
    m_paused = true;
}

void QYoloDetectThread::run()
{
    m_stop = false;     // 启动线程时令m_stop=false

    // 初始化准备工作
    VideoCapture capture;
    Mat frame;
    frame = capture.open(dp->sourcePath.toStdString());     // 读取该监测点的视频源
    if(!capture.isOpened()){    // 无法打开视频
        qDebug() << "无法打开监测点_" << dp->label << "的视频源，请编辑监测点视频源后重新开始检测";
        return; // 待优化：是结束线程好还是做点什么好
    }
    int count=0, frameRate=20, result;  // 计数、帧数截取间隔、检测结果
    msleep(500);        // 还要看看这个msleep()摆在哪好。作用是本线程初始化完还未开始YOLO推理时，等待其他线程也初始化好后再开始YOLO推理

//    //开始事件循环
//    while(!m_stop){
//        if(!m_paused){

//        }
////        m_stop = true;
//    }

    //开始事件循环
    while(!m_stop){
        if(!m_paused){
            // 开始检测
            if(capture.read(frame)){    // 成功读取视频帧
                count++;
                if(count % frameRate == 0){
                    qDebug() << "正在监测点_" << dp->label << "的线程中";
                    dp->frame = frame.clone();
                    qDebug() << "读取第" << count/frameRate << "帧";
                    result = dp->detect(dp->frame);
                    dp->results->insert(result);
                    if(result >= dp->volume_warning && dp->warning_flag == false){   // 若标志值状态为 不需发出预警弹窗
                        QVariant data;
                        data.setValue(dp);
                        emit warning_flow(data);                               // 发射人流量预警信号，参数为该超出人流量上限的监测点智能指针
                        qDebug() << "emit warning_flow";
                        dp->warning_flag = true;                                    // 需要预警弹窗
                    }
                    // TODO：将数据加到listWidget，目前想法是用信号与槽，参数有：标签或序号、数据，但感觉开销太大
                }
            }
            else{       // capture无法读取视频帧的情况
                cout << "can't read video in" << dp->label.toStdString() << endl;
                m_paused = true;
                m_stop = true;
                this->exit();
            }
        }
    }
    qDebug() << "已全部读取完监测点_" << dp->label << "的视频帧流";

    dp->results->print_new2old();
//    namedWindow("Pedestiran Detecting", cv::WINDOW_AUTOSIZE);
//    imshow("Pedestiran Detecting", dp->frame);
    capture.release();
//    msleep(5000);
    this->exit();

//    while(!m_stop){

//    }

    // 待优化：写个信号与槽，读取完视频帧流后发出结束信号，给主线程接收，让主线程停掉该线程
}

