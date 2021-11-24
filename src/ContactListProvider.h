#pragma once
#include <vector>
#include <string>
#include "Contact.h"
#include <map>

class ContactListProvider{
    public:
    ContactListProvider() = default;
    virtual std::vector<SimpleContact> getContacts() = 0;
    virtual std::vector<SimpleContact> getChunk(const uint32_t index, const uint32_t size) = 0;
    virtual uint32_t getLength() = 0;
    virtual void call(const SimpleContact& contact, void (*call_end_function)())  = 0;
};


class ContactListProviderFromFile: public ContactListProvider{
    public:
    ContactListProviderFromFile(const std::string pathname);;
    std::vector<SimpleContact> getContacts() override;
    std::vector<SimpleContact> getChunk(const uint32_t index, const uint32_t size) override;
    uint32_t getLength() override;
    void call(const SimpleContact& contact, void (*call_end_callback)()) override;
private:
    std::string pathname;
};



/*
class СachedSearchableCLP{
    public:
    СachedSearchableCLP() = default;
    void find_letter_chunk();
    void getLetters();
    void getAlphabeticalContacts();
    protected:
    private:
    uint32_t chunk_size = 20, cache_size=50;
    std::vector<Contact> circular_cahce;
    std::vector<Contact> first_index;
    std::map<char, int> letter_start;//the position of the first contact corresponding to each letter
};
*/
