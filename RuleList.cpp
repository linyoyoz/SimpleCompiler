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
    ///���rule
    for(int i=1;i<rule.size();i++)
        rule.at(i)->print();
}

///Follow(A) A = rrr->LHS
/// = Symbol A -> all in rule right
void RuleList::Follow(SymbolList *SymbolTable,Rule *rrr)
{
    ///��l��used
    SymbolTable->usedFollowOff();
    ///�ϩҦ���First�������k�s�Q��p�⤧�᪺���G
    SymbolTable->usedFirstOff();

    rrr->follow=FollowDFS(rrr->LHS);
}
SymbolList* RuleList::FollowDFS(Symbol *LHS)
{
    ///Follow(A)-> A= LHS
    SymbolList *ans = new SymbolList();

    ///���Ƨ�L�ɦ^��
    if(LHS->used_follow)
    {
        return ans;
    }
    ///�o�ӳW�h��LHS��follow�w�gused�F
    LHS->used_follow=1;

    ///���List�O���`�JFirst�MFollow���᪺���G
    SymbolList *tempList,*temp2List;

    ///�qLHS �X�{�b�k��W�h��[0...n]
    for(int i=0;i< LHS->ruleR.size();i++)
    {
        ///�@�ӥi���ƪ�symbolList�O��A(LHS) ���᪺Symbol List
        SymbolCommonList *subSymbolList = new SymbolCommonList();
        ///�@�Ӧ�m�ΨӰO���@�ӳW�h��(�b���wLHS���᪺��m)
        int c=0;
        ///���A�X�{��rule�ä@�@�C�|
        Rule *target_rule = LHS->ruleR.at(i);

        ///�����LHS�o��symbol���᪺symbol�òզ�List
        ///�^�ǵ�subSymbolList �H�����@First(subSymbolList)
        while(target_rule->RHS.createSubSymbolListAfter(LHS,&c,subSymbolList))
        {

            ///subSymbolList->printSymbol();
            ///�h��List�`�׶]�������G
            tempList = FirstDFS(subSymbolList);

            ///��ܦ����|������쥲���bfollow(target_rule��LHS)
            if(tempList->derive==1)
            {
                temp2List=FollowDFS(target_rule->LHS);
                tempList->addSymbol(temp2List);
            }
            ans->addSymbol(tempList);

            ///subSymbolList���R���P���m
            subSymbolList->~SymbolCommonList();
            subSymbolList = new SymbolCommonList();
        }
    }
    return ans;
}
///First(XXXXXX) XXX = rrr->RHS
void RuleList::First(SymbolList *SymbolTable,Rule *rrr)
{
    ///��l��used
    SymbolTable->usedFirstOff();

    ///�o�ӳW�h��LHS First�w�gused�F
    rrr->LHS->used_first=1;

    ///�`�ץh�M��First(rrr��RHS)
    ///�õ��Prrr��first �b�`�ק�쪺���G
    rrr->first = FirstDFS(&rrr->RHS);
}
///�^�Ǧ��T�إi���
///1.�b��RHS���L�{���������terminal�����^��
///2.�b�`�ת��L�{���A�Y��non-terminal�Ҧ����|�ҥi����terminal�����^��
///3.�b�`�ת��L�{���A���Ҧ�RHS symbol�٬O�����|�S��k���terminal
///�άO�W�h�����N�S��symbollist �ݭnderive �P follow
SymbolList* RuleList::FirstDFS(SymbolList *RHS)
{

    ///First(X) X=this rule RHS
    ///��ܧ�쪺���i���ƪ�List First(A)��ans
    SymbolList*ans=new SymbolList();
    ///�̷�RHS�h�@�ӭ�symbol��
    for(int i=0;i<RHS->s.size();i++)
    {
        ///�����w���ؼ�RHS symbol
        Symbol *target = RHS->s.at(i);

        ///��l���]��0���˰��p�U�����䪺�ܪ����Ǧ^
        ans->derive=0;
        ///��ܬ��@�몺terminal�A�����^�ǫK�O����
        if(target->type==0)
        {
            ans->addSymbol(target);
            ans->derive=0;
            return ans;
        }
        else///��ܬ�non-terminal�A�ݭn�`�J�h��First(T)���ܡA������T�X�{�b�W�h����
        {
            ///����L���j��
            if(target->used_first==1)///��ܤw�g��쭫�ƪ�First(symbol)�����^��
            {
                continue;
            }
            target->used_first=1;///��ܳo��symbol�w�g�ϥιL�F

            for(int i=0;i<target->ruleL.size();i++)///��symbol�X�{�b���䪺rule
            {
                ///����target�X�{�b���䪺�W�hrdown
                ///�ѥ���RHS�A�`�J���rdown���W�h
                Rule *rdown=target->ruleL.at(i);
                SymbolList *temp;
                temp = FirstDFS(&rdown->RHS);

                ///�h�K�[��쪺temp��F(ABa)=F(A)U F(Ba)
                ans->addSymbol(temp);

                ///��Y��temp�^��1��ܬY�����|�䤣��
                ///�ɭPans������1
                if(temp->derive==1)
                    ans->derive=1;
            }
            ///��ܨ�`�׷j���᪺�C�����|�Ҥ��ݭnderive
            if(ans->derive==0)
                return ans;
        }
    }
    ///��ܦ��I�䤣��symbol�ҥHans��1
    if(ans->s.size()==0)
        ans->derive=1;
    return ans;
}

RuleList::~RuleList()
{
    //dtor
}
