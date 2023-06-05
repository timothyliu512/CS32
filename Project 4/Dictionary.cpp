//
//  Dictionary.cpp
//  Project 4
//
//  Created by Timothy Liu on 5/31/23.
//

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap

// My includes
#include <functional> // Hash function
#include <stdlib.h>
#include <vector>   //
#include <algorithm> // Sort
#include <fstream>
using namespace std;

void removeNonLetters(std::string& s);

  // This class does the real work of the implementation.

class DictionaryImpl
{
  public:
    DictionaryImpl(int maxBuckets) : buckets(maxBuckets){}
    ~DictionaryImpl() {}
    void insert(std::string word);
    void lookup(std::string letters, void callback(std::string)) const;
  private:
    std::vector<std::list<std::string> > buckets;
};

// Constructs the dictionary hashtable
void DictionaryImpl::insert(std::string word)
{
    // For a given word:
    
    // Format the string so that it's a proper word
    // Remove numbers, spaces, etc. Basically only include letters
    removeNonLetters(word);
    
    // As long as valid word:
    if( ! word.empty() )
    {
        // Sort the word so all characters appear in alphabetical order
        std::string sortedWord = word;
        sort(sortedWord.begin(), sortedWord.end());
        // team -> aemt
        // mate -> aemt
        
        // Apply hash function and get hash value
        unsigned int index = std::hash<string>()(sortedWord) % buckets.size();
        
        // Access the list of anagrams
        std::list<std::string>& bucket = buckets[index];
        
        // Insert word to the end of the list
        bucket.push_back(word);
    }
}
    

// #1
void DictionaryImpl::lookup(std::string letters, void callback(std::string)) const
{
    // Bounds check for undefined behavior
    if (callback == nullptr)
        return;
    
    // Checks if valid word
    removeNonLetters(letters);
    if ( letters.empty() )
    {
        return;
    }

    // Sort the word so all characters in alphabetical order
    sort(letters.begin(), letters.end());
    
    // Apply hash function and get hash value to find correct bucket
    unsigned int index = std::hash<string>()(letters) % buckets.size();

    // Access the found list (bucket)
    const std::list<std::string>& bucket = buckets[index];
    
    // Iterate through each anagram in the bucket, outputting the anagrams
    for (std::list<std::string>::const_iterator word = bucket.begin(); word != bucket.end(); word++)
    {
        // Sort current word in list
        std::string sortedWord = *word;
        sort(sortedWord.begin(), sortedWord.end());
        // Check if it's actually an anagram of the word you inputted
        if(sortedWord == letters)
        {
            callback(*word);
        }
    }
    
    
    // Get the list associated with the bucket that you found
        
        
        // Iterate through list of anagrams
        
        
            // Return the found anagram
            
        
}

// Given function (unchanged)
void removeNonLetters(std::string& s)
{
    std::string::iterator to = s.begin();
    for (std::string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}


//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(std::string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(std::string letters, void callback(std::string)) const
{
    m_impl->lookup(letters,callback);
}

