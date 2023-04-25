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

private:
    Ui::MapDisplay *ui;
};

#endif // MAPDISPLAY_H
