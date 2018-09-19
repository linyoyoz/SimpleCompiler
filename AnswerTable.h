#include"SymbolCommonList.h"
#include"RuleList.h"
#include<fstream>
#include <iomanip>
using namespace std;
#ifndef ANSWERTABLE_H
#define ANSWERTABLE_H
#define DIS 8

///建出結果的table
class AnswerTable
{
    public:
        AnswerTable();
        virtual ~AnswerTable();

        void BuildList(SymbolList*);
        bool SymbolisExist(Rule*,vector<int>*);

        void BuildTable(RuleList*);
        void printTable(ostream*);
        void setup(SymbolList*,RuleList*);
        Rule* findRule(Symbol*,Symbol*,RuleList*);
    ///§äTTT©Mtttªº¤º®e
    int Tn;
    int tn;
    SymbolList TTT,ttt;

    vector<int>**table;

    protected:

    private:
};

#endif // ANSWERTABLE_H
