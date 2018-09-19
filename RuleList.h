#include"Symbol.h"
#include"SymbolCommonList.h"
#include"Rule.h"
#ifndef RULELIST_H
#define RULELIST_H


class RuleList
{
    public:
        RuleList();
        virtual ~RuleList();

        void addRule(Rule*);
        void printRule();
        SymbolList* FirstDFS(SymbolList*);
        void First(SymbolList*,Rule*);

        SymbolList* FollowDFS(Symbol*);
        void Follow(SymbolList*,Rule*);
        void findAns(Rule*);

        vector<Rule*>rule;//[MAX_RULE];
        ///rule.size()¬°n+1


    protected:

    private:
};

#endif // RULELIST_H
