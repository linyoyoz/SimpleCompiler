#ifndef SYMBOLCOMMONLIST_H
#define SYMBOLCOMMONLIST_H

#include "SymbolList.h"

//�i�H���ƪ�SymbolList
class SymbolCommonList : public SymbolList
{
    public:
        SymbolCommonList();
        void addSymbol(Symbol *target);
        virtual ~SymbolCommonList();

    protected:

    private:
};

#endif // SYMBOLCOMMONLIST_H
