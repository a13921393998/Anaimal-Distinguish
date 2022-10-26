#ifndef FILE_MANAGE_H
#define FILE_MANAGE_H
#include "QFile"
#include "QDataStream"
#include "QDebug"
#include "rules.h"
#include<QSql>
#include <QMessageBox>
#include<QSqlError>
#include<QSqlDatabase>
#include<QSqlQuery>
class File_Manage
{
public:
    static QString re_db_name;
    static QString regular_db_name;
    static QString knw_db_name;
    File_Manage();
    ~File_Manage();
    int getRe_num() const;
    void setRe_num(int value);
    int getRegular_num() const;
    void setRegular_num(int value);
    int getKnw_num() const;
    void setKnw_num(int value);
    Rules *getRegulars() const;
    void setRegulars(Rules *value);
    Result *getRes() const;
    void setRes(Result *value);
    Knowledge *getKnw() const;
    void setKnw(Knowledge *value);
    void Write_regulars_Inf(QStringList &temp);
    void Write_regulars_Inf();
    void Write_Re_Inf(QStringList &temp);
    void Write_Knw_Inf(QStringList &temp);
    void Read_regulars_Inf();
    void Read_Re_Inf();
    void Read_Knw_Inf();
    void Delete_regulars_Inf(int j);
    void Delete_Re_Inf(int j);
    void Delete_Knw_Inf(int j);
    QMap<int, Knowledge *> mk;
    QMap<int, Result *> mre;
    QMap<int, Rules *> mrul;
    bool OpenDatabase();
private:
    int re_num;
    int regular_num;
    int knw_num;
    Rules **regulars;
    Result **res;
    Knowledge **knw;
};

#endif // FILE_MANAGE_H
