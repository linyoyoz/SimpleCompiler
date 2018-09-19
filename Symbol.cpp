#include "Symbol.h"
#include"Rule.h"
Symbol::Symbol()
{
    ///ctor
}
///新增加左規則(表示作為一個symbol出現在rule左邊)
///Symbol A
///First(A) => for(i = 0...n) First(rule[i].RHS)
void Symbol::addruleL(Rule *id)
{
    ruleL.push_back(id);
    ///ruleL[ln]=id;
}
///表示出現在規則的右邊
///Symbol A
///Follow(A) => for(i = 0...n) First(After A SymbolList)
void Symbol::addruleR(Rule *id)
{
    ruleR.push_back(id);
}
/*Symbol::setType(string *token)
{
    if(token->at(0)>='a'&&token->at(0)<='z')
    {
        this->type=0;
    }
    else
    {
        this->type=1;
    }
}*/
void Symbol::print()
{
    if(type)
        cout<<id<<"(T):"<<name<<" "<<endl;
    else
        cout<<id<<"(t):"<<name<<" "<<endl;

    ///L規則的ID輸出
    cout<<"L規則-出現:";
    for(int i=0;i<ruleL.size();i++)
        cout<<ruleL.at(i)->id<<" ";
    cout<<endl;

    cout<<"R規則-出現:";
    for(int i=0;i<ruleR.size();i++)
        cout<<ruleR.at(i)->id<<" ";
    cout<<endl;
}

Symbol::~Symbol()
{
    //dtor
}
