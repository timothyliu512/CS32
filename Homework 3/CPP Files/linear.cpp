//
//  linear.cpp
//  Homework 3
//
//  Created by Timothy Liu on 5/6/23.
//

// NO #Include directives
// No using namespace std;
// NO main routine
// No implementation of somePredicate

#include <string>
#include <iostream>
#include <cassert>

using namespace std;

bool somePredicate(string s);
bool allTrue(const string a[], int n);
int countTrue(const string a[], int n);
int firstTrue(const string a[], int n);
int positionOfMax(const string a[], int n);
bool contains(const string a1[], int n1, const string a2[], int n2);


int main()
{
    return 1;
}


bool somePredicate(string s)
{
    return s == "a";
    
//    return s.empty();
    
}

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    if ( n <= 0 )
    {
        return true;
    }
    
    
    if( somePredicate( a[n-1] ) == false )
    {
        return false;
    }
    
    else
    {
        return allTrue( a , n-1 );
    }
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const string a[], int n)
{
    if ( n <= 0 )
    {
        return 0;
    }
    
    if ( somePredicate(a[n-1]) )
    {
        return countTrue( a, n-1 ) + 1;
    }
        
    else
    {
        return countTrue( a, n-1 );
    }
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const string a[], int n)
{
    if ( n <= 0 )
    {
        return -1;
    }
    
    if ( n == 1 )
    {
        if (somePredicate(a[0]))
        {
            return 0;
        }
        else
        {
            return -1;
        }
        
    }

    if ( firstTrue(a, n-1) == -1 )
    {
        if ( somePredicate(a[n-1]))
        {
            return n-1;
        }
    
        else
        {
            return -1;
        }
    }
    
    return firstTrue(a, n - 1);
    
}


// Return subscript of the first string in the array that is >= all
// strings in the array (i.e., return the smallest subscript m such
// that a[m] >= a[k] for all k from 0 to n-1).  If the function is told that no strings are to be considered to be in the array, return -1.
int positionOfMax(const string a[], int n)
{
    if ( n <= 0 )
    {
        return -1;
    }
    
    if ( n == 1 )
    {
        return 0;
    }
    
    int maxPos = positionOfMax(a, n-1);
    
    if( a[maxPos] < a[n-1] )
    {
        return n-1;
    }
    else
    {
        return maxPos;
    }
}

bool contains(const string a1[], int n1, const string a2[], int n2)
{
    
    if ( n2 > n1 )
    {
        return false;
    }
    
    if( (n2 == 0 && n1 == n2) ||  (n2 <= 0) )
    {
        return true;
    }
    
    if (a1[n1-1] == a2[n2-1])
    {
        return contains(a1, n1-1, a2, n2-1);
    }
    else
    {
        return contains(a1, n1-1, a2, n2);
    }
    
}
