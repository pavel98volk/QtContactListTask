#include "ContactListProvider.h"
#include<fstream>
#include<istream>
#include <chrono>
#include <thread>
#include <QDebug>
#include <exception>
#include <QFile>

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
  /* // replaced by packaged qrc resource
  std::ifstream in;
  in.open(this->pathname);
  if(!in.is_open()){
  throw std::runtime_error("Failed to open file with contacts in ContactListProviderFromFile");
  }*/
  //1. open file and initialize filestream
  QFile file(this->pathname.c_str());
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
      throw std::runtime_error("Could not open the file!");
  QTextStream in(&file);

  std::vector<SimpleContact> result;
  std::string line_buffer;

  while(!file.atEnd()){
    line_buffer = in.readLine().toStdString();
    //getline(in, line_buffer)
    if (line_buffer.find(",") != std::string::npos) {
        result.push_back(SimpleContact(line_buffer.substr(0, line_buffer.find(",")), line_buffer.substr(1, line_buffer.find(","))));
    }
  }
  return result;
}

std::vector<SimpleContact> ContactListProviderFromFile::getChunk(const uint32_t index, const uint32_t size){
    std::string s;
    uint32_t line_count{0};
    QFile file(this->pathname.c_str());
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("Could not open the file!");
    QTextStream in(&file);


    while(line_count < index && !file.atEnd()){
      in.readLine();
      //in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      line_count++;
    }
    std::vector<SimpleContact> result;
    result.reserve(size);
    std::string line_buffer;
    while(line_count < index+size && !file.atEnd()){
      line_buffer = in.readLine().toStdString();
      result.push_back(SimpleContact(line_buffer.substr(0, line_buffer.find(",")), line_buffer.substr(1, line_buffer.find(","))));
      line_count++;
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
