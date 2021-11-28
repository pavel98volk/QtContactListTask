#pragma once
#include <vector>
#include <QString>
#include <string>
#include "SimpleContact.h"
#include <map>

class ContactListProvider{
    public:
    virtual std::vector<SimpleContact> getContacts() = 0;
    virtual std::vector<SimpleContact> getChunk(const uint32_t index, const uint32_t size) = 0;
    virtual uint32_t getLength() = 0;
    virtual void call(const SimpleContact& contact, void (*call_end_function)())  = 0;
};

