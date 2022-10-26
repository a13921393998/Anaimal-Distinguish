#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "application.h"
#include "file_manage.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    r = new File_Manage();
    t = new Print();
    p = new Picture_Show();
    ui->setupUi(this);
    connect(t,SIGNAL(sSignal()),this,SLOT(re_Main()));
    connect(t,SIGNAL(data_renew(File_Manage *)),this,SLOT(data_renew(File_Manage *)));
    connect(this,SIGNAL(give_inf(File_Manage *)),t,SLOT(get_inf(File_Manage *)));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(toprint()));
    connect(p,SIGNAL(sSignal()),this,SLOT(pic_re_Main()));
    connect(this,SIGNAL(give_pic_inf(File_Manage *)),p,SLOT(get_inf(File_Manage *)));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(to_picture_show()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(close()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::re_Main(){
    t->clr();
    t->close();
    this->show();
}

void MainWindow::toprint(){
    emit give_inf(r);
    t->show();
}

void MainWindow::pic_re_Main(){
    p->clear();
    p->close();
    this->show();
}

void MainWindow::to_picture_show(){
    emit give_pic_inf(r);
    p->show();
}

void MainWindow::data_renew(File_Manage *r){
    delete this->r;
    this->r = r;
}
