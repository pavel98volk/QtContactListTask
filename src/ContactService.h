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

    uint32_t list_length() override{
        if(search_string == "" && !favourites_only){
            return cached_provider.length();
        } else{
            return filtered_results.size();
        }
    }
    Contact get(uint32_t index) override{
        if(search_string == "" && !favourites_only){
            if(full_list.size() != 0){
                return full_list[index];
            }
            return cached_provider.get(index);
        } else{
            return filtered_results[index];
        }
    }

    void search(std::string new_search_string) override{
        if(full_list.size() == 0){
            full_list = cached_provider.getAllWithoutCaching();
        }
        // if the last letter was appended to the string, and it is not the first letter
        if (new_search_string == search_string.substr(0,search_string.length()-1)){
            std::vector<Contact> old_filtered = std::move(filtered_results);
            this->search_filter(old_filtered, filtered_results);
        }
        else{
            search_string = new_search_string;
            if(search_string == ""){
                if(favourites_only){
                    favourites_filter(full_list, filtered_results);
                }
            }
            else if (!favourites_only){
                search_filter(full_list, filtered_results);
            } else{
                std::vector<Contact> temp_results;
                this->favourites_filter(full_list, temp_results);
                this->search_filter(temp_results, filtered_results);
            }
        }
    }

    void setFavFilter(bool new_value) override{
        if(new_value == true){
            std::vector<Contact> old_filtered = std::move(filtered_results);
            favourites_filter(old_filtered, filtered_results);
            favourites_service->listenToChange([this](FavouritesService::CHANGE_TYPE change_type,std::string value)->void{onFavouritesChange(change_type,value);});
        } else{

        }
    }
    bool getFavFilterStatus() override{return this->favourites_only;}
    std::string getSearchString() override{return this->search_string;}
private:
    void onFavouritesChange(FavouritesService::CHANGE_TYPE change_type,std::string value){

    }
    void favourites_filter(const std::vector<Contact>& copy_from, std::vector<Contact>& copy_to){
        copy_to.clear();
        if(favourites_service != nullptr){
            std::copy_if (copy_from.begin(), copy_from.end(), std::back_inserter(copy_to), [this](const Contact& c){return favourites_service->contains(c.getName());} );
        } else{
            std::copy(copy_from.begin(), copy_from.end(), std::back_inserter(copy_to));
        }
    }
    void search_filter(const std::vector<Contact>& copy_from, std::vector<Contact>& copy_to){
        copy_to.clear();
        std::regex search_expr (search_string);
        std::copy_if (copy_from.begin(), copy_from.end(), std::back_inserter(copy_to), [search_expr](const Contact& c){return std::regex_match(c.getName(),search_expr);} );

    }
    CachedProvider cached_provider;
    std::string search_string;
    bool favourites_only;
    std::vector<Contact> filtered_results;
    std::vector<Contact> full_list;
    std::shared_ptr<FavouritesService> favourites_service;
};



#endif // CONTACTSERVICE_H
