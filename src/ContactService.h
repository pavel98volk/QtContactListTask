#ifndef CONTACTSERVICE_H
#define CONTACTSERVICE_H
#include <Contact.h>
#include <string>
#include <string>
#include "ContactListProvider.h"
#include <memory>
#include "utils.h"
#include <future>

class ContactService
{
public:
    virtual uint32_t list_length() =0;
    virtual Contact get(uint32_t index) = 0;
    virtual void setSearchString(std::string search_string) = 0;
};


class CachedProvider{
public:
    CachedProvider(std::unique_ptr<ContactListProvider> provider,uint32_t chunk_size, uint32_t cached_chunk_count, uint32_t central_index);
    Contact get(uint32_t index);

    uint32_t length(){
        return contact_list_length;
    }
private:
    std::future<std::vector<Contact>> getChunk(int chunk_index);
    std::vector<MultigetFuture<std::vector<Contact>>> getInitialChunks();
protected:
    inline void calculate_first_chunk(uint32_t central_index);
private:
    std::unique_ptr<ContactListProvider> provider;
    CircularArray<MultigetFuture<std::vector<Contact>>> cached_chunks;
    const uint32_t chunk_size, chunk_count;
    int chunk_first;
    uint32_t contact_list_length;

};

class CachedSearchableContactService: public ContactService{
public:
    CachedSearchableContactService(std::string filename):cached_provider(std::make_unique<ContactListProviderFromFile>(filename),20,5,0){}
    uint32_t list_length() override{
        if(search_string == ""){
            return cached_provider.length();
        } else{
            return search_results.size();
        }
    }
    Contact get(uint32_t index) override{
        if(search_string == ""){
            return cached_provider.get(index);
        } else{
            return search_results[index];
        }
    }
    void setSearchString(std::string search_string) override{
        return;
    }
private:
    CachedProvider cached_provider;
    std::string search_string;
    std::vector<Contact> search_results;

};



#endif // CONTACTSERVICE_H
