//
//  Dictionary.h
//  Project 4
//
//  Created by Timothy Liu on 5/31/23.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <string>

class DictionaryImpl;

class Dictionary
{
  public:
    Dictionary(int maxBuckets = 50000);
    ~Dictionary();
    void insert(std::string word);
    void lookup(std::string letters, void callback(std::string)) const;
    
      // We prevent Dictionary objects from being copied or assigned
    Dictionary(const Dictionary&) = delete;
    Dictionary& operator=(const Dictionary&) = delete;

  private:
    DictionaryImpl* m_impl;
};

#endif /* DICTIONARY_H */
