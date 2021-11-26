#include "ContactService.h"
#include <QDebug>

CachedProvider::CachedProvider(std::unique_ptr<ContactListProvider> provider, uint32_t chunk_size, uint32_t cached_chunk_count, uint32_t central_index):
    provider(std::move(provider)), chunk_size(chunk_size),chunk_count(cached_chunk_count){
    this->calculate_first_chunk(central_index);

    this->contact_list_length = this->provider->getLength();
    cached_chunks.init(chunk_count,this->getInitialChunks());

}

Contact CachedProvider::get(uint32_t index){
    //1. if index is in the last chunk of the cached part of the list, load the previous chunk
    long current_chunk = index/chunk_size;
    if(current_chunk == chunk_first+chunk_count-1){
        qDebug()<<"loading new chunk.."<<chunk_first+chunk_count;
        chunk_first +=1;
        cached_chunks[chunk_first+chunk_count-1] = getChunk(chunk_first+chunk_count-1);
    }
    //2. if index is in the first chunk of the cached part of the list, load the next chunk
    else if(current_chunk == chunk_first){
        qDebug()<<"loading previous chunk: " << chunk_first-1;
        chunk_first -=1;
        cached_chunks[chunk_first] = getChunk(chunk_first);
    }
    //3. if index is beyond the cached part, this is concidered as jump and the whole cache is reloaded
    else if (current_chunk < chunk_first || current_chunk >= chunk_first+chunk_count){
        qDebug()<<"loading new chunk..";
        calculate_first_chunk(index);
        cached_chunks.init(chunk_count,this->getInitialChunks());
    }
    if(cached_chunks[current_chunk].get().size() <= index%chunk_size){
        throw std::out_of_range("The index exceeds the size of the respective chunk");
    }
    return cached_chunks[current_chunk].get()[index%chunk_size];
}

std::future<std::vector<GeneratedPhotoContact> > CachedProvider::getChunk(int chunk_index){
    if(chunk_index < 0 || chunk_index > (contact_list_length-1)/chunk_size){
        return std::async(std::launch::async, []{
            return std::vector<Contact>();
        });
    }
    return std::async(std::launch::async, [this, chunk_index]{
        std::vector<SimpleContact> scv = provider->getChunk(chunk_size*chunk_index,chunk_size);
        std::vector<Contact> cv;
        cv.reserve(scv.size());
        for(const SimpleContact& sc:scv){
            cv.push_back(sc);
        }
        return cv;
    });
}

std::vector<MultigetFuture<std::vector<GeneratedPhotoContact> > > CachedProvider::getInitialChunks(){
    std::vector<MultigetFuture<std::vector<Contact>>> result;
    result.reserve(chunk_count);
    for(uint32_t i=0;i<chunk_count;i++){
        int chunk_index = (int(i)-int(chunk_first))%int(chunk_count) + int(chunk_first);
        result.emplace_back(getChunk(chunk_index));
    }
    return result;
}

void CachedProvider::calculate_first_chunk(uint32_t central_index){
    chunk_first = (int(central_index) - int((chunk_count-1)*chunk_size)/2)/int(chunk_size);
}

uint32_t CachedSearchableContactService::list_length(){
    if(search_string == "" && !favourites_only){
        return cached_provider.length();
    } else{
        return filtered_results.size();
    }
}

GeneratedPhotoContact CachedSearchableContactService::get(uint32_t index){
    if(search_string == "" && !favourites_only){
        if(full_list.size() != 0){
            return full_list[index];
        }
        return cached_provider.get(index);
    } else{
        return filtered_results[index];
    }
}

void CachedSearchableContactService::search(std::string new_search_string){
    tolower_inplace(new_search_string);
    if(search_string == new_search_string){
        return;
    }
    if(full_list.size() == 0){
        full_list = cached_provider.getAllWithoutCaching();
    }
    //if filtered_results are populated
    if((search_string !="" || favourites_only)
                // and the last letter was appended to the string
                && new_search_string == search_string.substr(0,search_string.length()-1)){
        search_string == new_search_string;
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

void CachedSearchableContactService::setFavFilter(bool new_value){
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
        favourites_service->listenToChange([this](FavouritesService::CHANGE_TYPE change_type,std::string value)->void{onFavouritesChange(change_type,value);});
        qDebug() <<filtered_results.size();

    } else{
        if(search_string != ""){
            search_filter(full_list, filtered_results);
        } else{
            filtered_results.clear();
        }
    }
}

void CachedSearchableContactService::favourites_filter(const std::vector<GeneratedPhotoContact> &copy_from, std::vector<GeneratedPhotoContact> &copy_to){
    copy_to.clear();
    if(favourites_service != nullptr){
        std::copy_if (copy_from.begin(), copy_from.end(), std::back_inserter(copy_to), [this](const Contact& c){return favourites_service->contains(c.getName());} );
    } else{
        std::copy(copy_from.begin(), copy_from.end(), std::back_inserter(copy_to));
    }
}

void CachedSearchableContactService::search_filter(const std::vector<GeneratedPhotoContact> &copy_from, std::vector<GeneratedPhotoContact> &copy_to){
    copy_to.clear();
    std::regex search_expr (".*"+search_string+".*");
    std::copy_if (copy_from.begin(), copy_from.end(), std::back_inserter(copy_to), [search_expr](const Contact& c){return std::regex_match(tolower(c.getName()),search_expr);} );

}
