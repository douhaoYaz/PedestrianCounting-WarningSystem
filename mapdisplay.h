#ifndef MAPDISPLAY_H
#define MAPDISPLAY_H

#include <QMainWindow>
#include <vector>
#include "detectpoint.h"
#include <memory>

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

private:
    Ui::MapDisplay *ui;
    QString pic;
    int type_mouseEvent;                // 用于鼠标事件函数中选择执行哪种处理函数，以后可优化为枚举变量，暂时先用整型
    std::vector<std::shared_ptr<DetectPoint>> detectPoint_group;    // 存储 指向监测点的智能指针 的vector容器

    void addDetectPoint(QPoint pos);    // 添加监测点

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *) override;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // MAPDISPLAY_H
