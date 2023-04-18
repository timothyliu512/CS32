//
//  Sequence.cpp
//  Homework 1
//
//  Created by Timothy Liu on 4/13/23.
//

#include "Sequence.h"
#include <cassert>
#include <iostream>
#include <string>

Sequence::Sequence() : sequenceSize(0){
}    // Create an empty sequence (i.e., one whose size() is 0).


bool Sequence::empty() const {
    if (sequenceSize == 0)
    {
        return true;
    }
    return false;
}  // Return true if the sequence is empty, otherwise false.


int Sequence::size() const{
    
    return sequenceSize;
    
}   // Return the number of items in the sequence.

int Sequence::insert(int pos, const ItemType& value){
    
    if ( sequenceSize >= DEFAULT_MAX_ITEMS || pos < 0 || pos > sequenceSize) // Capacity check and bounds check
    {
        return -1;
    }
    
    sequenceSize++;
    
    for (int i = sequenceSize-1; i > pos; i--)
    {
        sequenceArray[i] = sequenceArray[i-1];
    }
    
    sequenceArray[pos] = value;
    
    return pos;
}
  // Insert value into the sequence so that it becomes the item at
  // position pos.  The original item at position pos and those that
  // follow it end up at positions one greater than they were at before.
  
  // Return pos if 0 <= pos <= size() and the value could be
  // inserted.  (It might not be, if the sequence has a fixed capacity,
  // e.g., because it's implemented using a fixed-size array.)  Otherwise,
  // leave the sequence unchanged and return -1.  Notice that
  // if pos is equal to size(), the value is inserted at the end.

int Sequence::insert(const ItemType& value){
    
    if ( sequenceSize + 1 > DEFAULT_MAX_ITEMS) // Capacity check
    {
        return -1;
    }
    
    // Identify smallest position p
    int smallestPos = sequenceSize;
    for (int i = 0; i < sequenceSize; i++)
    {
        if (value <= sequenceArray[i])
        {
            smallestPos = i;
            break;
        }
    }
    
    //Move everything that follows it and insert into position p
    sequenceSize++;
    for (int i = sequenceSize-1; i > smallestPos; i--)
    {
        sequenceArray[i] = sequenceArray[i-1];
    }
    
    sequenceArray[smallestPos] = value;
    
    return smallestPos;
}
  // Let p be the smallest integer such that value <= the item at
  // position p in the sequence; if no such item exists (i.e.,
  // value > all items in the sequence), let p be size().  Insert
  // value into the sequence so that it becomes the item in position
  // p.  The original item in position p and those that follow it end
  // up at positions one greater than before.  Return p if the value
  // was actually inserted.  Return -1 if the value was not inserted
  // (perhaps because the sequence has a fixed capacity and is full).

// Just inserts it automatically in order
 
bool Sequence::erase(int pos){
    
    if (pos <0 || pos >= sequenceSize)
    {
        return false;
    }
    
    if (pos >=0 && pos < sequenceSize)
    {
        for (int i = pos; i < sequenceSize-1; i++)
        {
            sequenceArray[i] = sequenceArray[i+1];
        }
        sequenceSize--;
        return true;
    }
    return false;
}
  // If 0 <= pos < size(), remove the item at position pos from
  // the sequence (so that all items that followed that item end up at
  // positions one lower than they were at before), and return true.
  // Otherwise, leave the sequence unchanged and return false.
 
int Sequence::remove(const ItemType& value){
    
    int numberOfDuplicates = 0;

    for ( int i = 0; i < sequenceSize; i++ )
    {
        if ( sequenceArray[i] == value )
        {
            numberOfDuplicates++;
            erase(i);
            i--;
        }
    }
    
    return numberOfDuplicates;
}
  // Erase all items from the sequence that == value.  Return the
  // number of items removed (which will be 0 if no item == value).

bool Sequence::get(int pos, ItemType& value) const {
    if (pos >= 0 && pos < sequenceSize)
    {
        value = sequenceArray[pos];
        return true;
    }
    return false;
}
  // If 0 <= pos < size(), copy into value the item in position pos
  // of the sequence and return true.  Otherwise, leave value unchanged
  // and return false.

bool Sequence::set(int pos, const ItemType& value){
    
    if (pos >=0 && pos < sequenceSize)
    {
        sequenceArray[pos] = value;
        return true;
    }
    return false;
}
  // If 0 <= pos < size(), replace the item at position pos in the
  // sequence with value and return true.  Otherwise, leave the sequence
  // unchanged and return false.

int Sequence::find(const ItemType& value) const{
    int p = -1;
    for (int i = 0; i < sequenceSize; i++)
    {
        if (sequenceArray[i] == value)
            p = i;
    }
    return p;
}
  // Let p be the smallest integer such that value == the item at
  // position p in the sequence; if no such item exists, let p be -1.
  // Return p.

void Sequence::swap(Sequence& other){

    Sequence tempSequence;
    
    for (int i = sequenceSize-1; i >= 0; i--)
    {
        tempSequence.insert(0, sequenceArray[i]);
        erase(i);
    }
    
    for (int i = other.size()-1; i>= 0; i--)
    {
        ItemType tempItem;
        other.get(i, tempItem);
        insert(0, tempItem);
        other.erase(i);
    }
    
    for (int i = 0; i < tempSequence.size(); i++)
    {
        ItemType tempItem;
        tempSequence.get(i, tempItem);
        other.insert(i,tempItem);
    }
    
}
  // Exchange the contents of this sequence with the other one.

void Sequence::dump() const{
    
    std::cerr << std::endl;
    
    for (int i = 0; i < sequenceSize; i++)
        { std::cerr << sequenceArray[i] << " "; }
    std::cerr << std::endl;
    std::cerr << std::endl;
}

