#pragma once
#include <Contact.h>
#include <QString>
#include "ContactListProvider.h"
#include "ContactListProviderFromFile.h"

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
    virtual void search(QString search_string) = 0;
    virtual void setFavFilter(bool new_value) = 0;
    virtual bool getFavFilterActive() = 0;
    virtual QString getSearchString() =0;
};
