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
#include <functional>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <fstream>
//using namespace std;

void removeNonLetters(std::string& s);

  // This class does the real work of the implementation.

class DictionaryImpl
{
  public:
    DictionaryImpl(int /* maxBuckets */) {}
    ~DictionaryImpl() {}
    void insert(std::string word);
    void lookup(std::string letters, void callback(std::string)) const;
  private:
    std::unordered_map < std::string, std::list<std::string> > uMap;
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
        
        // Assign word to its correct bucket with its other anagrams based on its matching sorted letters
        uMap[sortedWord].push_back(word);
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
    
    // Find the correct bucket (Gives you the corresponding list with the hash value)
    // If not found, you will be at the end of the unordered_map
    std::unordered_map<std::string, std::list<std::string> >::const_iterator p = uMap.find(letters);
    
    // As long as we're not at the end of our unordered_map (meaning you found the associated list)
    if(p != uMap.end() )
    {
        // Get the list associated with the bucket that you found
        const std::list<std::string>& list = p->second;
        
        // Iterate through list of anagrams
        for(std::list<std::string>::const_iterator listIterator = list.begin(); listIterator != list.end() ; listIterator++)
        {
            // Return the found anagram
            callback(*listIterator);
        }
    }
    
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

