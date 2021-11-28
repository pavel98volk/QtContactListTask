#pragma once
#include <QString>
#include "Contact.h"
#include "FavouritesService.h"
#include "ContactListProviderFromFile.h"
#include "CachedCLP.h"
#include "ContactService.h"





class ContactServiceCachedImpl: public ContactService{
public:
    ContactServiceCachedImpl(std::shared_ptr<FavouritesService> fs, QString filename):
        cached_provider(std::make_unique<ContactListProviderFromFile>(filename),20,5,0),
        favourites_service(fs), search_string(""),favourites_only(false){}

    uint32_t list_length() override;
    Contact get(uint32_t index) override;

    void search(QString new_search_string) override;

    void setFavFilter(bool new_value) override;
    bool getFavFilterActive() override{return this->favourites_only;}
    QString getSearchString() override{return this->search_string;}
private:
    void onFavouritesChange(FavouritesService::CHANGE_TYPE change_type,QString value);
    void favourites_filter(const std::vector<Contact>& copy_from, std::vector<Contact>& copy_to);
    void search_filter(const std::vector<Contact>& copy_from, std::vector<Contact>& copy_to);
    CachedCLP cached_provider;
    QString search_string;
    bool favourites_only;
    std::vector<Contact> filtered_results;
    std::vector<Contact> full_list;
    std::shared_ptr<FavouritesService> favourites_service;
};
