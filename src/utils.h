#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <future>
#include <QDebug>

/* 1. Circular array has a constant size
 * 2. Initial data must be provided.
 */
template <class T>
class CircularArray{
public:
    CircularArray():length(0){

    }
    CircularArray(int length, std::vector<T>&& data):length(length){
        this->data = std::move(data);
    }
    void init(int length, std::vector<T>&& data){
        this->data = std::move(data);
        this->length = length;
    }

    T& operator[](int index){
        int real_index = index%length;
        if(real_index < 0) real_index +=length;
        return data[real_index];
    }
protected:
    int length;
private:
    std::vector<T> data;
};

template <class T>
class MultigetFuture{
public:
    MultigetFuture(std::future<T> f){
        this->f = std::move(f);
        this->data = nullptr;
    };
    T& get(){
        if(data ==nullptr){
            this->wait();
        }
        return *data;
    }
protected:
    void wait(){
        f.wait();
        data = std::make_unique<T>(std::move(f.get()));
    }

private:
    std::future<T> f;
    std::unique_ptr<T> data;
};

template <class T>
class AutoKeyIntMap: public std::map<int, T>{
public:
    int insert_genkey(T data){
        int key = rand();
        while (this->find(key) != this->end()) {
            key = rand();
        }
        this->insert({key, data});
    }
};


uint32_t crc32_checksum(const std::string message);

uint32_t getNumberBits(const uint32_t number, const uint from, const uint to);
