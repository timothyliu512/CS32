//
//  testSequence.cpp
//  Homework 1
//
//  Created by Timothy Liu on 4/13/23.
//

#include <iostream>
#include "Sequence.h"

using namespace std;

int main() {
    Sequence s;
            s.insert(0, 1);
            s.insert(1, 2);
            s.insert(2, 5);
            s.insert(3, 2);
            s.insert(4, 3);
            assert(s.remove(2) == 2);
            assert(s.size() == 3);
            ItemType x;
            assert(s.get(0, x)  &&  x == 1);
            assert(s.get(1, x)  &&  x == 5);
            assert(s.get(2, x)  &&  x == 3);
    Sequence s2;
            assert(s2.empty());
            assert(s2.find(42) == -1);
            assert(s2.insert(42) == 0);
            assert(s2.size() == 1  &&  s2.find(42) == 0);
    
    Sequence s1;
            s1.insert(0, 123);
            s1.insert(0, 567);
            Sequence s3;
            s3.insert(0, 888);
            s1.swap(s3);
            assert(s1.size() == 1  &&  s1.find(888) == 0  &&  s3.size() == 2  &&
                        s3.find(567) == 0  &&  s3.find(123) == 1);
    
    Sequence sTest;
            sTest.insert(0, 1);
            sTest.insert(1, 2);
            sTest.insert(2, 0);
            sTest.insert(3, 3);
            assert(sTest.find(0) == 2);
            sTest.remove(1);
            assert(sTest.size() == 3  &&  sTest.find(2) == 0  &&  sTest.find(0) == 1  &&
                        sTest.find(3) == 2);
    
    Sequence a;   // a can hold at most 1000 items
    for (int i = 0; i < 9; i++)
    {
        a.insert(0);
    }
    Sequence b;      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 20;

               // No failures inserting 5 items into b
            for (int k = 0; k < 5; k++)
                 assert(b.insert(v) != -1);

               // When two Sequences' contents are swapped, their capacities are
               // swapped as well:
            a.swap(b);
            assert(b.size() ==9);
            assert(a.size() == 5);
    
    Sequence sTest2;
            assert(sTest2.empty());
            assert(sTest2.find(42) == -1);
            assert(sTest2.insert(42) == 0);
            assert(sTest2.size() == 1  &&  sTest2.find(42) == 0);
    
    Sequence aa;
            assert(aa.set(0, 90)==false);
            aa.dump();
            
            aa.insert(20);
            aa.insert(30);
            aa.insert(40);
            aa.insert(50);
            aa.insert(10);
            
            assert( aa.size() ==5);
            assert( aa.remove(10)==true);
            assert( aa.remove(10)==false);
            assert( aa.find(20) == 0);
            assert( aa.erase(0)==true);
            assert( aa.find(30) == 0);
            assert( aa.size() == 3);
            assert( aa.erase(0)==true);
            assert( aa.erase(0)==true);
            assert( aa.erase(0)==true);
            assert( aa.erase(0)==false);
            assert( aa.size()==0);
            assert( aa.empty()==true);
            assert( aa.remove(0)==false);
            assert(aa.set(0, 20)==false);
            
    Sequence bb;
            for (int i = 0; i < 159; i++)
            {
                bb.insert(i, i+1);
            }
            assert( bb.size() == 159);
            assert( bb.insert(159, 90) == 159);
            assert( bb.size() == 160);
            
            unsigned long testVar = 230;
            
            assert(bb.get(0,testVar)==true);
            assert(testVar == 1);
            assert(bb.set(0,230)==true);
            assert(bb.size()==160 && bb.size()==DEFAULT_MAX_ITEMS);
    
    Sequence bb2 = bb;
            
            assert(bb2.size()==160);
            assert(bb2.find(230)==0);
            //bb.dump();
            assert( bb2.find(230)==0 );
            assert(bb2.find(160)==-1);
            
            for (int i = 0; i < 160; i++)
            {
                bb2.erase(0);
            }
            bb2.dump();
    
    Sequence cc;
            for (int i = 0; i < 160; i++)
            {
                cc.insert(0, 160-i-1);
            }
            
            assert(cc.find(159)==159);
            
            for (int i = 0; i < 160; i++)
            {
                cc.remove(i);
            }
            
            for (int i = 0; i < 10; i++)
            {
                cc.insert(i+1);
            }
            
            cc.remove(5);
            assert (cc.size()==9);
            cc.insert(5);
            assert (cc.size()==10);
            cc.insert(5);
            assert (cc.size()==11);
            cc.dump();
    
    Sequence idk;
        idk.insert(0, 10);
        idk.insert(0, 20);
        assert(idk.size() == 2);
        ItemType random = 999;
        assert(idk.get(0, random) && random == 20);
        assert(idk.get(1, random) && random == 10);
    
    Sequence Chris;
    
    for (int i = 190; i > 0; i--)
    {
        Chris.insert(i);
    }
    Chris.dump();
    
    Sequence Chandler = Chris;
    Chandler.dump();
    
    for (int i = 0; i < 190; i++)
    {
        Chandler.erase(0);
    }
    
    for (int i = 0; i < 190; i++)
    {
        Chandler.insert(0,i);
    }
    Chandler.dump();
    
    
    std::cerr << "Passed Sequence" << std::endl;
    return 0;
}
