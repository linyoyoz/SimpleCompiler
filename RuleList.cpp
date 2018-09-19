#include "RuleList.h"

RuleList::RuleList()
{
    //ctor
    Rule *p = new Rule();
    rule.push_back(p);

}
void RuleList::addRule(Rule *r)
{
    rule.push_back(r);

}
void RuleList::printRule()
{
    ///顯示rule
    for(int i=1;i<rule.size();i++)
        rule.at(i)->print();
}

///Follow(A) A = rrr->LHS
/// = Symbol A -> all in rule right
void RuleList::Follow(SymbolList *SymbolTable,Rule *rrr)
{
    ///初始化used
    SymbolTable->usedFollowOff();
    ///使所有的First偵測器歸零利於計算之後的結果
    SymbolTable->usedFirstOff();

    rrr->follow=FollowDFS(rrr->LHS);
}
SymbolList* RuleList::FollowDFS(Symbol *LHS)
{
    ///Follow(A)-> A= LHS
    SymbolList *ans = new SymbolList();

    ///當重複找過時回傳
    if(LHS->used_follow)
    {
        return ans;
    }
    ///這個規則的LHS的follow已經used了
    LHS->used_follow=1;

    ///兩個List記錄深入First和Follow之後的結果
    SymbolList *tempList,*temp2List;

    ///從LHS 出現在右邊規則的[0...n]
    for(int i=0;i< LHS->ruleR.size();i++)
    {
        ///一個可重複的symbolList記錄A(LHS) 之後的Symbol List
        SymbolCommonList *subSymbolList = new SymbolCommonList();
        ///一個位置用來記錄一個規則裡(在指定LHS之後的位置)
        int c=0;
        ///找到A出現的rule並一一列舉
        Rule *target_rule = LHS->ruleR.at(i);

        ///找到位於LHS這個symbol之後的symbol並組成List
        ///回傳給subSymbolList 以給它作First(subSymbolList)
        while(target_rule->RHS.createSubSymbolListAfter(LHS,&c,subSymbolList))
        {

            ///subSymbolList->printSymbol();
            ///去找List深度跑完的結果
            tempList = FirstDFS(subSymbolList);

            ///表示有路徑仍未找到必須在follow(target_rule的LHS)
            if(tempList->derive==1)
            {
                temp2List=FollowDFS(target_rule->LHS);
                tempList->addSymbol(temp2List);
            }
            ans->addSymbol(tempList);

            ///subSymbolList的刪除與重置
            subSymbolList->~SymbolCommonList();
            subSymbolList = new SymbolCommonList();
        }
    }
    return ans;
}
///First(XXXXXX) XXX = rrr->RHS
void RuleList::First(SymbolList *SymbolTable,Rule *rrr)
{
    ///初始化used
    SymbolTable->usedFirstOff();

    ///這個規則的LHS First已經used了
    rrr->LHS->used_first=1;

    ///深度去尋找First(rrr的RHS)
    ///並給與rrr的first 在深度找到的結果
    rrr->first = FirstDFS(&rrr->RHS);
}
///回傳有三種可能性
///1.在找RHS的過程中直接找到terminal直接回傳
///2.在深度的過程中，某個non-terminal所有路徑皆可接到terminal直接回傳
///3.在深度的過程中，找到所有RHS symbol還是有路徑沒辦法找到terminal
///或是規則本身就沒有symbollist 需要derive 與 follow
SymbolList* RuleList::FirstDFS(SymbolList *RHS)
{

    ///First(X) X=this rule RHS
    ///表示找到的不可重複的List First(A)的ans
    SymbolList*ans=new SymbolList();
    ///依照RHS去一個個symbol找
    for(int i=0;i<RHS->s.size();i++)
    {
        ///找到指定的目標RHS symbol
        Symbol *target = RHS->s.at(i);

        ///初始假設為0那樣假如下面有找的變直接傳回
        ans->derive=0;
        ///表示為一般的terminal，直接回傳便是答案
        if(target->type==0)
        {
            ans->addSymbol(target);
            ans->derive=0;
            return ans;
        }
        else///表示為non-terminal，需要深入去找First(T)的話，必須找T出現在規則左邊
        {
            ///防止無限迴圈
            if(target->used_first==1)///表示已經找到重複的First(symbol)直接回傳
            {
                continue;
            }
            target->used_first=1;///表示這個symbol已經使用過了

            for(int i=0;i<target->ruleL.size();i++)///此symbol出現在左邊的rule
            {
                ///找到第target出現在左邊的規則rdown
                ///由它的RHS再深入找到rdown的規則
                Rule *rdown=target->ruleL.at(i);
                SymbolList *temp;
                temp = FirstDFS(&rdown->RHS);

                ///去添加找到的temp使F(ABa)=F(A)U F(Ba)
                ans->addSymbol(temp);

                ///當某個temp回傳1表示某條路徑找不到
                ///導致ans必須為1
                if(temp->derive==1)
                    ans->derive=1;
            }
            ///表示其深度搜索後的每條路徑皆不需要derive
            if(ans->derive==0)
                return ans;
        }
    }
    ///表示此點找不到symbol所以ans為1
    if(ans->s.size()==0)
        ans->derive=1;
    return ans;
}

RuleList::~RuleList()
{
    //dtor
}
