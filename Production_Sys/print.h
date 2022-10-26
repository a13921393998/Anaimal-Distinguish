#ifndef PRINT_H
#define PRINT_H

#include <QGroupBox>
//#include "application.h"
#include "file_manage.h"
namespace Ui {
class Print;
}

class Print : public QGroupBox
{
    Q_OBJECT

public:
    explicit Print(QWidget *parent = nullptr);
    ~Print();
    bool exist_knw(int i);
    bool exist_result(int i);
    void clr();
signals:
    void sSignal();
    void data_renew(File_Manage *r);
private:
    Ui::Print *ui;
    File_Manage *r;
private slots:
    void get_inf(File_Manage *r);
    void add_knw();
    void delete_knw();
    void add_result();
    void delete_result();
    void add_rule();
    void delete_rule();
    void sSlot(){
        emit sSignal();
    }
    void renew();
};

#endif // PRINT_H
