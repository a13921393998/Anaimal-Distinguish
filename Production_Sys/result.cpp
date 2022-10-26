#include "result.h"

int Result::getRe_id() const
{
    return re_id;
}

void Result::setRe_id(int value)
{
    re_id = value;
}

QString *Result::getRe_name() const
{
    return re_name;
}

void Result::setRe_name(QString *value)
{
    re_name = value;
}

Result::Result()
{
    re_id = -1;
    re_name = new QString("");
}
