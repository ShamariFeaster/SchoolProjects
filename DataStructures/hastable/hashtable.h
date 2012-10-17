#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <crypt.h>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <stdlib.h>
#include <cstring>
#include <algorithm>
#include <iomanip>
using namespace std;

namespace cop4530
{

static const unsigned int max_prime = 64997;

class HashTable
  {
  public:
    HashTable();
    explicit HashTable(size_t n);
    ~HashTable();
    unsigned int size();
    void dumpTable();
    bool loadFromFile(string filename);
    bool writeToFile(string filename);

    bool addUser(string uname, string pw, bool encrypt_pw);
    bool removeUser(string uname, string pw);
    bool changePw(string uname, string pw);
    bool findUser(string uname, string pw);
  private:
    unsigned int Index (const string &);
    unsigned int hash_function   (const string& );
    unsigned int prime_below(unsigned int);
    void setPrimes(vector<unsigned int> &);
    vector < list < pair <string, string> > > bucketVector;

    size_t length;
  };
}

#include "hashtable.cpp"

#endif
