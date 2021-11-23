#include "ContactListProvider.h"
#include<fstream>
#include<istream>
#include <chrono>
#include <thread>
#include <QDebug>

uint32_t countLines(std::string pathname){
    std::string s;
    uint32_t line_count{0};
    std::ifstream in;
    in.open(pathname);
    std::ofstream out;
    while(!in.eof()) {
    	getline(in, s);
    	line_count++;	
    }
    return line_count;
}

ContactListProviderFromFile::ContactListProviderFromFile(const std::string pathname):pathname(pathname){}


std::vector<SimpleContact> ContactListProviderFromFile::getContacts(){
    std::ifstream in (this->pathname, std::ifstream::in);
  std::vector<SimpleContact> result;
  std::string line_buffer;

  while(!in.eof()){
    getline(in, line_buffer);
    if (line_buffer.find(",") != std::string::npos) {
        result.push_back(SimpleContact(line_buffer.substr(0, line_buffer.find(",")), line_buffer.substr(1, line_buffer.find(","))));
    }
  }
  return result;
}

std::vector<SimpleContact> ContactListProviderFromFile::getChunk(const uint32_t index, const uint32_t size){
    std::string s;
    uint32_t line_count{0};
    std::ifstream in(this->pathname,std::ifstream::in);

    while(line_count < index && !in.eof()){
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::vector<SimpleContact> result;
    result.reserve(size);
    std::string line_buffer;
    while(line_count < index+size && !in.eof()){
      getline(in, line_buffer);
      result.push_back(SimpleContact(line_buffer.substr(0, line_buffer.find(",")), line_buffer.substr(1, line_buffer.find(","))));
    }
    result.shrink_to_fit();
    return result;
}

uint32_t ContactListProviderFromFile::getLength(){
  return countLines(this->pathname);
}

void ContactListProviderFromFile::call(const SimpleContact& contact, void (*call_end_callback)()){
  std::this_thread::sleep_for(std::chrono::seconds(10));
  call_end_callback();
}
