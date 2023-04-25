//
//  main.cpp
//  Project 2
//
//  Created by Timothy Liu on 4/19/23.
//

#include <iostream>
#include <cassert>
#include "Sequence.h"

using namespace std;

#define CHECKTYPE(c, f, r, a)  \
        {  \
         static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
             "You did not declare " #c "::" #f " as the Project 2 spec does");  \
         auto p = static_cast<r (c::*)a>(&c::f);  \
         (void) p;  \
        }
        #define CHECKTYPENONMEMBER(f, r, a)  \
        {  \
         static_assert(std::is_same<decltype(&f), r (*)a>::value, \
             "You did not declare " #f " as the Project 2 spec does");  \
         auto p = static_cast<r (*)a>(f);  \
         (void) p;  \
        }

        static_assert(std::is_default_constructible<Sequence>::value,
                "Sequence must be default-constructible.");
        static_assert(std::is_copy_constructible<Sequence>::value,
                "Sequence must be copy-constructible.");
        static_assert(std::is_copy_assignable<Sequence>::value,
                "Sequence must be assignable.");

        void thisFunctionWillNeverBeCalled()
        {
            CHECKTYPE(Sequence, empty,  bool, () const);
            CHECKTYPE(Sequence, size,   int,  () const);
            CHECKTYPE(Sequence, erase,  bool, (int));
            CHECKTYPE(Sequence, remove, int,  (const ItemType&));
            CHECKTYPE(Sequence, get,    bool, (int, ItemType&) const);
            CHECKTYPE(Sequence, set,    bool, (int, const ItemType&));
            CHECKTYPE(Sequence, find,   int,  (const ItemType&) const);
            CHECKTYPE(Sequence, swap,   void, (Sequence&));
            CHECKTYPENONMEMBER(subsequence,   int,  (const Sequence&, const Sequence&));
            CHECKTYPENONMEMBER(concatReverse, void, (const Sequence&, const Sequence&, Sequence&));
            { auto p = static_cast<int (Sequence::*)(int, const ItemType&)>(&Sequence::insert); (void) p; }
            { auto p = static_cast<int (Sequence::*)(const ItemType&)>(&Sequence::insert); (void) p; }
        }

///////////////////////////////////////////
// Int Main
///////////////////////////////////////////

int main() {
    
    Sequence empty;
    assert( empty.size() == 0 && empty.empty() );            // Empty sequence
    assert( empty.erase(0) == false );      // Erasing from 0 size sequence
    assert( empty.remove("nothing") == 0 ); // Removing from 0 size sequence
    assert( empty.set(0, "Still nothing") == false ); // Setting value of empty sequence
    assert( empty.set(1, "Still nothing") == false ); // Setting value out of bounds
    
    Sequence noLongerEmpty(empty);          // Copy constructor on empty sequence
    assert( noLongerEmpty.size() == 0);     // Check if size same
    
    Sequence a;
    assert( a.insert("c") == 0);    // Insert without position
    assert( a.insert("a") == 0);    // Alphanumerical insertion
    assert( a.insert("b") == 1);    // Alphanumerical insertion
    assert( a.size() == 3 );        // Size after insertion
    assert( a.empty() == false );   // Empty or not after insertion
    
    Sequence b;
    b = a; // Assignment operator
    assert( b.size() == 3 );        // Check size after assignment
    assert( b.find("c") == 2 );     // Check whether sequence still the same after assignment
    assert( b.find("b") == 1 );
    assert( b.find("a") == 0 );
    assert( b.set(0, "1") == true ); // Setting 0th position
    assert( b.size() == 3 );         // Check size
    assert( b.insert(0, "2") == 0 ); // Insert new value into new sequence object
    assert( a.find("a") == 0 );      // Check if original sequence isn't altered
    assert( b.erase(0) == true);     // Erase from sequence size larger than 1
    assert( b.erase(0) == true);
    assert( b.erase(1) == true);    // Erase last value from sequence
    assert( b.erase(0) == true);    // Erase from sequence size == 1
    assert( b.size() == 0 );
    
    Sequence c(a);                  // Copy constructor on non-empty sequence
    assert( c.size() == a.size() );
    assert( c.set(1, "b") == true);
    assert( c.set(2, "a") == true); // Setting tail value
    assert( c.remove("a") == 2);    // Remove multiple values
    assert( c.size() == 1 );        // Check size after removing
    
    Sequence d;
    assert( d.insert(0, "First") == 0 );   // Insert when position == size
    assert( d.insert(1, "Second") == 1 );  // Insert when position == size
    assert( d.insert(2, "Third") == 2 );   // Insert when position == size
    assert( d.insert(3, "Fourth") == 3 );  // Insert when position == size
    d.swap(d);                             // Swapping with self
    assert( d.size() == 4 );               // Check size after swapping with self
    d.swap(a);                             // Swap with another sequence
    assert( d.size() == 3 );               // Check size after swapping with another sequence
    assert( a.size() == 4 );
    assert( d.find("First") == -1);        // Check for new values in swapped sequences
    assert( a.find("First") == 0);
    assert( d.find("a") == 0 );
    assert( d.find("Second") == -1);        // Check for new values in swapped sequences
    assert( a.find("Second") == 1);
    assert( d.find("b") == 1 );
    assert( d.set(0, "1") == true );
    assert( d.set(1, "2") == true );
    assert( d.set(2, "3") == true );
    assert( a.find("1") == -1 );            // Check if swapped sequences don't share same address
    ItemType willBeOverwritten = "Replace me";
    assert( d.get(0, willBeOverwritten) == true ); // Get value
    assert( willBeOverwritten == "1" );
    ItemType wontBeOverwritten = "Unchanged";
    assert( d.get(-1, wontBeOverwritten) == false ); // Get function on out of bounds position
    assert( d.get(4, wontBeOverwritten) == false ); // Get function on out of bounds position
    assert( wontBeOverwritten == "Unchanged" );
    
    Sequence First;
    assert( First.insert(0,"a") == 0 );
    assert( First.insert(0,"b") == 0 );
    assert( First.insert(0,"c") == 0 );
    
    Sequence Second;
    assert( Second.insert(0,"d") == 0 );
    assert( Second.insert(0,"e") == 0 );
    assert( Second.insert(0,"f") == 0 );
    
    Sequence Result;
    
    concatReverse(First, Second, Result);
    assert( Result.size() == First.size() + Second.size() ); // Check result size
    assert( Result.find("a") == 0 ); // Check if result sequence is concatenated and reversed
    assert( Result.find("b") == 1 );
    assert( Result.find("c") == 2 );
    assert( Result.find("d") == 3 );
    assert( Result.find("e") == 4 );
    assert( Result.find("f") == 5 );
    
    Sequence Single;
    Sequence SingleResult;
    assert( Single.insert(0,"c") == 0 );
    assert( Single.insert(0,"a") == 0 );
    assert( Single.insert(0,"t") == 0 );
    concatReverse(Single, Single, SingleResult); // Call concatReverse with the same sequence
    assert( SingleResult.size() == 6);           // Check size after concatReverse
    assert( SingleResult.find("c") == 0 );
    assert( SingleResult.find("a") == 1 );
    assert( SingleResult.find("t") == 2 );
    assert( SingleResult.remove("c") == 2 ); // Removing after concatReverse on same object
    assert( SingleResult.remove("a") == 2 );
    assert( SingleResult.remove("t") == 2 );
    
    
    Sequence EmptyConcat;
    Sequence EmptyConcatResult;
    concatReverse(EmptyConcat, EmptyConcat, EmptyConcatResult); // concatReverse on empty sequence
    assert( EmptyConcatResult.size() == 0 );    // Check size after concatReverse on empty sequence
    
    Sequence NotEmptyConcat;
    assert( NotEmptyConcat.insert("A") == 0 );
    concatReverse(EmptyConcat, NotEmptyConcat, EmptyConcatResult); // concatReverse on empty sequence and non empty sequence
    assert( EmptyConcatResult.size() == 1 );  // Check size
    assert( EmptyConcatResult.find("A") == 0 ); // Check original non empty sequence
    
    Sequence sameConcat1;
    sameConcat1.insert(0,"d");
    sameConcat1.insert(0,"o");
    sameConcat1.insert(0,"g");
    assert( sameConcat1.size() == 3 );
    concatReverse(sameConcat1, sameConcat1, sameConcat1); // Using same sequence for seq1, seq2, and result
    assert( sameConcat1.size() == 6 ); // Size check for after concatReversing the same sequence
    
    // Check if sequence is correct after concatReversing the same sequence
    ItemType comparing;
    sameConcat1.get(0,comparing);
    assert( comparing == "d" );
    sameConcat1.get(1,comparing);
    assert( comparing == "o" );
    sameConcat1.get(2,comparing);
    assert( comparing == "g" );
    sameConcat1.get(3,comparing);
    assert( comparing == "d" );
    sameConcat1.get(4,comparing);
    assert( comparing == "o" );
    sameConcat1.get(5,comparing);
    assert( comparing == "g" );
    
    
    for (int i = 0; i < 6; i++)
    {sameConcat1.erase(0);}
    sameConcat1.insert(0,"d");
    sameConcat1.insert(0,"o");
    sameConcat1.insert(0,"g");
    
    Sequence sameConcat2;
    sameConcat2.insert(0,"f");
    sameConcat2.insert(0,"r");
    sameConcat2.insert(0,"o");
    sameConcat2.insert(0,"g");
    
    concatReverse(sameConcat1, sameConcat2, sameConcat1); // concatReverse where result is one of the sequences you're reversing
    
    assert( sameConcat1.size() == 7 ); // Check size of result sequence
    sameConcat1.get(0,comparing); // Check result sequence
    assert( comparing == "d" );
    sameConcat1.get(1,comparing);
    assert( comparing == "o" );
    sameConcat1.get(2,comparing);
    assert( comparing == "g" );
    sameConcat1.get(3,comparing);
    assert( comparing == "f" );
    sameConcat1.get(4,comparing);
    assert( comparing == "r" );
    sameConcat1.get(5,comparing);
    assert( comparing == "o" );
    sameConcat1.get(6,comparing);
    assert( comparing == "g" );
    
    assert( sameConcat2.size() == 4 ); // Check that other sequence hasn't been altered
    sameConcat2.get(3,comparing);
    assert( comparing == "f" );
    sameConcat2.get(2,comparing);
    assert( comparing == "r" );
    sameConcat2.get(1,comparing);
    assert( comparing == "o" );
    sameConcat2.get(0,comparing);
    assert( comparing == "g" );
    
    Sequence largeSequence;
    assert( largeSequence.insert(0,"c") == 0);
    assert( largeSequence.insert(0,"b") == 0);
    assert( largeSequence.insert(0,"a") == 0);
    assert( largeSequence.insert(0,"z") == 0);
    assert( largeSequence.insert(0,"d") == 0);
    assert( largeSequence.insert(0,"c") == 0);
    assert( largeSequence.insert(0,"b") == 0);
    assert( largeSequence.insert(0,"a") == 0);
    
    Sequence smallerSequence;
    assert( smallerSequence.insert(0, "c") == 0 );
    assert( smallerSequence.insert(0, "b") == 0 );
    assert( smallerSequence.insert(0, "a") == 0 );
    
    assert( subsequence(largeSequence, smallerSequence) == 0 ); // Sequence "abc" is first found in index 0 even though there are 2 "abc"s
    assert( subsequence(smallerSequence, largeSequence) == -1 ); // Subsequence is larger than sequence you're looking through
    assert( subsequence(largeSequence, largeSequence) == 0 );    // Inputting same sequence
    assert( largeSequence.insert(1,"z") == 1);
    assert( subsequence(largeSequence, smallerSequence) == 6 );  // Non consecutive subsequence comes before consecutive sequence
    
    Sequence emptySubSequence;
    
    assert( subsequence(largeSequence, emptySubSequence) == -1 ); // Empty subsequence
    assert( subsequence(emptySubSequence, emptySubSequence) == -1 ); // Both sequences empty
    assert( subsequence(emptySubSequence, smallerSequence) == -1 ); // Empty sequence
    
    
    // Test 1: Empty sequence and single value sequence
    Sequence s1;
    assert(s1.empty() && s1.size() == 0);
    assert(s1.insert(0, "apple") == 0);
    assert(!s1.empty() && s1.size() == 1);

    // Test 2: Insert at various positions
    Sequence s2;
    assert(s2.insert(0, "apple") == 0);
    assert(s2.insert(1, "banana") == 1);
    assert(s2.insert(0, "orange") == 0);
    assert(s2.insert(3, "grape") == 3);
    assert(s2.size() == 4);

    // Test 3: Erase from various positions
    Sequence s3;
    s3.insert("apple");
    s3.insert("banana");
    s3.insert("orange");
    s3.insert("grape");
    assert(s3.erase(0));
    assert(s3.erase(2));
    assert(s3.size() == 2);
    std::string value3;
    s3.get(0, value3);
    assert(value3 == "banana");
    s3.get(1, value3);
    assert(value3 == "grape");

    // Test 4: Remove all occurrences of a specific value
    Sequence s4;
    s4.insert("apple");
    s4.insert("banana");
    s4.insert("apple");
    s4.insert("orange");
    s4.insert("apple");
    assert(s4.remove("apple") == 3);
    assert(s4.size() == 2);
    std::string value4;
    s4.get(0, value4);
    assert(value4 == "banana");
    s4.get(1, value4);
    assert(value4 == "orange");

    // Test 5: Find value
    Sequence s5;
    s5.insert("apple");
    s5.insert("banana");
    s5.insert("orange");
    s5.insert("grape");
    assert(s5.find("apple") == 0);
    assert(s5.find("banana") == 1);
    assert(s5.find("grape") == 2);
    assert(s5.find("orange") == 3);
    assert(s5.find("kiwi") == -1);

    // Test 6: Swap two sequences
    Sequence s6;
    s6.insert("apple");
    s6.insert("banana");
    Sequence s7;
    s7.insert("orange");
    s7.insert("grape");
    s6.swap(s7);
    assert(s6.size() == 2);
    assert(s6.find("orange") == 1);
    assert(s6.find("grape") == 0);
    assert(s7.size() == 2);
    assert(s7.find("apple") == 0);
    assert(s7.find("banana") == 1);

    // Test 7: Set value at a specific position
    Sequence s8;
    s8.insert("apple");
    s8.insert("banana");
    s8.insert("orange");
    std::string value8;
    assert(s8.set(1, "grape"));
    s8.get(1, value8);
    assert(value8 == "grape");
    assert(!s8.set(3, "kiwi"));

    // Test 8: Get value from an empty sequence
    Sequence s9;
    std::string value9;
    assert(!s9.get(0, value9));
    
    cerr << "PASSED TESTS" << endl;
    return 0;
}
