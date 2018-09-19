#include"Symbol.h"
#include<string>
#include<iostream>
using namespace std;


#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H

///用來進行一個CFG的symbol table的存取包含新增symbol和用string找到symbol
///symbol不可以重複的SymbolList
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
        ///記錄目前的symbol數目，全部都是指標型態只有symbolTable會分配到記憶體位置
        ///其餘的follow或first類型的List皆為指向
        ///n為此symbollist symbol的數量
        vector<Symbol*>s;// *s[MAX_SYMBOL];
        bool derive;
    protected:

    private:
};

#endif // SYMBOLLIST_H
