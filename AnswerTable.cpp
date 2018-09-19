#include "AnswerTable.h"

AnswerTable::AnswerTable()
{
    Tn=0;
    tn=0;
    //ctor
}
void AnswerTable::setup(SymbolList *symbolTable,RuleList *ruleTable)
{
    BuildList(symbolTable);
    BuildTable(ruleTable);
}
///�ظm���SymbolList�Ϥ�T�Mt
void AnswerTable::BuildList(SymbolList *symbolTable)
{
    ///�ΨӽT�{���L$���s�b
    Symbol *ended;
    bool has=0;

    for(int i=0;i<symbolTable->s.size();i++)
    {
        if(symbolTable->s.at(i)->type==1)
        {
            symbolTable->s.at(i)->subid=Tn++;
            TTT.addSymbol(symbolTable->s.at(i));
        }
        else
        {
            if(symbolTable->s.at(i)->name!="$")
            {
                symbolTable->s.at(i)->subid=tn++;
                ttt.addSymbol(symbolTable->s.at(i));
            }
            else
            {
                ended = symbolTable->s.at(i);
                has=1;
            }
        }
    }
    if(has)
    {
         ended->subid=tn++;
         ttt.addSymbol(ended);
    }
    ///�����ʺA��Tn���Ъ��_�l�I
    table = new vector<int>*[Tn];
    ///�����C��Tn���ttn���ת��@���}�C
    for(int i=0;i<Tn;i++)
    {
        table[i]=new vector<int>[tn];
    }
}
bool AnswerTable::SymbolisExist(Rule *r,vector<int>*ptr)
{
    for(int i=0;i<ptr->size();i++)
    {
        if(r->id==ptr->at(i))
            return true;
    }
    return false;
}
void AnswerTable::BuildTable(RuleList *ruleTable)
{
    for(int i=1;i<ruleTable->rule.size();i++)
    {
        Rule *r = ruleTable->rule.at(i);

        for(int j=0;j<r->answer->s.size();j++)
        {

            Symbol *symbol= r->answer->s.at(j);

            vector<int>*ptr = &table[r->LHS->subid][symbol->subid];

            ///�W�@�D�_�{�T�Osymbol�S���b�̭�
            if(!SymbolisExist(r,ptr))
                table[r->LHS->subid][symbol->subid].push_back(r->id);
        }
    }
}
void AnswerTable::printTable(ostream *fp)
{
    *fp<<setw(DIS)<<""<<"|";
    for(int i=0;i<tn;i++)
    {
        *fp<<setw(DIS)<<ttt.s.at(i)->name<<"|";
    }
    *fp<<endl;
    for(int i=0;i<Tn;i++)
    {
        *fp<<setw(DIS)<<TTT.s.at(i)->name<<"|";
        for(int j=0;j<tn;j++)
        {
            if(table[i][j].size())
            {
                *fp<<setw(DIS-2*table[i][j].size())<<"";

                for(int k=0;k<table[i][j].size();k++)
                {
                    *fp<<table[i][j].at(k)<<" ";
                }
                *fp<<"|";
            }
            else
            {
                *fp<<setw(DIS)<<""<<"|";
            }
        }
        *fp<<endl;
    }
}
//�ϥΥh���W�h
///���ruletoken�X�{�����W�h��
///table[�Ѽ�1][�Ѽ�2]
Rule* AnswerTable::findRule(Symbol *ruletoken,Symbol *inputtoken,RuleList *ruletable)
{
    int a=ruletoken->subid;
    int b=inputtoken->subid;
    if(table[a][b].size()>0)
    {
        int targetid = table[a][b].at(0);
        Rule *r = ruletable->rule.at(targetid);
        return r;
    }
    else
    {
        return NULL;
    }

}
AnswerTable::~AnswerTable()
{
    //dtor
}
