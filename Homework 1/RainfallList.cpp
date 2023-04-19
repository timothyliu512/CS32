//
//  RainfallList.cpp
//  Homework 1
//
//  Created by Timothy Liu on 4/17/23.
//

#include "RainfallList.h"
#include <iostream>

// The words for and while must not appear in RainfallList.h or RainfallList.cpp, except perhaps in the implementations of RainfallList::minimum and RainfallList::maximum. The characters [ (open square bracket) and * must not appear in RainfallList.h or RainfallList.cpp except in comments if you wish. You do not have to change unsigned long to ItemType in RainfallList.h and RainfallList.cpp if you don't want to (since unlike Sequence, which is designed for a wide variety of item types, RainfallList is specifically designed to work with unsigned longs). In the code you turn in, RainfallList's member functions must not call Sequence::dump.

RainfallList::RainfallList() : mRainfallSequence() {
    
    
}      // Create an empty rainfall list.

bool RainfallList::add(unsigned long rainfall) {
    
    if (rainfall > 400 || mRainfallSequence.size() > DEFAULT_MAX_ITEMS )
    {
        return false;
    }
    
    int lastPos = mRainfallSequence.size(); // Find the last position in sequence
    mRainfallSequence.insert(lastPos, rainfall); // Insert rainfall to last position
    return true;
}
  // If the rainfall is valid (a value from 0 to 400) and the rainfall list
  // has room for it, add it to the rainfall list and return true.
  // Otherwise, leave the rainfall list unchanged and return false.

bool RainfallList::remove(unsigned long rainfall) {
    
    if (mRainfallSequence.find(rainfall) == -1) // If can't find specified rainfall, don't do anything
    {
        return false;
    }
    
    int pos = mRainfallSequence.find(rainfall); // Find position of specified rainfall
    mRainfallSequence.erase(pos); // Erase that one instance of specified rainfall
    return true;
}
  // Remove one instance of the specified rainfall from the rainfall list.
  // Return true if a rainfall was removed; otherwise false.

int RainfallList::size() const {
    
    return mRainfallSequence.size();
}  // Return the number of rainfalls in the list.



unsigned long RainfallList::minimum() const {
    
    if (mRainfallSequence.size() == 0)
    {
        return NO_RAINFALLS;
    }
    
    unsigned long currentMinValue; // Smallest sequence value found
    unsigned long tempMinValue; // Current sequence value
    
    mRainfallSequence.get(0,currentMinValue); // Assigns 0th index value to be minimum

    for (int i = 0; i < mRainfallSequence.size(); i++)
    {
        mRainfallSequence.get(i,tempMinValue); // Get current sequence value
        
        if ( tempMinValue < currentMinValue ) // If current value is less than min value, replace it
        {
            currentMinValue = tempMinValue;
        }
    }
    
    return currentMinValue;
}
  // Return the lowest-valued rainfall in the rainfall list.  If the list is
  // empty, return NO_RAINFALLS.

unsigned long RainfallList::maximum() const {

    
    if (mRainfallSequence.size() == 0)
    {
        return NO_RAINFALLS;
    }
    
    unsigned long currentMaxValue; // Smallest sequence value found
    unsigned long tempMaxValue; // Current sequence value
    
    mRainfallSequence.get(0,currentMaxValue); // Assigns 0th index value to be minimum

    for (int i = 0; i < mRainfallSequence.size(); i++)
    {
        mRainfallSequence.get(i,tempMaxValue); // Get current sequence value
        
        if ( tempMaxValue > currentMaxValue ) // If current value is less than min value, replace it
        {
            currentMaxValue = tempMaxValue;
        }
    }
    
    return currentMaxValue;
}
  // Return the highest-valued rainfall in the rainfall list.  If the list is
  // empty, return NO_RAINFALLS.


