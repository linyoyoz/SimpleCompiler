#include"Symbol.h"
#include"SymbolList.h"
#include"Rule.h"
#include"RuleList.h"
#include"AnswerTable.h"
#include"Snow.h"
#include <iostream>
//對於io檔案之間的處理
#include<fstream>
//對於string輸入之間的處理
#include<sstream>
#include<map>
#include<string>
#include<stack>
#include<queue>
#define MAX 500
using namespace std;
/*
給與輸入帶入參數
*/
SymbolList symbolTable;
RuleList ruleTable;
AnswerTable answertable;
queue<Symbol*>inputtoken;
stack<Symbol*>ruletoken;
///Snow snow;
///輸出檔案
fstream fp;

///輸入檔案
ifstream fin;

///Rule r[MAX];
///int rn=0;

/// fp 輸出檔案用::ostream
/// fin讀取檔案用::istream
/// ostringstream 輸出string用::ostream
/// istringstream 讀取string用::istream

///目前一個檔案只支援輸入一個CFG
bool input(/*int argc,char *argv[],int mode,int number*/)
{
    int miss=0;
    /*
    ///開啟檔案
    if(mode)
    {
        fin.open(argv[1]);
        if(!fin.is_open())
            cout<<"找不到檔案"<<endl;
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
    ///一行輸入的記錄
    string line_string;

    ///備份多個同樣LHS規則的symbol
    Symbol *LHS=NULL;
    ///一個token的記錄
    string token;

    //讓fin的輸入一行
    //讀取一行
    while(getline(fin,line_string))
    {

        //cout<<line_string<<endl;

        //內部在切割
        istringstream line;
        line.str(line_string);

        //規則
        Rule *rule = new Rule();
        rule->id=ruleTable.rule.size();
        ruleTable.addRule(rule);

        //用來做每個不同字元的分割
        bool first=1,second=0,middle=0;
        /*
        讓istringstream 的 line以空格切割到token
        讀取一個token
        */
        while(getline(line,token,' '))
        {
            cout<<token<<" ";
            if(token=="lamda")
            {

            }
            else if(first==1)//第一次是數字必須略過
            {
                first=0;
                second=1;
            }
            else if(second==1)//第二次會有|或是T兩種可能性
            {
                second=0;
                if(token=="|")
                {
                    if(LHS==NULL)
                    {
                        cout<<"錯誤的CFG，第一行不可以沒有LHS"<<endl;
                        miss=1;
                    }
                    else
                    {
                        ///給與LHS的連接
                        rule->addLHS(LHS);
                        ///給予指定id的symbol添加左規則
                        ///LHS記錄的是上一次出現的左symbol
                        ///到這裡表示其為這個規則的LHS
                        symbolTable.symbolAddRuleL(LHS,rule);

                        continue;
                    }
                }
                else
                {
                    if(token.at(0)>'Z'||token.at(0)<'A')
                    {
                        cout<<"錯誤的CFG，LHS必須為大寫開頭"<<endl;
                        miss=1;
                    }

                    ///把LHS token放入table
                    symbolTable.addSymbol(&token);
                    Symbol *symbol=symbolTable.findSymbol(&token);
                    LHS=symbol;

                    ///給與LHS的連接
                    rule->addLHS(symbol);
                    ///給予指定id的symbol添加左規則
                    symbolTable.symbolAddRuleL(symbol,rule);

                    middle=1;//她下一個會是轉移點
                }
            }
            else if(middle==1)//中間轉換的>
            {
                middle=0;
                continue;
            }
            else///此必為右區間
            {
                ///把RHS token放入table
                symbolTable.addSymbol(&token);
                Symbol *symbol=symbolTable.findSymbol(&token);
                ///給與RHS的連接
                rule->addRHS(symbol);
                ///給予指定id的symbol添加右規則
                symbolTable.symbolAddRuleR(symbol,rule);
            }
        }
        cout<<endl;
    }
    string ed="$";
    if(symbolTable.findSymbol(&ed)==NULL)
    {
        cout<<"CFG內找不到能做為結尾的symbol $"<<endl;
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

///輸出stack
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
    ///靠左輸出25格
    cout<<setw(25)<<left<<line.str();
}
///輸出queue
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
            ansoutput<<"Error:格式錯誤"<<endl;
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
                ///當兩個字串皆輸入完並且皆為$
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
                ansoutput<<"Error:不合規則"<<ruletoken.top()->name<<"與"<<inputtoken.front()->name<<"不相等"<<endl;
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
                ansoutput<<"Error:找不到規則使"<<ruletoken.top()->name<<"能導出"<<inputtoken.front()->name<<endl;
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
        ///input的資料結構初始化
        inputtoken=queue<Symbol*>();
        ruletoken=stack<Symbol*>();
        ///
        ///
        ///切割輸入資料
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
                cout<<"不存在的token輸入"<<endl;
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
        cout<<"輸入0手動輸入input  輸入1檔案輸入 輸入其他離開"<<endl;
        cout<<"輸入數字:";
        cin>>a;
        getchar();
        if(a=="0")
        {
            cout<<"手動輸入模式，輸入exit()離開"<<endl;
            inputString(&cin);
        }

        else if(a=="1")
        {
            ifstream fin;

            cout<<"輸入檔案名稱:";
            string FileName;
            cin>>FileName;
            getchar();

            fin.open(FileName.c_str());
            if(fin.is_open())
                    inputString(&fin);
            else
                cout<<"找不到檔案"<<endl;
        }
        else
            break;
    }
}
//控制開啟的CFG檔案
void ControlMode()
{
    fp.open("out.txt", ios::out);
    string FileName;

    while(1)
    {
        cout<<"輸入要開啟的CFG檔案名稱:";
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
            cout<<"找不到檔案"<<endl;
        fin.close();
    }
}
int main(int argc,char *argv[])
{
    ControlMode();
    return 0;
}
