#include "file_manage.h"
QString File_Manage::re_db_name = "./data/re_db.dat";
QString File_Manage::regular_db_name = "./data/regular_db.dat";
QString File_Manage::knw_db_name = "./data/knw_db_name.dat";
File_Manage::File_Manage()
{
    Read_Re_Inf();
    Read_Knw_Inf();
    Read_regulars_Inf();
}
File_Manage::~File_Manage(){
//    delete regulars;
//    delete res;
//    delete knw;
}

int File_Manage::getRe_num() const
{
    return re_num;
}

void File_Manage::setRe_num(int value)
{
    re_num = value;
}

int File_Manage::getRegular_num() const
{
    return regular_num;
}

void File_Manage::setRegular_num(int value)
{
    regular_num = value;
}

Rules *File_Manage::getRegulars() const
{
    return *regulars;
}

void File_Manage::setRegulars(Rules *value)
{
    regulars = &value;
}

Result *File_Manage::getRes() const
{
    return *res;
}

void File_Manage::setRes(Result *value)
{
    res = &value;
}

Knowledge *File_Manage::getKnw() const
{
    return *knw;
}

void File_Manage::setKnw(Knowledge *value)
{
    knw = &value;
}

int File_Manage::getKnw_num() const
{
    return knw_num;
}

void File_Manage::setKnw_num(int value)
{
    knw_num = value;
}

void File_Manage::Read_regulars_Inf(){
    QFile regular_db(regular_db_name);
    regular_db.open(QIODevice::ReadOnly);
    QDataStream in(&regular_db);
    in >> regular_num;
    regulars = new Rules*[regular_num];
//    qDebug() << regular_num;
    for(int i=0;i<regular_num;i++){
        int k = 0;
        int temp;
        Rules *t1 = new Rules;
        in >> temp;
        t1->rule_id = temp;
        while(1){
            in >> temp;
            t1->knw[k] = mk.value(temp);
            k++;
            if(temp==-1){
                break;
            }
        }
        in >> temp;
        if(mre.contains(temp)){
            t1->re = mre.value(temp);
            regulars[i] = t1;
//            qDebug() << *(t1->knw[0])->getKnw_name() << " " << *(t1->re->getRe_name());
//            qDebug() << (t1->re->getRe_id());
        }else{
            t1->ret = mk.value(temp);
            regulars[i] = t1;
//            qDebug() << *(t1->knw[0])->getKnw_name() << " " << *(t1->ret->getKnw_name());
//            qDebug() << (t1->ret->getKnw_id());
        }
//        t1->rule_id = i;
        mrul.insert(t1->rule_id,t1);
    }
    regular_db.close();
}

void File_Manage::Write_regulars_Inf(){
    QFile regular_db(regular_db_name);
    regular_db.open(QIODevice::WriteOnly);
    QDataStream out(&regular_db);
    int len = regular_num;
    out << len;
    for(int i=0;i<len;i++){
        out << i;
        int t = 0;
        while(1){
            if(regulars[i]->knw[t]->getKnw_id()!=-1){
                out << regulars[i]->knw[t]->getKnw_id();
            }else{
                out << -1;
                break;
            }
            t++;
        }
        if(regulars[i]->ret!=nullptr){
            out << regulars[i]->ret->getKnw_id();
        }else{
            out << regulars[i]->re->getRe_id();
        }
    }
    regular_db.close();
}

void File_Manage::Write_regulars_Inf(QStringList &temp){
    QFile regular_db(regular_db_name);
    regular_db.open(QIODevice::WriteOnly);
    QDataStream out(&regular_db);
    int len = regular_num+1;
    out << len;
    for(int i=0;i<regular_num;i++){
        out << regulars[i]->rule_id;
        int t = 0;
        while(1){
            if(regulars[i]->knw[t]->getKnw_id()!=-1){
                out << regulars[i]->knw[t]->getKnw_id();
            }else{
                out << -1;
                break;
            }
            t++;
        }
        if(regulars[i]->ret!=nullptr){
            out << regulars[i]->ret->getKnw_id();
        }else{
            out << regulars[i]->re->getRe_id();
        }
    }
    out << regular_num;
    for(int i=0;i<temp.size()-1;i++){
        out << temp[i].toInt();
    }
    out << temp[temp.size()-1].toInt();
    regular_db.close();
}

void File_Manage::Delete_regulars_Inf(int j){
    QFile regular_db(regular_db_name);
    regular_db.open(QIODevice::WriteOnly);
    QDataStream out(&regular_db);
    int len = regular_num-1;
    out << len;
    for(auto it=mrul.begin();it!=mrul.end();it++){
        if(it.value()->rule_id==j){
            continue;
        }
        out << it.value()->rule_id;
        int t = 0;
        while(1){
            if(it.value()->knw[t]->getKnw_id()!=-1){
                out << it.value()->knw[t]->getKnw_id();
            }else{
                out << -1;
                break;
            }
            t++;
        }
        if(it.value()->ret!=nullptr){
            out << it.value()->ret->getKnw_id();
        }else{
            out << it.value()->re->getRe_id();
        }
    }
//    for(int i=0;i<regular_num;i++){
//        if(i==j){
//            continue;
//        }
//        out << regulars[i]->rule_id;
//        int t = 0;
//        while(1){
//            if(regulars[i]->knw[t]->getKnw_id()!=-1){
//                out << regulars[i]->knw[t]->getKnw_id();
//            }else{
//                out << -1;
//                break;
//            }
//            t++;
//        }
//        if(regulars[i]->ret!=nullptr){
//            out << regulars[i]->ret->getKnw_id();
//        }else{
//            out << regulars[i]->re->getRe_id();
//        }
//    }
    regular_db.close();
}

void File_Manage::Read_Re_Inf(){
    QFile re_db(re_db_name);
    re_db.open(QIODevice::ReadOnly);
    QDataStream in(&re_db);
    in >> re_num;
    res = new Result*[re_num];
    QString temp;
    int t;
//    qDebug() << re_num;
    for(int i=0;i<re_num;i++){
        in >> t;
        in >> temp;
        QString *a = new QString(temp);
        Result * b = new Result();
        b->setRe_id(t);
        b->setRe_name(a);
        res[i] = b;
//        qDebug() << res[i].getRe_id() << " " << *res[i].getRe_name();
//        qDebug() << b->getRe_id() << *(b->getRe_name());
        mre.insert(t,b);
    }
    re_db.close();
}

void File_Manage::Write_Re_Inf(QStringList &temp){
    QFile re_db(re_db_name);
    re_db.open(QIODevice::WriteOnly);
    QDataStream out(&re_db);
    int len = temp.size();
//    QString *t = temp;
//    int len = 0;
//    while(t!=nullptr){
//        len++;
//        t++;
//    }
    out << re_num+len;
//    qDebug() << re_num;
    for(int i=0;i<re_num;i++){
        out << res[i]->getRe_id();
        out << *(res[i]->getRe_name());
//        qDebug() << re[i];
    }
    for(int i=0;i<len;i++){
        out << re_num+i+10000;
        out << temp[i];
    }
    re_db.close();
}

void File_Manage::Delete_Re_Inf(int j){
    for(auto i=mrul.begin();i!=mrul.end();i++){
        if(i.value()->re!=nullptr&&i.value()->re->getRe_id()==j){
            Delete_regulars_Inf(i.value()->rule_id);
            Read_regulars_Inf();
        }
    }
    QFile re_db(re_db_name);
    re_db.open(QIODevice::WriteOnly);
    QDataStream out(&re_db);
    out << re_num-1;
//    qDebug() << re_num;
    for(auto it=mre.begin();it!=mre.end();it++){
        if(it.value()->getRe_id()==j){
            continue;
        }
        out << it.value()->getRe_id();
        out << *(it.value()->getRe_name());
    }
    re_db.close();
}

void File_Manage::Read_Knw_Inf(){
    QFile knw_db(knw_db_name);
    knw_db.open(QIODevice::ReadOnly);
    QDataStream in(&knw_db);
    in >> knw_num;
//    qDebug() << knw_num;
    knw = new Knowledge*[knw_num];
    QString t;
    int tt;
    for(int i=0;i<knw_num;i++){
        in >> tt;
        in >> t;
        QString *temp = new QString(t);
        Knowledge *b = new Knowledge();
        b->setKnw_id(tt);
        b->setKnw_name(temp);
        knw[i] = b;
        mk.insert(tt,b);
//        qDebug() << tt << *(mk[tt]->getKnw_name());
//        qDebug() << knw[i]->getKnw_id() << " " << *knw[i]->getKnw_name();
//        qDebug() << tt;
    }
    mk.insert(-1,new Knowledge());
    knw_db.close();
}

void File_Manage::Write_Knw_Inf(QStringList &temp){
//    QString temp[24] = {
//        "有毛","有奶","有羽毛","会飞","吃肉","有犬齿","会下蛋","眼盯前方",
//        "是黄褐色","有暗斑点","有黑色条纹","有长脖子","有长腿","是黑白二色","善飞","哺乳动物",
//        "有蹄动物","鸟","食肉动物","反刍动物","会游泳","不会飞","有爪子","有蹄"
//    };
    QFile knw_db(knw_db_name);
    knw_db.open(QIODevice::WriteOnly);
    QDataStream out(&knw_db);
//    QString *t = temp;
//    int len = 0;
//    while(t!=nullptr){
//        len++;
//        t++;
//    }
    int len = temp.size();
    out << len+knw_num;
    for(int i=0;i<knw_num;i++){
        out << knw[i]->getKnw_id();
        out << *(knw[i]->getKnw_name());
    }
    for(int i=0;i<len;i++){
        out << knw_num+i;
        out << temp[i];
    }
    knw_db.close();
}

void File_Manage::Delete_Knw_Inf(int j){
    for(auto i=mrul.begin();i!=mrul.end();i++){
        int t = 0;
        while(1){
            int temp = i.value()->knw[t]->getKnw_id();
            if(temp==-1){
                break;
            }
            if(temp==j){
                Delete_regulars_Inf(i.value()->rule_id);
                Read_regulars_Inf();
            }
            t++;
        }
        if(i.value()->ret!=nullptr&&i.value()->ret->getKnw_id()==j){
            Delete_regulars_Inf(i.value()->rule_id);
            Read_regulars_Inf();
        }
    }
    QFile knw_db(knw_db_name);
    knw_db.open(QIODevice::WriteOnly);
    QDataStream out(&knw_db);
    out << knw_num-1;
    for(auto it=mk.begin();it!=mk.end();it++){
        if(it.value()->getKnw_id()==j||it.value()->getKnw_id()==-1){
            continue;
        }
        out << it.value()->getKnw_id();
        out << *(it.value()->getKnw_name());
    }
//    for(int i=0;i<knw_num;i++){
//        if(i==j){
//            continue;
//        }
//        out << knw[i]->getKnw_id();
//        out << *(knw[i]->getKnw_name());
//    }
    knw_db.close();
//    Read_Knw_Inf();
}

bool File_Manage::OpenDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
    qDebug()<<"ODBC driver?"<<db.isValid();
    QString dsn = QString::fromLocal8Bit("Production_Sys");      //数据源名称
    db.setHostName("Production_sys");                        //选择本地主机，127.0.0.1
    db.setDatabaseName(dsn);                            //设置数据源名称
    db.setUserName("Production_Sys");                               //登录用户
    db.setPassword("123456");                              //密码
//    qDebug() << db.open();
    if(!db.open())                                      //打开数据库
    {
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
        return false;                                   //打开失败
    }
    else
    {
        qDebug()<<"database open success!";
        QSqlQuery query(db); //查询Card表并输出，测试能否正常操作数据库
        query.exec("SELECT * FROM Knw");
        while(query.next()){
            qDebug()<<query.value(0).toInt() <<query.value(1).toString();
        }
    }
    return true;
}
