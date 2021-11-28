#include "ContactServiceCachedImpl.h"
#include <QDebug>
#include <algorithm>


uint32_t ContactServiceCachedImpl::list_length(){
    if(search_string == "" && !favourites_only){
        return cached_provider.length();
    } else{
        return filtered_results.size();
    }
}

Contact ContactServiceCachedImpl::get(uint32_t index){
    if(search_string == "" && !favourites_only){
        if(full_list.size() != 0){
            return full_list[index];
        }
        return cached_provider.get(index);
    } else{
        return filtered_results[index];
    }
}

void ContactServiceCachedImpl::search(QString new_search_string){
    new_search_string = new_search_string.toLower();
    if(search_string == new_search_string){
        return;
    }
    if(full_list.size() == 0){
        full_list = cached_provider.getAllWithoutCaching();
    }
    //if filtered_results are populated
    if(false && (search_string !="" || favourites_only)
                // and the string was extended (last or first part appended)
                && new_search_string.contains(search_string,Qt::CaseInsensitive)){
        search_string = new_search_string;
        std::vector<Contact> old_filtered = std::move(filtered_results);
        search_filter(old_filtered, filtered_results);

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
            favourites_filter(full_list, temp_results);
            search_filter(temp_results, filtered_results);
        }
    }
}

void ContactServiceCachedImpl::setFavFilter(bool new_value){
    if(favourites_only == new_value){
        return;
    }
    if(full_list.size() == 0){
        full_list = cached_provider.getAllWithoutCaching();
    }
    this->favourites_only = new_value;
    if(new_value == true){
        if(search_string!=""){
            std::vector<Contact> old_filtered = std::move(filtered_results);
            favourites_filter(old_filtered, filtered_results);
        } else{
            favourites_filter(full_list, filtered_results);
        }
        favourites_service->listenToChange([this](FavouritesService::CHANGE_TYPE change_type,QString value)->void{onFavouritesChange(change_type,value);});
    } else{
        if(search_string != ""){
            search_filter(full_list, filtered_results);
        } else{
            filtered_results.clear();
        }
    }
}

void ContactServiceCachedImpl::onFavouritesChange(FavouritesService::CHANGE_TYPE change_type, QString value){
    switch(change_type){
        case FavouritesService::CHANGE_TYPE::Remove:{
            std::vector<Contact> old_filtered = std::move(filtered_results);
            favourites_filter(old_filtered, filtered_results);
        } break;
        case FavouritesService::CHANGE_TYPE::Insert:
        case FavouritesService::CHANGE_TYPE::UpdateAll:{
            if(search_string!=""){
                std::vector<Contact> temp_results;
                favourites_filter(full_list, temp_results);
                search_filter(temp_results, filtered_results);
            } else{
                favourites_filter(full_list, filtered_results);
            }
        }
    }
    qDebug() <<filtered_results.size();
}

void ContactServiceCachedImpl::favourites_filter(const std::vector<Contact> &copy_from, std::vector<Contact> &copy_to){
    copy_to.clear();
    if(favourites_service != nullptr){
        std::copy_if (copy_from.begin(), copy_from.end(), std::back_inserter(copy_to), [this](const Contact& c){return favourites_service->contains(c.getName());} );
    } else{
        std::copy(copy_from.begin(), copy_from.end(), std::back_inserter(copy_to));
    }
}

void ContactServiceCachedImpl::search_filter(const std::vector<Contact> &copy_from, std::vector<Contact> &copy_to){
    copy_to.clear();
    std::copy_if (copy_from.begin(), copy_from.end(), std::back_inserter(copy_to), [this](const Contact& c){return c.getName().contains(search_string,Qt::CaseInsensitive);} );

}
