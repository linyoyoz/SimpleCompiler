#include<string>
#include<iostream>
#include<vector>

using namespace std;

#ifndef SYMBOL_H
#define SYMBOL_H

class Rule;
///�O���@�ӳ�@symbol�����A
class Symbol
{
    public:
        Symbol();
        virtual ~Symbol();
        void print();
        void addruleR(Rule*);
        void addruleL(Rule*);
        ///�O����symbol��id,name,type
        int id;
        string name;
        int type;
        int subid;

        ///��b���`�ת�first�ɽT�{�o�I���L�Q��L
        bool used_first;
        ///��b���`�ת�follow�ɽT�{�o�I���L�Q��L
        bool used_follow;

        ///�O���o��symbol�b�����W�h�W���X�{�L�A�åB�O�b�����٬O�k��
        ///int ruleL[MAX_SYMBOL];
        vector<Rule*>ruleL;
        vector<Rule*>ruleR;

    protected:

    private:



};

#endif // SYMBOL_H
