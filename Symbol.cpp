#include "Symbol.h"
#include"Rule.h"
Symbol::Symbol()
{
    ///ctor
}
///�s�W�[���W�h(��ܧ@���@��symbol�X�{�brule����)
///Symbol A
///First(A) => for(i = 0...n) First(rule[i].RHS)
void Symbol::addruleL(Rule *id)
{
    ruleL.push_back(id);
    ///ruleL[ln]=id;
}
///��ܥX�{�b�W�h���k��
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

    ///L�W�h��ID��X
    cout<<"L�W�h-�X�{:";
    for(int i=0;i<ruleL.size();i++)
        cout<<ruleL.at(i)->id<<" ";
    cout<<endl;

    cout<<"R�W�h-�X�{:";
    for(int i=0;i<ruleR.size();i++)
        cout<<ruleR.at(i)->id<<" ";
    cout<<endl;
}

Symbol::~Symbol()
{
    //dtor
}
