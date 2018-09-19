#include "Rule.h"

Rule::Rule()
{

}
void Rule::addLHS(Symbol *id)
{
    LHS=id;
}
void Rule::addRHS(Symbol *id)
{
    RHS.addSymbol(id);
}
void Rule::print()
{
    cout<<id<<":"<<endl;
    cout<<"LHS:"<<LHS->name<<endl;
    cout<<"RHS:";
    for(int i=0;i<RHS.s.size();i++)
        cout<<RHS.s.at(i)->name<<" ";//<<"|"<<RHS[i]<<"| ";
    cout<<endl;
}
///print First and Follow
void Rule::Fprint()
{

    for(int i=0;i<first->s.size();i++)
        cout<<first->s.at(i)->name<<" ";
    if(first->derive)
    {
        cout<<"yes";
        for(int i=0;i<follow->s.size();i++)
            cout<<follow->s.at(i)->name<<" ";
    }
    else
        cout<<"no";
    cout<<endl;
}
void Rule::Aprint()
{
    cout<<id<<":";
    for(int i=0;i<answer->s.size();i++)
        cout<<answer->s.at(i)->name<<" ";
    cout<<endl;
}
Rule::~Rule()
{
    //dtor
}
