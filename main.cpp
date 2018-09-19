#include"Symbol.h"
#include"SymbolList.h"
#include"Rule.h"
#include"RuleList.h"
#include"AnswerTable.h"
#include"Snow.h"
#include <iostream>
//���io�ɮפ������B�z
#include<fstream>
//���string��J�������B�z
#include<sstream>
#include<map>
#include<string>
#include<stack>
#include<queue>
#define MAX 500
using namespace std;
/*
���P��J�a�J�Ѽ�
*/
SymbolList symbolTable;
RuleList ruleTable;
AnswerTable answertable;
queue<Symbol*>inputtoken;
stack<Symbol*>ruletoken;
///Snow snow;
///��X�ɮ�
fstream fp;

///��J�ɮ�
ifstream fin;

///Rule r[MAX];
///int rn=0;

/// fp ��X�ɮץ�::ostream
/// finŪ���ɮץ�::istream
/// ostringstream ��Xstring��::ostream
/// istringstream Ū��string��::istream

///�ثe�@���ɮץu�䴩��J�@��CFG
bool input(/*int argc,char *argv[],int mode,int number*/)
{
    int miss=0;
    /*
    ///�}���ɮ�
    if(mode)
    {
        fin.open(argv[1]);
        if(!fin.is_open())
            cout<<"�䤣���ɮ�"<<endl;
    }
    else
    {
        ostringstream line;
        if(number!=1)
            line<<"input"<<number<<".txt";
        else
            line<<"input.txt";
        string x=line.str();

        fin.open(x.c_str());
    }

    */
    ///�@���J���O��
    string line_string;

    ///�ƥ��h�ӦP��LHS�W�h��symbol
    Symbol *LHS=NULL;
    ///�@��token���O��
    string token;

    //��fin����J�@��
    //Ū���@��
    while(getline(fin,line_string))
    {

        //cout<<line_string<<endl;

        //�����b����
        istringstream line;
        line.str(line_string);

        //�W�h
        Rule *rule = new Rule();
        rule->id=ruleTable.rule.size();
        ruleTable.addRule(rule);

        //�ΨӰ��C�Ӥ��P�r��������
        bool first=1,second=0,middle=0;
        /*
        ��istringstream �� line�H�Ů���Ψ�token
        Ū���@��token
        */
        while(getline(line,token,' '))
        {
            cout<<token<<" ";
            if(token=="lamda")
            {

            }
            else if(first==1)//�Ĥ@���O�Ʀr�������L
            {
                first=0;
                second=1;
            }
            else if(second==1)//�ĤG���|��|�άOT��إi���
            {
                second=0;
                if(token=="|")
                {
                    if(LHS==NULL)
                    {
                        cout<<"���~��CFG�A�Ĥ@�椣�i�H�S��LHS"<<endl;
                        miss=1;
                    }
                    else
                    {
                        ///���PLHS���s��
                        rule->addLHS(LHS);
                        ///�������wid��symbol�K�[���W�h
                        ///LHS�O�����O�W�@���X�{����symbol
                        ///��o�̪�ܨ䬰�o�ӳW�h��LHS
                        symbolTable.symbolAddRuleL(LHS,rule);

                        continue;
                    }
                }
                else
                {
                    if(token.at(0)>'Z'||token.at(0)<'A')
                    {
                        cout<<"���~��CFG�ALHS�������j�g�}�Y"<<endl;
                        miss=1;
                    }

                    ///��LHS token��Jtable
                    symbolTable.addSymbol(&token);
                    Symbol *symbol=symbolTable.findSymbol(&token);
                    LHS=symbol;

                    ///���PLHS���s��
                    rule->addLHS(symbol);
                    ///�������wid��symbol�K�[���W�h
                    symbolTable.symbolAddRuleL(symbol,rule);

                    middle=1;//�o�U�@�ӷ|�O�ಾ�I
                }
            }
            else if(middle==1)//�����ഫ��>
            {
                middle=0;
                continue;
            }
            else///�������k�϶�
            {
                ///��RHS token��Jtable
                symbolTable.addSymbol(&token);
                Symbol *symbol=symbolTable.findSymbol(&token);
                ///���PRHS���s��
                rule->addRHS(symbol);
                ///�������wid��symbol�K�[�k�W�h
                symbolTable.symbolAddRuleR(symbol,rule);
            }
        }
        cout<<endl;
    }
    string ed="$";
    if(symbolTable.findSymbol(&ed)==NULL)
    {
        cout<<"CFG���䤣��వ��������symbol $"<<endl;
         miss=1;
    }

    return !miss;
    //cout<<list.number;
    //symbolTable.printSymbol();
    //ruleTable.printRule();
}
void FollowAll()
{
    for(int i=1;i<ruleTable.rule.size();i++)
    {
       Rule *f = ruleTable.rule.at(i);
       if(f->first->derive)
       {
           ruleTable.Follow(&symbolTable,f);
       }
       //f->Fprint();
    }
}
void FirstAll()
{
    for(int i=1;i<ruleTable.rule.size();i++)
    {
        Rule *f = ruleTable.rule.at(i);
        ruleTable.First(&symbolTable,f);
    }
}
void AnsAll()
{
    for(int i=1;i<ruleTable.rule.size();i++)
    {
        Rule *f = ruleTable.rule.at(i);
        f->answer = new SymbolList();
        f->answer->addSymbol(f->first);
        if(f->first->derive)
            f->answer->addSymbol(f->follow);
        //-------------------------------------testPRINT------------------------
        f->Fprint();
    }
}
void setupTable()
{
    FirstAll();
    FollowAll();
    AnsAll();
}
void init()
{
    symbolTable=SymbolList();
    ruleTable=RuleList();
    answertable = AnswerTable();
    //snow =Snow();
}

///��Xstack
void Stackprint(stack<Symbol*> *p)
{
    ostringstream line;
    line<<"Rule:";
    stack<Symbol*>*pp = new stack<Symbol*>();
    while(!p->empty())
    {
        pp->push(p->top());
        line<<p->top()->name<<" ";
        p->pop();
    }
    while(!pp->empty())
    {
        p->push(pp->top());
        pp->pop();
    }
    ///�a����X25��
    cout<<setw(25)<<left<<line.str();
}
///��Xqueue
void Queueprint(queue<Symbol*> *q)
{
    cout<<"Input:";
    queue<Symbol*>*qq = new queue<Symbol*>();
    while(!q->empty())
    {
        qq->push(q->front());
        cout<<q->front()->name<<" ";
        q->pop();
    }
    while(!qq->empty())
    {
        q->push(qq->front());
        qq->pop();
    }
    cout<<endl;
}
void LL()
{
    ostringstream ansoutput;

    ruletoken.push(ruleTable.rule.at(1)->LHS);
    bool accept=0;
    int x;
    while(!accept)
    {
        //cin>>x;
        if(ruletoken.empty()||inputtoken.empty())
        {
            ansoutput<<"Error:�榡���~"<<endl;
            break;
        }
        else
        {
            Stackprint(&ruletoken);
            Queueprint(&inputtoken);
        }
        if(ruletoken.top()->type==0)
        {
            if(ruletoken.top()==inputtoken.front())
            {
                ///���Ӧr��ҿ�J���åB�Ҭ�$
                if(ruletoken.top()->name=="$"&&ruletoken.size()==1&&inputtoken.size()==1)
                {
                    accept=1;
                    ansoutput<<"Accept"<<endl;
                    break;
                }
                ruletoken.pop();
                inputtoken.pop();
            }
            else
            {
                ansoutput<<"Error:���X�W�h"<<ruletoken.top()->name<<"�P"<<inputtoken.front()->name<<"���۵�"<<endl;
                break;
            }
        }
        else
        {
            Rule *r = answertable.findRule(ruletoken.top(),inputtoken.front(),&ruleTable);
            if(r!=NULL)
            {
                ansoutput<<r->id<<" ";
                ruletoken.pop();
                for(int i=r->RHS.s.size()-1;i>=0;i--)
                {
                    ruletoken.push(r->RHS.s.at(i));
                }
            }
            else
            {
                ansoutput<<"Error:�䤣��W�h��"<<ruletoken.top()->name<<"��ɥX"<<inputtoken.front()->name<<endl;
                break;
            }
        }
    }
    cout<<ansoutput.str()<<endl;
}
bool inputString(istream *input)
{
    string data;
    string line_string;
    while(getline(*input,line_string))
    {
        if(line_string=="exit()")
            break;
        ///input����Ƶ��c��l��
        inputtoken=queue<Symbol*>();
        ruletoken=stack<Symbol*>();
        ///
        ///
        ///���ο�J���
        istringstream line;
        line.str(line_string);
         while(getline(line,data,' '))
         {
            cout<<data<<" ";
            Symbol *symbol = symbolTable.findSymbol(&data);
            if(symbol!=NULL)
                inputtoken.push(symbol);
            else
            {
                cout<<"���s�b��token��J"<<endl;
                return false;
            }
         }
         cout<<endl;
         LL();
    }
    ///( v + f ( v ) ) $
}
bool ScannerMode()
{
    string a;
    while(1)
    {
        cout<<"��J0��ʿ�Jinput  ��J1�ɮ׿�J ��J��L���}"<<endl;
        cout<<"��J�Ʀr:";
        cin>>a;
        getchar();
        if(a=="0")
        {
            cout<<"��ʿ�J�Ҧ��A��Jexit()���}"<<endl;
            inputString(&cin);
        }

        else if(a=="1")
        {
            ifstream fin;

            cout<<"��J�ɮצW��:";
            string FileName;
            cin>>FileName;
            getchar();

            fin.open(FileName.c_str());
            if(fin.is_open())
                    inputString(&fin);
            else
                cout<<"�䤣���ɮ�"<<endl;
        }
        else
            break;
    }
}
//����}�Ҫ�CFG�ɮ�
void ControlMode()
{
    fp.open("out.txt", ios::out);
    string FileName;

    while(1)
    {
        cout<<"��J�n�}�Ҫ�CFG�ɮצW��:";
        cin>>FileName;

        getchar();
        fin.open(FileName.c_str());
        if(fin.is_open())
        {
            init();
            if(input())
            {
                setupTable();
                answertable.setup(&symbolTable,&ruleTable);
                answertable.printTable(&cout);
                ScannerMode();
            }

        }
        else
            cout<<"�䤣���ɮ�"<<endl;
        fin.close();
    }
}
int main(int argc,char *argv[])
{
    ControlMode();
    return 0;
}
