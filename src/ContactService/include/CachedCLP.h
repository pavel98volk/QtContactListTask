#pragma once
#include "Contact.h"
#include <memory>
#include "ContactListProvider.h"
#include <future>
#include "utils.h"
/*
 * This class temporarily stores the sequential subset of the contact list to reduce queries to the device while having acceptable memory consumption and loading time.
 * It uses futures to load the chunk of contacts asynchronously when the neighbor chunk is beinng accessed.
 */
class CachedCLP{
public:
    CachedCLP(std::unique_ptr<ContactListProvider> provider,uint32_t chunk_size, uint32_t cached_chunk_count, uint32_t central_index);
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
