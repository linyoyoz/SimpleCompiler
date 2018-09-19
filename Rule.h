#include"Symbol.h"
#include"SymbolCommonList.h"
#include<string>
#include<iostream>


using namespace std;

#ifndef RULE_H
#define RULE_H


///�O���@�ӳW�h
class Rule
{
    public:
        Rule();
        virtual ~Rule();
        //�bL�W��T��id
        ///XX>A B C
        //LHS:XX
        //RHS:A B C
        void addLHS(Symbol*);
        void addRHS(Symbol*);
        void print();
        void Fprint();
        void Aprint();

        ///�O���o�ӳW�h��LHS symbol�MRHS��symbol
        Symbol *LHS;
        SymbolCommonList RHS;

        ///�O���o�ӳW�h��쪺First(RHS)�H��Follow(LHS)
        SymbolList *first;
        SymbolList *follow;
        SymbolList *answer;

        int id;
    protected:

    private:
};

#endif // RULE_H
