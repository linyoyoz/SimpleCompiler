#include"SymbolList.h"
#include<stack>
#include<vector>
using namespace std;
#ifndef SNOW_H
#define SNOW_H


class Snow
{
    public:
        Snow();
        virtual ~Snow();
        stack<Symbol*>inputtoken;
        stack<Symbol*>ruletoken;
    protected:

    private:
};

#endif // SNOW_H
