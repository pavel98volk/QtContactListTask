#include "ContactListProviderFromFile.h"

#include<fstream>
#include<istream>
#include <chrono>
#include <thread>
#include <QDebug>
#include <exception>
#include <QFile>


ContactListProviderFromFile::ContactListProviderFromFile(const QString pathname):pathname(pathname){}


std::vector<SimpleContact> ContactListProviderFromFile::getContacts(){
  //1. open file and initialize filestream
  QFile file(this->pathname);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
      throw std::runtime_error("Could not open the file!");
  QTextStream in(&file);

  std::vector<SimpleContact> result;
  QString line_buffer;

  while(!in.atEnd()){
      QStringList splitted = in.readLine().split(",");
      result.push_back(SimpleContact(splitted.value(0), splitted.value(1)));
  }
  return result;
}

std::vector<SimpleContact> ContactListProviderFromFile::getChunk(const uint32_t index, const uint32_t size){
    uint32_t line_count{0};
    QFile file(this->pathname);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("Could not open the file!");
    QTextStream in(&file);


    while(line_count < index && !in.atEnd()){
      in.readLine();
      //in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      line_count++;
    }
    std::vector<SimpleContact> result;
    result.reserve(size);
    std::string line_buffer;

    while(line_count < index+size && !in.atEnd()){
      QStringList splitted = in.readLine().split(",");
      result.push_back(SimpleContact(splitted.value(0), splitted.value(1)));
      line_count++;
    }
    result.shrink_to_fit();
    return result;
}

uint32_t ContactListProviderFromFile::getLength(){
    uint32_t line_count{0};
    QFile file(this->pathname);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("Could not open the file!");
    QTextStream in(&file);
    while( !in.atEnd())
    {   in.readLine();
        line_count++;
    }
    return line_count;
}

void ContactListProviderFromFile::call(const SimpleContact& contact, void (*call_end_callback)()){
  std::this_thread::sleep_for(std::chrono::seconds(10));
  call_end_callback();
}
