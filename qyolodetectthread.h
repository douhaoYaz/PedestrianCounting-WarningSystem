#ifndef QYOLODETECTTHREAD_H
#define QYOLODETECTTHREAD_H

#include <QThread>
#include "detectpoint.h"
#include <memory>
#include <QMutex>
#include <QMetaType>
#include <QVariant>

Q_DECLARE_METATYPE(std::shared_ptr<DetectPoint>);   // 将std::shared_ptr<DetectPoint>这个类声明为元类型，才能作为信号与槽的参数传递

class QYoloDetectThread : public QThread
{
    Q_OBJECT
public:
    explicit QYoloDetectThread(QObject *parent = nullptr);
    QYoloDetectThread(std::shared_ptr<DetectPoint> dp);             // 重载构造函数

private:
    QMutex mutex;   // 互斥量

    bool m_paused=true; // 暂停线程
    bool m_stop=false;  // 停止线程

    std::shared_ptr<DetectPoint> dp;

    // QThread interface
protected:
    virtual void run() override;

signals:
//    void warning_flow(std::shared_ptr<DetectPoint> dp);       // 人流量预警信号
    void warning_flow(QVariant data);       // 人流量预警信号
};


//Q_DECLARE_METATYPE(std::shared_ptr<DetectPoint>);   // 将std::shared_ptr<DetectPoint>这个类声明为元类型，才能作为信号与槽的参数传递


#endif // QYOLODETECTTHREAD_H
