#include "SymbolCommonList.h"

SymbolCommonList::SymbolCommonList()
{
    //ctor
}

SymbolCommonList::~SymbolCommonList()
{
    //dtor
}
///�D�n�ΰ��W�h��RHS
void SymbolCommonList::addSymbol(Symbol *target)
{
    s.push_back(target);
}
