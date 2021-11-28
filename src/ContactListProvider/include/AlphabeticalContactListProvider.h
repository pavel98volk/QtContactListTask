#pragma once
#include "ContactListProvider.h"
class ContactListProviderAlphabetical: public virtual ContactListProvider{
    public:
    virtual std::vector<QString> getAvailableLetters()=0; // QString to support unicode, wchar_t may not always work
    virtual uint32_t getLeterIndex() =0;
};


