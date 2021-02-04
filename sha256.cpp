#include <iostream>
#include <fstream>
#include <vector>
#include <openssl/sha.h>

// sudo apt-get install libssl-dev
// g++ -lssl -lcrypto sha256.cpp

using namespace std;

struct block
   {
   unsigned char data[1024];
   unsigned char hash[32];
   };

static_assert(sizeof(struct block) == sizeof(unsigned char)*(1024+32)); // no padding allowed
   
void get_sha256(unsigned char * data, int size, unsigned char * hash)
   {
   SHA256_CTX sha256;
   SHA256_Init(&sha256);
   SHA256_Update(&sha256, data, size);
   SHA256_Final(hash, &sha256);
   }
   
int main()
   {
   vector<block> all_blocks;
   ifstream my_file("test1.mp4", ios::binary | ios::in);
   int i = 0;
   while (my_file.good())
      {
      block tmp;
      my_file.read((char *) tmp.data, 1024);
      all_blocks.push_back(tmp);
      }
   get_sha256(all_blocks[all_blocks.size()-1].data, my_file.gcount(), all_blocks[all_blocks.size()-2].hash);
   my_file.close();
   for (int i = all_blocks.size()-2; i >= 1; i--)
      get_sha256(all_blocks[i].data, 1024+32, all_blocks[i-1].hash);
   unsigned char hzero[32];
   get_sha256(all_blocks[0].data, 1024+32, hzero);
   for(int i=0; i<32; ++i)
      printf("%02x", hzero[i]);
   cout << "\n";
   return 0;
   }
