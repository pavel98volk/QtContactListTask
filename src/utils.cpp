#include "utils.h"

uint32_t crc32_checksum(const std::string message) {
   uint32_t byte, crc, mask;

   int length = message.length();
   crc = 0xFFFFFFFF;
   for(int i =0; i<length;i++){
      byte = message[i];            // Get next byte.
      crc = crc ^ byte;
      for (int j = 7; j >= 0; j--) {    // Do eight times.
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
      }
      i = i + 1;
   }
   return ~crc;
}

uint32_t getNumberBits(const uint32_t number, const uint from, const uint to){
    uint32_t mask = 0;
    for(uint i = from; i <=to;i++){
        mask += 1<<i;
    }
    return (number & mask)>>from;
}
void tolower_inplace(std::string& data){
    std::for_each(data.begin(), data.end(), [](char & c){
        c = ::tolower(c);
    });
}
std::string tolower(std::string data){
    tolower_inplace(data);
    return data;
}



