//
//  testRainfallList.cpp
//  Homework 1
//
//  Created by Timothy Liu on 4/17/23.
//

#include <string>
#include <iostream>
#include <cassert>
#include "RainfallList.h"

using namespace std;

int main() {
    
    RainfallList test;
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        test.add(10);
    }
    
    test.minimum();
    test.maximum();
    
    test.remove(10);
    std::cerr << "end: "<< test.size() << endl;
    
    test.add(20);
    
    RainfallList test2;
    
    assert( test2.minimum() == NO_RAINFALLS);
    
    test2.add(10);
    test2.add(30);
    test2.add(15);
    test2.add(10);
    
    assert( test2.size() == 4 );
    assert( test2.minimum() == 10);
    assert( test2.maximum() == 30);
    assert ( test2.remove(510) == false);
    assert ( test2.size() == 4);
    assert ( test2.remove(10) == true);
    assert ( test2.size() == 3);
    test2.remove(30);
    test2.remove(15);
    test2.remove(10);
    assert(test2.size() == 0);
    assert(test2.minimum() == NO_RAINFALLS);
    assert(test2.maximum() == NO_RAINFALLS);
    test2.add(20);
    assert( test2.size()==1 );
    assert( test2.minimum() == test2.maximum());
    test2.add(20);
    assert( test2.minimum() == test2.maximum());
    test2.add(30);
    assert( test2.minimum() ==20);
    assert( test2.maximum() ==30);
    
    for(int i = 0; i < 160; i++)
    {
        test2.add( i );
    }
    assert( test2.size() == 160);
    assert( test2.minimum() == 0);
    assert( test2.maximum() == 156);
    
    cout << "Passed Rainfall"<<endl;
    
    return 0;
}



