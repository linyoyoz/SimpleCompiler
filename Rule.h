#include"Symbol.h"
#include"SymbolCommonList.h"
#include<string>
#include<iostream>


using namespace std;

#ifndef RULE_H
#define RULE_H


///記錄一個規則
class Rule
{
    public:
        Rule();
        virtual ~Rule();
        //在L上的T的id
        ///XX>A B C
        //LHS:XX
        //RHS:A B C
        void addLHS(Symbol*);
        void addRHS(Symbol*);
        void print();
        void Fprint();
        void Aprint();

        ///記錄這個規則的LHS symbol和RHS的symbol
        Symbol *LHS;
        SymbolCommonList RHS;

        ///記錄這個規則找到的First(RHS)以及Follow(LHS)
        SymbolList *first;
        SymbolList *follow;
        SymbolList *answer;

        int id;
    protected:

    private:
};

#endif // RULE_H
