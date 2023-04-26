#include "dialog_dpinfo.h"
#include "ui_dialog_dpinfo.h"

Dialog_dpInfo::Dialog_dpInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_dpInfo)
{
    ui->setupUi(this);
}

Dialog_dpInfo::~Dialog_dpInfo()
{
    delete ui;
}

void Dialog_dpInfo::on_pushButton_clicked()
{
    emit sendData(ui->lineEdit_sourcePath->text(), ui->lineEdit_PedestrianMaxium->text(), ui->lineEdit_nameDetectPoint->text());
    this->close();
}

