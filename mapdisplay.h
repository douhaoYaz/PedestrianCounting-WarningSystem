#ifndef MAPDISPLAY_H
#define MAPDISPLAY_H

#include <QMainWindow>

namespace Ui {
class MapDisplay;
}

class MapDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapDisplay(QWidget *parent = nullptr);
    ~MapDisplay();

    QString pic;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MapDisplay *ui;
};

#endif // MAPDISPLAY_H
