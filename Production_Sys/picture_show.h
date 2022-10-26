#ifndef PICTURE_SHOW_H
#define PICTURE_SHOW_H

#include <QGroupBox>
#include "file_manage.h"
namespace Ui {
class Picture_Show;
}

class Picture_Show : public QGroupBox
{
    Q_OBJECT

public:
    explicit Picture_Show(QWidget *parent = nullptr);
    ~Picture_Show();
    int *Sys_data;
    bool equal(int i);
    QString judgement();
    void clear();
signals:
    void sSignal();
private:
    Ui::Picture_Show *ui;
    File_Manage *r;
private slots:
    void print_result();
    void get_inf(File_Manage *r);
    void sSlot(){
        emit sSignal();
    }
    void set_check_type(int a,int b);
};

#endif // PICTURE_SHOW_H
