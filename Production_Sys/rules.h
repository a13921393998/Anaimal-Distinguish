#ifndef RULES_H
#define RULES_H
#include "result.h"
#include "knowledge.h"

class Rules
{
public:
    Rules();
    int rule_id;
    Result* re;
    Knowledge* knw[15];
    Knowledge* ret;
};

#endif // RULES_H
