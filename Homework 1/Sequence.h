//
//  Sequence.h
//  Homework 1
//
//  Created by Timothy Liu on 4/13/23.
//

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdio.h>
#include <string>

const int DEFAULT_MAX_ITEMS = 160;

// using ItemType = std::string;
using ItemType = unsigned long;

class Sequence
{
  public:
    Sequence();    // Create an empty sequence (i.e., one whose size() is 0).
    bool empty() const;  // Return true if the sequence is empty, otherwise false.
    int size() const;    // Return the number of items in the sequence.
    void dump() const;
    
    int insert(int pos, const ItemType& value);
    
    int insert(const ItemType& value);
    // Just inserts it automatically in order
     
    bool erase(int pos);
     
    int remove(const ItemType& value);

    bool get(int pos, ItemType& value) const; // Is it const?

    bool set(int pos, const ItemType& value);

    int find(const ItemType& value) const;

    void swap(Sequence& other);
    
private:
    int sequenceSize;
    ItemType sequenceArray[DEFAULT_MAX_ITEMS];
};


#endif /* SEQUENCE_H */
