#include "knowledge.h"

QString *Knowledge::getKnw_name() const
{
    return knw_name;
}

void Knowledge::setKnw_name(QString *value)
{
    knw_name = value;
}

Knowledge::Knowledge()
{
    knw_id = -1;
    knw_name = new QString("");
}

int Knowledge::getKnw_id() const
{
    return knw_id;
}

void Knowledge::setKnw_id(int value)
{
    knw_id = value;
}
