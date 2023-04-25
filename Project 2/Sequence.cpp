//
//  Sequence.cpp
//  Project 2
//
//  Created by Timothy Liu on 4/19/23.
//

#include "Sequence.h"
#include <iostream>
#include <string>

using namespace std;
//using ItemType = unsigned long;
using ItemType = std::string;

// EMPTY
bool Sequence::empty() const
{
    if (sequenceSize == 0) // If size is 0, sequence is empty
    {
        return true;
    }
    
    if ( head == nullptr && tail == nullptr) // If linked list contains 0 nodes, sequence is empty
    {
        return true;
    }
    
    return false; // Otherwise sequence not empty
}

// SIZE
int Sequence::size() const
{
    return sequenceSize; // Getter for size of linked list
}

// INSERT( POS, VALUE)
int Sequence::insert(int pos, const ItemType& value){
    
    if ( pos < 0  ||  pos > size() ) // Bounds check
    {
        return -1;
    }
    
    if ( size() == 0 )  // If nothing in linked list, need to create the first node
    {
        Node* newNode = new Node; // New node to hold new value
        newNode->nodeValue = value; // Store value into the node
        head = tail = newNode; // Head and tail point to single node
        newNode->next = newNode->prev = nullptr; // No previous or next values b/c only 1 item
        sequenceSize++; // Increase sequence size to reflect changes
        return pos;
    }
    
    // Create new node for new value
    Node* newNode = new Node;       // Dynamically allocate new node
    newNode->nodeValue = value;     // Store value into the node
    
    Node* p = head;
    for (int i = 0; p != nullptr && i < pos; p=p->next, i++) // Go through the node until you reach position you want, starting with the first node
    {
        ;
    }
    
    // Plan: At the node you land on, that node and the nodes that follow are pushed down one. So the inserted node gets inserted right before the current node p is pointing at
    if ( p == head ) // New node should be inserted at the very start
    {
        newNode->next = head;       // Establish inserted node's successor
        newNode->prev = nullptr;    // Establish inserted node's predecessor
        p->prev = newNode;          // Connect pointed node to inserted nodee
        head = newNode;             // Establish new head
        sequenceSize++;             // Increase sequence size
        return pos;                 // Return pos it was inserted at
    }
    else if ( p == nullptr )        // New node should be inserted at the very end
    {
        newNode->next = nullptr;    // Establish inserted node's successor
        newNode->prev = tail;       // Establish inserted node's predecessor
        tail->next = newNode;       // The original last node will now be the second to last node
        tail = newNode;             // Establish new tail
        sequenceSize++;             // Increase sequence size
        return pos;                 // Return pos it was inserted at
    }
    else                            // New node should be inserted between start and end
    {
        newNode->next = p;          // Establish inserted node's successor
        newNode->prev = p->prev;    // Establish inserted node's predecessor
        p->prev->next = newNode;    // Previous node's successor will now be the inserted node
        p->prev = newNode;          // Successor node's predecessor will now be the inserted node
        sequenceSize++;             // Increase sequence size
        return pos;                 // Return pos it was inserted at
    }
}

// INSERT( VALUE )
int Sequence::insert(const ItemType& value){
    
    int insertedPosition = 0;                   // Keeps track of position value is inserted into
    Node* newNode = new Node;                   // Dynamically allocate new node
    newNode->nodeValue = value;                 // Set new node's value
    
    if ( size() == 0 )  // If nothing in linked list, need to create the first node
    {
        head = tail = newNode;                   // Set head and tail equal to each other
        newNode->next = newNode->prev = nullptr; // Establish successors and predecessors
        sequenceSize++;                          // Increase sequence size
        return insertedPosition;
    }
    
    Node* p = head;        // Start at first node
    
    for ( ; p != nullptr ; p = p->next, insertedPosition++) // Go to position that new node will be inserted into and record the index
    {
        if ( newNode->nodeValue <= p->nodeValue) // If
        {
            break;
        }
    }
    
    if (p == head) // If new node should be inserted at very beginning of linked list
    {
        newNode->next = p;          // Set new node's successor
        newNode->prev = nullptr;    // Set new node's predecessor
        p->prev = newNode;          // Connect current head's predecessor to be the inserted node
        head = newNode;             // Establish new head
        sequenceSize++;             // Increase sequence size
        return insertedPosition;
    }
    else if (p == nullptr) // If new node should be inserted at very end of linked list
    {
        newNode->next = nullptr;    // Set new node's successor
        newNode->prev = tail;       // Set new node's predecessor
        tail->next = newNode;       // Establish current tail's successor to be the inserted node
        tail = newNode;             // Establish new tail
        sequenceSize++;             // Increase sequence size
        return insertedPosition;
    }
    else // Otherwise insert new node between beginning and end
    {
        newNode->next = p;          // Set new node's successor
        newNode->prev = p->prev;    // Set new node's predecessor
        p->prev->next = newNode;    // Connect before node's sucessor to be new node
        p->prev = newNode;          // Connect next node's predecessor to be new node
        sequenceSize++;             // Increase sequence size
        return insertedPosition;
    }
}

// ERASE ( POS )
bool Sequence::erase(int pos){
    if ( pos < 0  ||  pos >= size() || size() == 0) // Bounds check
    {
        return false;
    }
    
    if ( size() == 1 )  // Only one node needs to be removed
    {
        sequenceSize--; // Decrease the sequence size
        delete head;    // Only node is removed
        head = tail = nullptr;  // Indicate that there are 0 nodes
        return true;
    }
    
    Node* p = head; // Go to first node
    for (int i = 0; p != nullptr && i < pos; p=p->next, i++) // Go through the node until you reach position you want
    {
        ;
    }
    
    if ( p == head && size() > 1 )      // If head needs to be removed
    {
        Node* toBeDeleted = p;          // Will hold the node that will be deleted
        //p = head->next;                 // Point to the next node (which will be the new head later)
        head->next->prev = nullptr;     // Establish new head's predecessor
        head = head->next;              // Establish new head
        delete toBeDeleted;             // Delete the node
        sequenceSize--;                 // Decrease sequence size
        return true;
    }
    else if ( p == tail && size() > 1 ) // If tail needs to be removed
    {
        Node* toBeDeleted = p;          // Will hold node that will be deleted
        //p = tail->prev;                 // Point to the previous node (which will be the new tail later)
        tail->prev->next = nullptr;     // Establish new tail's sucessor
        tail = tail->prev;              // Establish new tail
        delete toBeDeleted;             // Delete the node
        sequenceSize--;                 // Decrease sequence size
        return true;
    }
    else        // Delete the node p is currently on
    {
        Node* toBeDeleted = p;          // Will hold node that will be deleted
        p->prev->next = p->next;        // Establish previous node's new sucessor
        p->next->prev = p->prev;        // Establish next node's predecessor
        //p = p->prev;                    // Point one node before
        delete toBeDeleted;             // Delete the node
        sequenceSize--;                 // Decrease sequence size
        return true;
    }
}


// REMOVE (VALUE )
int Sequence::remove(const ItemType& value){
    
    int removedItems = 0; // How many items get removed

    if (sequenceSize == 0) // No items to remove
    {
        return removedItems;
    }

    Node* p = head;                         // Go to first node

    while (p != nullptr)                    // Iterate through nodes
    {
        if (value == p->nodeValue)          // Found node you want to remove
        {
            if ( p == head )                // If head node being removed
            {
                head = p->next;             // Officially establish new head
            }
            else if ( p == tail)            // If tail node being removed
            {
                p->prev->next = nullptr;    // Set new tail's successor to be nullptr
                tail = p->prev;             // Officially establish new tail
            }
            else                            // Other nodes
            {
            p->prev->next = p->next;        // Disconnect next pointer from node being removed
            p->next->prev = p->prev;        // Disconnect previous pointer from node being removed
            }

            Node* toBeDeleted = p;          // Temp pointer that will point at node being deleted
            p = p->next;                    // Move p pointer to the next node before deleting
            delete toBeDeleted;             // Delete the node
            removedItems++;                 // Indicate that node has been removed
            sequenceSize--;                 // Decrease the sequence size
        }
        else
        {
            p = p->next; // Move to the next node if current node is not removed
        }
    }

    return removedItems;
    
}

// GET ( POS, EXTERNALVALUE )
bool Sequence::get(int pos, ItemType& value) const{
    if ( pos < 0  ||  pos >= size() ) // Bounds check
    {
        return false;
    }
    
    Node* p = head;
    for (int i = 0; p != nullptr && i < pos; p=p->next, i++) // Go through the node until you reach position you want
    {
        ;
    }
    value = p->nodeValue; // Replace the value you inputted with the value from the node found
    
    return true;
}

// SET ( POS, DESIREDVALUE )
bool Sequence::set(int pos, const ItemType& value){
    
    if ( pos < 0  ||  pos >= size() || size() == 0 ) // Bounds check
    {
        return false;
    }
    
    Node* p = head; // Point to first node
    
    for (int i = 0; p != nullptr && i < pos ; p = p->next, i++) // Loop through all the nodes until you reach desired position
    {
        ;
    }
    
    p->nodeValue = value; // Set the node's value to the value you want
    return true;
}

// FIND ( VALUE )
int Sequence::find(const ItemType& value) const{
    
    int pos = 0;                                // Keep track of current position
    bool found = false;                         // Found a match or not?
    
    Node* p = head; // Point to first node
    for ( ; p != nullptr ; p = p->next, pos++)  // Loop through all the nodes
    {
        if (p->nodeValue == value) // If the value of current node matches your value, stop iterating
        {
            found = true; // Indicate that there is indeed a match
            break;
        }
    }
    
    if (found == false) // If no match found, return -1
    {
        return -1;
    }
    
    return pos; // Return the position found
}

// SWAP
void Sequence::swap(Sequence& other)
{
    // Swap sequence sizes
    int tempSize = other.size(); // Store other's size
    other.sequenceSize = sequenceSize; // Replace other's size with current's size
    sequenceSize = tempSize; // Replace current's size with other's size (stored in a temp)
    
    // Swap heads
    Node* tempHead = other.head; // Store other's head
    other.head = head; // Replace other's head with current head
    head = tempHead; // Replace current's head with other's head (stored in a temp)
    
    // Swap tails
    Node* tempTail = other.tail; // Store other's tail
    other.tail = tail; // Replace other's tail with current's tail
    tail = tempTail; // Replace current's tail with other's tail (stored in a temp)
    
}

void Sequence::dump() const
{
    if (size() == 0)
    {
        std::cerr << "EMPTY" << std::endl;
        return;
    }
    else
    {
        Node* p = head;
        
        while ( p!= nullptr )
        {
            std::cerr << p->nodeValue << " ";
            p = p->next;
        }
        std::cerr << std::endl;
    }
}


///////////////////////////////////////////////////////////
// Constructors
///////////////////////////////////////////////////////////

// DEFAULT CONSTRUCTOR
Sequence::Sequence()
: sequenceSize(0) {
    head = tail = nullptr; // Creates sequence with 0 "realized" values
}
    

// COPY CONSTRUCTOR
Sequence::Sequence(const Sequence& other)
: sequenceSize( other.size() ) {
    
    if (other.head == nullptr) // Edge case for if other sequence is empty
    {
        head = tail = nullptr;
        return;
    }
    
    head = new Node;                            // Create new node
    head->nodeValue = other.head->nodeValue;    // Equalize head values
    head->next = head->prev = nullptr;          // Initialize next and previous node pointers
    tail = head;                                // Equalize tail and head since only 1 node currently

    Node* pOther = other.head->next; // Iterate through nodes in original list (starting from the second node)
    Node* p = head; // Keep track of last node in the new linked list

    while (pOther != nullptr)                    // As long as not at end of other linked list
    {
        Node* newNode = new Node;                // Create new node and copy value from other node into new node
        newNode->nodeValue = pOther->nodeValue;
        newNode->next = nullptr;                 // Next pointer will be nullptr b/c last node currently
        newNode->prev = p;                       // Set prev pointer to last node in new linked list

        p->next = newNode; // Next pointer of last node in new linked list will point to newly created node
        p = newNode; // Point to newly created node
        tail = newNode; // Tail points to newly created node at end of linked list

        pOther = pOther->next; // Go to next node in other linked list
    }
}
    

// ASSIGNMENT OPERATOR
Sequence& Sequence::operator=(const Sequence& rhs){
    if (this != &rhs) // If not equal
    {
        Sequence temp(rhs); // Create a temporary sequence with exact characteristics of righthand side sequence
        swap(temp); // Put temporary sequence into the one you want
        sequenceSize = rhs.size(); // Copy over size
    }
    return *this;
}
    

// DESTRUCTOR
Sequence::~Sequence(){
    if ( sequenceSize == 0 ) // If sequence empty no need to delete
    {
        return;
    }
    
    if ( sequenceSize == 1 ) // If only one node, delete the single node
    {
        delete head;
        sequenceSize--; // Decrease sequence size to 0
        return;
    }
    
    Node* p = head; // Point to first node
    while ( p != nullptr && p != tail) // While pointer hasn't reached the last node
    {
        p = p->next;        // Go to the next node
        delete p->prev;     // Delete the previous node
    }
    delete tail;            // Then delete the remaining node
}
    
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    
    int subsequenceStartPos = -1;
    if (seq2.size() == 0 || seq2.size() > seq1.size() ) // Bounds check
    {
        return subsequenceStartPos;
    }
    
    for ( int i = 0; i < seq1.size() ; i++ ) // Go through seq1
    {
        int j = 0; // Index for going through seq2
        
        for ( ; j < seq2.size() ; j++ ) // Go through seq2
        {
            subsequenceStartPos = i;            // Set subsequence start position preemptively
            ItemType seq1Compare, seq2Compare;  // Get temp variable to compare seq1 and seq2 values
            seq1.get(i + j, seq1Compare);       // Get value from seq1
            seq2.get(j, seq2Compare);           // Get value from seq2
            
            if ( seq1Compare != seq2Compare )   // If no match at current corresponding indices, break iteration
            {
                break;
            }
        }
        
        
        if ( j == seq2.size() )                 // If able to iterate through seq2 entirely, then subsequence found
        {
            return subsequenceStartPos;
        }
    }
    
    return -1; // If no subsequence found
    
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    // Make temp sequence to later copy into result
    Sequence tempSeq;
    
    // Insert seq1 into temp sequence while also reversing
    for (int i = 0; i < seq1.size(); i++)   // Iterate through seq1 values
    {
        ItemType temp;                      // Temporarily store value to be copied over
        seq1.get(i, temp);                  // Get the value from seq1
        tempSeq.insert(0, temp);             // Append the value into beginning of temp sequence
        
    }
    
    // Insert seq2 into temp sequence after seq1 while also reversing
    for (int i = 0; i < seq2.size(); i++)   // Iterate through seq2 values
    {
        ItemType temp;                      // Temporarily store value to be copied over
        seq2.get(i, temp);                  // Get the value from seq2
        tempSeq.insert(seq1.size(), temp);   // Append the value into temp sequence AFTER position where seq1 finished
    }
    
    // Put the temp sequence into the result sequence you want
    tempSeq.swap( result );
}





