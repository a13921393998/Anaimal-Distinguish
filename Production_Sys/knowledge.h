#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H
#include "QString"
class Knowledge
{
private:
    int knw_id;
    QString *knw_name;
public:
    Knowledge();
    int getKnw_id() const;
    void setKnw_id(int value);
    QString *getKnw_name() const;
    void setKnw_name(QString *value);
};

#endif // KNOWLEDGE_H
