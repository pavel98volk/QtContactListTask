#ifndef CONTACTSERVICE_H
#define CONTACTSERVICE_H
#include <Contact.h>
#include <string>
#include <string>
#include "ContactListProvider.h"
#include <memory>
#include "utils.h"
#include <future>
#include "FavouritesService.h"
#include <regex>
//first, the favourites filter is applied, then
class ContactService
{
public:
    virtual uint32_t list_length() =0;
    virtual Contact get(uint32_t index) = 0;
    virtual void search(std::string search_string) = 0;
    virtual void setFavFilter(bool new_value) = 0;
    virtual bool getFavFilterStatus() = 0;
    virtual std::string getSearchString() =0;
};


class CachedProvider{
public:
    CachedProvider(std::unique_ptr<ContactListProvider> provider,uint32_t chunk_size, uint32_t cached_chunk_count, uint32_t central_index);
    Contact get(uint32_t index);
    std::vector<Contact> getAllWithoutCaching(){
        std::vector<Contact> cv;
        std::vector<SimpleContact> scv = provider->getContacts();
        cv.reserve(scv.size());
        for(const auto& sc: scv){
            cv.emplace_back(sc);
        }
        return cv;
    }
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
    CachedSearchableContactService(std::shared_ptr<FavouritesService> fs, std::string filename):
        cached_provider(std::make_unique<ContactListProviderFromFile>(filename),20,5,0),
        favourites_service(fs), search_string(""),favourites_only(false){}

    uint32_t list_length() override;
    Contact get(uint32_t index) override;

    void search(std::string new_search_string) override;

    void setFavFilter(bool new_value) override;
    bool getFavFilterStatus() override{return this->favourites_only;}
    std::string getSearchString() override{return this->search_string;}
private:
    void onFavouritesChange(FavouritesService::CHANGE_TYPE change_type,std::string value){

    }
    void favourites_filter(const std::vector<Contact>& copy_from, std::vector<Contact>& copy_to);
    void search_filter(const std::vector<Contact>& copy_from, std::vector<Contact>& copy_to);
    CachedProvider cached_provider;
    std::string search_string;
    bool favourites_only;
    std::vector<Contact> filtered_results;
    std::vector<Contact> full_list;
    std::shared_ptr<FavouritesService> favourites_service;
};



#endif // CONTACTSERVICE_H
