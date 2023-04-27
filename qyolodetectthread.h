#ifndef QYOLODETECTTHREAD_H
#define QYOLODETECTTHREAD_H

#include <QThread>
#include "detectpoint.h"
#include <memory>
#include <QMutex>

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
};

#endif // QYOLODETECTTHREAD_H
