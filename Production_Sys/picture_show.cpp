#include "picture_show.h"
#include "ui_picture_show.h"
#include "QCheckBox"
Picture_Show::Picture_Show(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::Picture_Show)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(sSlot()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(print_result()));
    QPixmap *p = new QPixmap("./data/OIP-C.jpg");
    p->scaled(ui->label_2->size());
    ui->label_2->setScaledContents(true);
    ui->label_2->setPixmap(*p);
    ui->tableWidget->verticalHeader()->setHidden(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

Picture_Show::~Picture_Show()
{
    delete ui;
}

void Picture_Show::get_inf(File_Manage* r){
    this->r = r;
    Sys_data = new int[r->getKnw_num()];
    for(int i=0;i<r->getKnw_num();i++){
        Sys_data[i] = 0;
    }
    for(int i=0;i<r->getKnw_num();i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int rowIdx = ui->tableWidget->rowCount()-1;
        QTableWidgetItem *item0 = new QTableWidgetItem(*(r->mk[i]->getKnw_name()));
        ui->tableWidget->setItem(rowIdx,0,item0);
        ui->tableWidget->item(rowIdx,0)->setCheckState(Qt::Unchecked);
    }
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(set_check_type(int,int)));
}
void Picture_Show::set_check_type(int a,int b){
    if(Sys_data[a]==1){
        Sys_data[a] = 0;
    }else{
        Sys_data[a] = 1;
    }
    int temp = b;
    b = temp;
//    qDebug() << a;
}

bool Picture_Show::equal(int i){
    bool l = true;
    int t = 0;
    while(r->mrul.value(i)->knw[t]->getKnw_id()!=-1){
        if(Sys_data[r->mrul.value(i)->knw[t]->getKnw_id()]!=1){
            l = false;
            break;
        }
        t++;
    }
    return l;
}

QString Picture_Show::judgement(){
    int t = 0;
    while(t>=0){
        for(int i=0;i<r->getRegular_num();i++){
            if(equal(i)==true){
                if(r->mrul.value(i)->re==nullptr&&Sys_data[r->mrul.value(i)->ret->getKnw_id()]==0){
                    Sys_data[r->mrul.value(i)->ret->getKnw_id()] = 1;
                }else if(r->mrul.value(i)->ret==nullptr){
                    return *(r->mrul.value(i)->re->getRe_name());
                }
            }
        }
        t--;
    }
    return "无匹配对象";
}

void Picture_Show::clear(){
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        ui->tableWidget->item(i,0)->setCheckState(Qt::Unchecked);
        Sys_data[i] = 0;
    }
    for(int row = ui->tableWidget->rowCount()-1;row>=0;row--){
        ui->tableWidget->removeRow(row);
    }
}

void Picture_Show::print_result(){
    QString temp = judgement();
    ui->label->setText(temp);
    QPixmap *p = new QPixmap("./data/"+temp+".jpg");
    p->scaled(ui->label_2->size());
    ui->label_2->setScaledContents(true);
    ui->label_2->setPixmap(*p);
}
