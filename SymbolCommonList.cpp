#include "SymbolCommonList.h"

SymbolCommonList::SymbolCommonList()
{
    //ctor
}

SymbolCommonList::~SymbolCommonList()
{
    //dtor
}
///主要用做規則的RHS
void SymbolCommonList::addSymbol(Symbol *target)
{
    s.push_back(target);
}
