#include "print.h"
#include "ui_print.h"
#include "QInputDialog"
Print::Print(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::Print)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(sSlot()));
    connect(ui->Knw_add,SIGNAL(clicked()),this,SLOT(add_knw()));
    connect(ui->Knw_delete,SIGNAL(clicked()),this,SLOT(delete_knw()));
    connect(ui->Result_add,SIGNAL(clicked()),this,SLOT(add_result()));
    connect(ui->Result_delete,SIGNAL(clicked()),this,SLOT(delete_result()));
    connect(ui->Rule_add,SIGNAL(clicked()),this,SLOT(add_rule()));
    connect(ui->Rule_delete,SIGNAL(clicked()),this,SLOT(delete_rule()));
    connect(ui->Renew,SIGNAL(clicked()),this,SLOT(renew()));
    ui->tableWidget->verticalHeader()->setHidden(true);
    ui->tableWidget_2->verticalHeader()->setHidden(true);
    ui->tableWidget_3->verticalHeader()->setHidden(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

Print::~Print()
{
    delete ui;
}

bool Print::exist_knw(int i){
    bool temp = true;
    if(r->mk.find(i)==r->mk.end()){
        temp = false;
    }
    return temp;
}

bool Print::exist_result(int i)
{
    bool temp = true;
    if(r->mre.find(i)==r->mre.end()){
        temp = false;
    }
    return temp;
}

void Print::get_inf(File_Manage *r){
    this->r = r;
    for(auto it=r->mk.begin();it!=r->mk.end();it++){
        Knowledge *k = it.value();
        if(k->getKnw_id()==-1){
            continue;
        }
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int rowIdx = ui->tableWidget->rowCount()-1;
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(k->getKnw_id()));
        QTableWidgetItem *item1 = new QTableWidgetItem(*(k->getKnw_name()));
        ui->tableWidget->setItem(rowIdx,0,item0);
        ui->tableWidget->setItem(rowIdx,1,item1);
    }
    for(auto it=r->mre.begin();it!=r->mre.end();it++){
        Result *k = it.value();
        ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
        int rowIdx = ui->tableWidget_2->rowCount()-1;
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(k->getRe_id()));
        QTableWidgetItem *item1 = new QTableWidgetItem(*(k->getRe_name()));
        ui->tableWidget_2->setItem(rowIdx,0,item0);
        ui->tableWidget_2->setItem(rowIdx,1,item1);
    }
    for(auto it=r->mrul.begin();it!=r->mrul.end();it++){
        Rules *k = it.value();
        ui->tableWidget_3->insertRow(ui->tableWidget_3->rowCount());
        int rowIdx = ui->tableWidget_3->rowCount()-1;
        QString temp = "";
        int t = 0;
        while(1){
            if(k->knw[t]->getKnw_id()==-1){
                break;
            }
            if(temp==""){
                temp += QString::number(k->knw[t]->getKnw_id());
            }else{
                temp += ("->"+QString::number(k->knw[t]->getKnw_id()));
            }
            t++;
        }
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(k->rule_id));
        QTableWidgetItem *item1 = new QTableWidgetItem(temp);
        QTableWidgetItem *item2;
//        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(k.));
        if(k->re!=nullptr){
            item2 = new QTableWidgetItem(*(k->re->getRe_name()));
        }else{
            item2 = new QTableWidgetItem(*(k->ret->getKnw_name()));
        }
        ui->tableWidget_3->setItem(rowIdx,0,item0);
        ui->tableWidget_3->setItem(rowIdx,1,item1);
        ui->tableWidget_3->setItem(rowIdx,2,item2);
    }
//    for(int i=0;i<r->getRegular_num();i++){
//        if(r->mrul.find(i)==r->mrul.end()){
//            continue;
//        }
//        Rules *k = r->mrul[i];
//        if(k==nullptr){
//            continue;
//        }
////        qDebug() << k->getKnw_id();
//        ui->tableWidget_3->insertRow(ui->tableWidget_3->rowCount());
//        int rowIdx = ui->tableWidget_3->rowCount()-1;
//        QString temp = "";
//        int t = 0;
//        while(1){
//            if(k->knw[t]->getKnw_id()==-1){
//                break;
//            }
//            if(temp==""){
//                temp += QString::number(k->knw[t]->getKnw_id());
//            }else{
//                temp += ("->"+QString::number(k->knw[t]->getKnw_id()));
//            }
//            t++;
//        }
//        QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(k->rule_id));
//        QTableWidgetItem *item1 = new QTableWidgetItem(temp);
//        QTableWidgetItem *item2;
////        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(k.));
//        if(k->re!=nullptr){
//            item2 = new QTableWidgetItem(*(k->re->getRe_name()));
//        }else{
//            item2 = new QTableWidgetItem(*(k->ret->getKnw_name()));
//        }
//        ui->tableWidget_3->setItem(rowIdx,0,item0);
//        ui->tableWidget_3->setItem(rowIdx,1,item1);
//        ui->tableWidget_3->setItem(rowIdx,2,item2);
//    }
}


void Print::add_knw()
{
    bool bRet = false;
    QString text = QInputDialog::getMultiLineText(this,"知识增加","请输入新的知识","",&bRet);
    if(bRet&&!text.isEmpty()){
        QStringList list = text.split('\n');
        r->Write_Knw_Inf(list);
    }
}

void Print::delete_knw()
{
    bool bRet = false;
    QString text = QInputDialog::getText(this,"删除知识","请输入需要删除的知识编号:",QLineEdit::Normal,"",&bRet);
    int temp = text.toInt();
    if(bRet&&!text.isEmpty()){
        if(r->mk.find(temp)!=r->mk.end()||r->mre.find(temp)!=r->mre.end()){
            r->Delete_Knw_Inf(temp);
        }else{
            QMessageBox::critical(0,"错误信息","无法删除数据库中没有的数据",QMessageBox::Ok|QMessageBox::Default,0,0);
        }
    }
}

void Print::add_result()
{
    bool bRet = false;
    QString text = QInputDialog::getMultiLineText(this,"结果增加","请输入新的推理结果:","",&bRet);
    if(bRet&&!text.isEmpty()){
        QStringList list = text.split('\n');
        r->Write_Re_Inf(list);
    }
}

void Print::delete_result()
{
    bool bRet = false;
    QString text = QInputDialog::getText(this,"删除结果","请输入需要删除的结果编号:",QLineEdit::Normal,"",&bRet);
    int temp = text.toInt();
    if(bRet&&!text.isEmpty()){
        if(r->mre.find(temp)!=r->mre.end()){
            r->Delete_Re_Inf(text.toInt());
        }else{
            QMessageBox::critical(0,"错误信息","无法删除数据库中没有的数据",QMessageBox::Ok|QMessageBox::Default,0,0);
        }
    }
}

void Print::add_rule()
{
    bool bRet = false;
    QString text = QInputDialog::getText(this,"推理库增加","请输入新的推理过程(格式如:x,x,...,-1,x):",QLineEdit::Normal,"",&bRet);
    if(bRet&&!text.isEmpty()){
        bool temp = true;
        QStringList list = text.split(',');
        for(int i=0;i<list.size()-2;i++){
            if(!exist_knw(list[i].toInt())){
                temp = false;
            }
        }
        int tt = list[list.size()-1].toInt();
        if(tt>=10000){
            if(!exist_result(tt)){
                temp = false;
            }
        }else{
            if(!exist_knw(tt)){
                temp = false;
            }
        }
        if(temp){
            r->Write_regulars_Inf(list);
        }else{
            QMessageBox::critical(0,"错误信息","知识库中不包含推理知识",QMessageBox::Ok|QMessageBox::Default,0,0);
        }
    }
}

void Print::delete_rule()
{
    bool bRet = false;
    QString text = QInputDialog::getText(this,"规则删除","请输入需要删除的规则编号:",QLineEdit::Normal,"",&bRet);
    if(bRet&&!text.isEmpty()){
        r->Delete_regulars_Inf(text.toInt());
    }
}

void Print::clr(){
    for(int row = ui->tableWidget->rowCount()-1;row>=0;row--){
        ui->tableWidget->removeRow(row);
    }
    for(int row = ui->tableWidget_2->rowCount()-1;row >=0;row--){
        ui->tableWidget_2->removeRow(row);
    }
    for(int row = ui->tableWidget_3->rowCount()-1;row>=0;row--){
        ui->tableWidget_3->removeRow(row);
    }
}

void Print::renew(){
    r = new File_Manage();
    clr();
    get_inf(r);
    emit data_renew(r);
}

