#pragma once
#include "ContactListProvider.h"

class ContactListProviderFromFile: public virtual ContactListProvider{
    public:
    ContactListProviderFromFile(const QString pathname);
    std::vector<SimpleContact> getContacts() override;
    std::vector<SimpleContact> getChunk(const uint32_t index, const uint32_t size) override;
    uint32_t getLength() override;
    void call(const SimpleContact& contact, void (*call_end_callback)()) override;
protected:
    QString pathname;
};
