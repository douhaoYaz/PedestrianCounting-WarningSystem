#ifndef DIALOG_DPINFO_H
#define DIALOG_DPINFO_H

#include <QDialog>

namespace Ui {
class Dialog_dpInfo;
}

class Dialog_dpInfo : public QDialog
{
    Q_OBJECT
signals:
    void sendData(QString sourcePath, QString PedestrianMaxium, QString label);

public:
    explicit Dialog_dpInfo(QWidget *parent = nullptr);
    ~Dialog_dpInfo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_dpInfo *ui;
};

#endif // DIALOG_DPINFO_H
