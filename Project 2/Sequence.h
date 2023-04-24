//
//  Sequence.h
//  Project 2
//
//  Created by Timothy Liu on 4/19/23.
//

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdio.h>
#include <string>

//using ItemType = unsigned long;
using ItemType = std::string;

class Sequence
{
    // declare destructor, copy constructor, or assignment operator
    
    
  public:
    
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;
    // Constructors
    
    Sequence(); // Default constructor
    
    Sequence(const Sequence& other);   // Copy constructor
    
    Sequence& operator=(const Sequence& rhs); // Assignment operator
    
    ~Sequence(); // Destructor
    
    
private:
    int       sequenceSize;        // the number of items in the sequence
    
    struct Node
        {
            ItemType nodeValue;
            Node* next;
            Node* prev;
        };
    Node* head;
    Node* tail;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);



#endif /* SEQUENCE_H */
