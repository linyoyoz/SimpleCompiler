#include "SymbolList.h"

SymbolList::SymbolList()
{
    derive=1;
    //ctor
}

SymbolList::~SymbolList()
{
    //dtor
}
///給予指定id點指定它出現在哪個規則的左邊
void SymbolList ::symbolAddRuleL(Symbol *id,Rule *left)
{
    id->addruleL(left);
}
///給予指定id點指定它出現在哪個規則的右邊
void SymbolList ::symbolAddRuleR(Symbol *id,Rule *right)
{
    id->addruleR(right);
}
///主要在於一開始的token建立symbol table
void SymbolList::addSymbol(string *token)
{
    for(int i=0;i<s.size();i++)
    {
            if(*token==s[i]->name)
                return;
    }
    Symbol *f = new Symbol();
    ///f的屬性增加，因為它是新的
    f->name=*token;
    f->id=s.size();

    if(token->at(0)>='A'&&token->at(0)<='Z')
        f->type=1;
    else
        f->type=0;

    s.push_back(f);
}
///主要用做於First和Follow的類型
void SymbolList::addSymbol(Symbol *target)
{
    for(int i=0;i<s.size();i++)
    {
            ///表示已經在裡面
            if(target==s.at(i))
                return;
    }
    ///當此點沒有在List上時
    s.push_back(target);
}
///主要用做於First和Follow的類型
void SymbolList::addSymbol(SymbolList *targetList)
{
    for(int i=0;i<targetList->s.size();i++)
    {
        addSymbol(targetList->s.at(i));
    }
}
void SymbolList::printSymbol()
{
    cout<<"symbol table:"<<endl;
    for(int i=0;i<s.size();i++)
        s.at(i)->print();
}
///在這個List裡找到指定的Symbol
Symbol* SymbolList::findSymbol(string *token)
{
    for(int i=0;i<s.size();i++)
    {
        if(s.at(i)->name==*token)
            return s.at(i);
    }
    return NULL;
}
///把used的值全部歸零
void SymbolList::usedFirstOff()
{
    for(int i=0;i<s.size();i++)
        s.at(i)->used_first=0;
}
///把usedFollow的值全部歸零
void SymbolList::usedFollowOff()
{
    for(int i=0;i<s.size();i++)
        s.at(i)->used_follow=0;
}
///把在sss之後的地方做成一個symbollist並回傳
bool SymbolList::createSubSymbolListAfter(Symbol *sss,int *c,SymbolList *ans)
{
    ///開關在打開後把剩餘的symbol丟到ans裡
    bool onoff=0;
    for(int i=*c;i<this->s.size();i++)
    {
        if(onoff)
        {
            ans->addSymbol(s.at(i));
        }
        if(s.at(i)==sss&&!onoff)
        {
            onoff=1;
            *c=i+1;
            continue;
        }
    }
    return onoff;
    //return ans;
}
/*
void SymbolList::addSymbol(string *token)
{
    for(int i=0;i<Tn;i++)
    {
            if(*token==T[i].name)
                return;
    }
    if(token->at(0)>='A'&&token->at(0)<='Z')
    {

        T[Tn].name=*token;
        Tn++;
    }
    else
    {
        for(int i=0;i<tn;i++)
        {
            if(*token==t[i].name)
                return;
        }
        t[tn].name=*token;
        tn++;
    }

}
void SymbolList::printSymbol()
{
    for(int i=0;i<tn;i++)
        cout<<i<<":"<<t[i].name<<endl;
    for(int i=0;i<Tn;i++)
        cout<<i<<":"<<T[i].name<<endl;
}*/
