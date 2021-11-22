#pragma once;
#include <vector>
#include <string>
#include "Contact.h"
#include <map>
class ContactListProvider{
    public:
    ContactListProvider() = default;
    virtual std::vector<SimpleContact> getContacts() = 0;
    virtual std::vector<SimpleContact> getChunk(const uint32_t& chunk) = 0;
    virtual uint32_t getChunkCount() = 0;
    virtual uint32_t getChunkSize() = 0;
    virtual void call(const SimpleContact& contact, void (*call_end_function)())  = 0;
};

class ContactListProviderFromFile: public ContactListProvider{
    public:
    ContactListProviderFromFile(const std::string pathname):pathname(pathname){};
    std::vector<SimpleContact> getContacts() override;
    std::vector<SimpleContact> getChunk(const uint32_t& chunk) override;
    uint32_t getChunkCount() override;
    uint32_t getChunkSize() override;
    void call(const SimpleContact& contact, void (*call_end_callback)()) override;

private:
    std::string pathname;
};

/*
class ContactService{
public:
    ContactService(ContactListProvider&& provider){

    }
private:
    std::unique_ptr<ContactListProvider
};*/

//assumes that contacts are provided in alphabetical order.
/*
class AlphabeticalContactListProviderNaive: public ContactListProvider{
    public:
    AlphabeticalContactListProviderNaive() = default;
    void find_letter_chunk();
    void getLetters();
    void getAlphabeticalChunk(char letter, uint32_t chunk_num);
    void getAlphabeticalContacts();
    protected:
    private:
    std::map<char, int> letter_position;
};*/
