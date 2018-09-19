#include"Symbol.h"
#include<string>
#include<iostream>
using namespace std;


#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H

///�ΨӶi��@��CFG��symbol table���s���]�t�s�Wsymbol�M��string���symbol
///symbol���i�H���ƪ�SymbolList
class SymbolList
{
    public:
        SymbolList();
        virtual ~SymbolList();
        void addSymbol(string*);
        void addSymbol(Symbol*);
        void addSymbol(SymbolList*);

        ///symbol add rule
        void symbolAddRuleL(Symbol*,Rule*);
        void symbolAddRuleR(Symbol*,Rule*);
        void printSymbol();

        Symbol* findSymbol(string*);
        void usedFirstOff();
        void usedFollowOff();

        bool createSubSymbolListAfter(Symbol*,int*,SymbolList*);
        ///�O���ثe��symbol�ƥءA�������O���Ы��A�u��symbolTable�|���t��O�����m
        ///��l��follow��first������List�Ҭ����V
        ///n����symbollist symbol���ƶq
        vector<Symbol*>s;// *s[MAX_SYMBOL];
        bool derive;
    protected:

    private:
};

#endif // SYMBOLLIST_H
