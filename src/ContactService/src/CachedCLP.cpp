
#include "CachedCLP.h"

CachedCLP::CachedCLP(std::unique_ptr<ContactListProvider> provider, uint32_t chunk_size, uint32_t cached_chunk_count, uint32_t central_index):
    provider(std::move(provider)), chunk_size(chunk_size),chunk_count(cached_chunk_count){
    this->calculate_first_chunk(central_index);

    this->contact_list_length = this->provider->getLength();
    cached_chunks.init(chunk_count,this->getInitialChunks());

}

Contact CachedCLP::get(uint32_t index){
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
        qDebug()<<"reloading chunks...";
        calculate_first_chunk(index);
        cached_chunks.init(chunk_count,this->getInitialChunks());
    }
    if(cached_chunks[current_chunk].get().size() <= index%chunk_size){
        throw std::out_of_range("The index exceeds the size of the respective chunk");
    }
    return cached_chunks[current_chunk].get()[index%chunk_size];
}

std::future<std::vector<Contact> > CachedCLP::getChunk(int chunk_index){
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

std::vector<MultigetFuture<std::vector<Contact> > > CachedCLP::getInitialChunks(){
    std::vector<MultigetFuture<std::vector<Contact>>> result;
    result.reserve(chunk_count);
    for(uint32_t i=0;i<chunk_count;i++){
        int chunk_index = (int(i)-int(chunk_first))%int(chunk_count) + int(chunk_first);
        result.emplace_back(getChunk(chunk_index));
    }
    return result;
}

void CachedCLP::calculate_first_chunk(uint32_t central_index){
    chunk_first = (int(central_index) - int((chunk_count-1)*chunk_size)/2)/int(chunk_size);
}
