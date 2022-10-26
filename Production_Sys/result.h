#ifndef RESULT_H
#define RESULT_H
#include "QString"
class Result
{
private:
    int re_id;
    QString *re_name;
public:
    Result();
    int getRe_id() const;
    void setRe_id(int value);
    QString *getRe_name() const;
    void setRe_name(QString *value);
};

#endif // RESULT_H
