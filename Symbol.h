#include<string>
#include<iostream>
#include<vector>

using namespace std;

#ifndef SYMBOL_H
#define SYMBOL_H

class Rule;
///記錄一個單一symbol的型態
class Symbol
{
    public:
        Symbol();
        virtual ~Symbol();
        void print();
        void addruleR(Rule*);
        void addruleL(Rule*);
        ///記錄此symbol的id,name,type
        int id;
        string name;
        int type;
        int subid;

        ///當在做深度的first時確認這點有無被找過
        bool used_first;
        ///當在做深度的follow時確認這點有無被找過
        bool used_follow;

        ///記錄這個symbol在哪條規則上有出現過，並且是在左邊還是右邊
        ///int ruleL[MAX_SYMBOL];
        vector<Rule*>ruleL;
        vector<Rule*>ruleR;

    protected:

    private:



};

#endif // SYMBOL_H
