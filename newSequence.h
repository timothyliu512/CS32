//
//  newSequence.h
//  Homework 1
//
//  Created by Timothy Liu on 4/13/23.
//

#ifndef NEWSEQUENCE_H
#define NEWSEQUENCE_H

#include <stdio.h>
#include <string>

const int DEFAULT_MAX_ITEMS = 160;

// using ItemType = std::string;
using ItemType = unsigned long;

class Sequence
{
  public:
    
    bool empty() const;  // Return true if the sequence is empty, otherwise false.
    int size() const;    // Return the number of items in the sequence.
    void dump() const;
    
    int insert(int pos, const ItemType& value);
    
    int insert(const ItemType& value);
    // Just inserts it automatically in order
     
    bool erase(int pos);
     
    int remove(const ItemType& value);

    bool get(int pos, ItemType& value) const;

    bool set(int pos, const ItemType& value);

    int find(const ItemType& value) const;
    
    void swap(Sequence& other);
    
    // Constructors:
    
    Sequence();    // Create an empty sequence (i.e., one whose size() is 0).
    
    Sequence(int arraySize); // Constructor with parameter
    
    Sequence(const Sequence& other);   // copy constructor
    
    Sequence& operator=(const Sequence& rhs); // Assignment operator
    
    ~Sequence(); // Destructor
    
private:
    int maxSequenceSize;
    int sequenceSize;
    ItemType* sequenceArray;
};


#endif /* NEWSEQUENCE_H */
