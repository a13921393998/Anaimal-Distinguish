#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "print.h"
#include "picture_show.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void give_inf(File_Manage *r);
    void give_pic_inf(File_Manage *r);
private:
    Ui::MainWindow *ui;
    File_Manage *r;
    Print *t;
    Picture_Show *p;
private slots:
    void toprint();
    void re_Main();
    void pic_re_Main();
    void to_picture_show();
    void data_renew(File_Manage *r);
};
#endif // MAINWINDOW_H
