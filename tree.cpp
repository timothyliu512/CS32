//
//  tree.cpp
//  Homework 3
//
//  Created by Timothy Liu on 5/7/23.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int countIncludes(const string a1[], int n1, const string a2[], int n2);
void separate(string a[],
              int n,
              string separator,
              int& firstNotLess,
              int& firstGreater);
void order(string a[], int n);

int main() {
    string a[7] = {"john","sonia","elena","ketanji","sonia","elena","samuel"};
    string b1[3] = {"john","ketanji","elena"}; // 1
    string b2[3] = {"john","elena","samuel"};  // 2
    string b3[3] = {"ketanji","john","elena"}; // 0
    string b4[3] = {"sonia","elena","samuel"}; // 3

    string nums[5] = {"2","3","1","4","5"};

    assert( countIncludes(a, 7, b1, 3) == 1);
    assert( countIncludes(a, 7, b2, 3) == 2);
    assert( countIncludes(a, 7, b3, 3) == 0);
    assert( countIncludes(a, 7, b4, 3) == 3);

    string banana[6] = {"b","a","n","a","n","a"};
    string an[2] = {"a","n"};
    assert( countIncludes(banana, 6, an, 2) == 3 );

    order(a, 7);

    for (int i = 0; i < 7; i++)
    {
        cout << a[i] << " ";
    }

    cout << endl;
    order(nums, 5);
    for (int i = 0; i < 5; i++)
    {
        cout << nums[i] << " ";
    }

    cout << endl;
    string ordered[5] = {"l","m","n","o","p"};
    order( ordered, 5);
    for (int i = 0; i < 5; i++)
    {
        cout << ordered[i] << " ";
    }


    cout << endl;
    string revOrdered[5] = {"z","y","x","w","v"};
    order( revOrdered, 5);
    for (int i = 0; i < 5; i++)
    {
        cout << revOrdered[i] << " ";
    }

    cout << endl;
    string same[5] = {"y","y","y","y","y"};
    order( same, 5);
    for (int i = 0; i < 5; i++)
    {
        cout << same[i] << " ";
    }

    cout << endl;
    string similar[5] = {"yes","yeah","yer","ye","yep"};
    order( similar, 5);
    for (int i = 0; i < 5; i++)
    {
        cout << similar[i] << " ";
    }

    cout << endl;

    cout << endl;
    
    string t1[9] = {"john", "sonia", "elena", "ketanji", "sonia", "elena", "samuel"};
        string t2[5] = { "john", "ketanji", "elena"};
        string t3[5] = {"john", "elena", "samuel"};
        string t4[5] = {"ketanji", "john", "elena"};
        string t5[5] = {"sonia", "elena", "samuel"};
        string t6[0];
        string t7[1] = {"bobo"};
        string t8[3] = {"gecs", "a92039e0"};
        assert(countIncludes(t1, 7, t2, 3) == 1);
        assert(countIncludes(t1, 7, t3, 3) == 2);
        assert(countIncludes(t1, 7, t4, 3) == 0);
        assert(countIncludes(t1, 7, t5, 3) == 3);
        order(t1, 0);
        assert(t1[0] == "john");
        assert(t1[1] == "sonia");
        assert(t1[2] == "elena");
        assert(t1[3] == "ketanji");
        assert(t1[6] == "samuel");
        order(t1, 1);
        assert(t1[0] == "john");
        assert(t1[1] == "sonia");
        assert(t1[2] == "elena");
        assert(t1[3] == "ketanji");
        assert(t1[6] == "samuel");
        order(t1, 3);
        assert(t1[0] == "elena");
        assert(t1[1] == "john");
        assert(t1[2] == "sonia");
        assert(t1[3] == "ketanji");
        assert(t1[6] == "samuel");
        order(t1, 5);
        assert(t1[0] == "elena");
        assert(t1[2] == "ketanji");
        assert(t1[4] == "sonia");
        assert(t1[5] == "elena");
        order(t1, 7);
        assert(t1[0] == "elena");
        assert(t1[1] == "elena");
        assert(t1[4] == "samuel");
        assert(t1[6] == "sonia");
        order(t6, 0);
        order(t7, 1);
        assert(t7[0] == "bobo");
        order(t8, 1);
        assert(t8[0] == "gecs");
        assert(t8[1] == "a92039e0");
        order(t8, 2);
        assert(t8[1] == "gecs");
        assert(t8[0] == "a92039e0");
        
        const int SIZE = 4;
           const int SIZE1 = 3;
           const int SIZE2 = 1;
           
           //single element cases
           string aaa[SIZE2] = {"a"};
           
           order(aaa, SIZE2);
           assert(aaa[0] == "a");

           //even elements cases
           string aa1[SIZE] = {"a", "b", "c", "d"};
           string aa2[SIZE] = {"a", "b", "d", "c"};
           string aa3[SIZE] = {"a", "c", "b", "d"};
           string aa4[SIZE] = {"a", "c", "d", "b"};
           string aa5[SIZE] = {"a", "d", "b", "c"};
           string aa6[SIZE] = {"a", "d", "c", "b"};
           
           string aa7[SIZE] = {"b", "a", "c", "d"};
           string aa8[SIZE] = {"b", "a", "d", "c"};
           string aa9[SIZE] = {"b", "c", "a", "d"};
           string aa10[SIZE] = {"b", "c", "d", "a"};
           string aa11[SIZE] = {"b", "d", "a", "c"};
           string aa12[SIZE] = {"b", "d", "c", "a"};
           
           string aa13[SIZE] = {"c", "a", "b", "d"};
           string aa14[SIZE] = {"c", "a", "d", "b"};
           string aa15[SIZE] = {"c", "b", "a", "d"};
           string aa16[SIZE] = {"c", "b", "d", "a"};
           string aa17[SIZE] = {"c", "d", "a", "b"};
           string aa18[SIZE] = {"c", "d", "b", "a"};
           
           string aa19[SIZE] = {"d", "a", "c", "b"};
           string aa20[SIZE] = {"d", "a", "b", "c"};
           string aa21[SIZE] = {"d", "b", "a", "c"};
           string aa22[SIZE] = {"d", "b", "c", "a"};
           string aa23[SIZE] = {"d", "c", "a", "b"};
           string aa24[SIZE] = {"d", "c", "b", "a"};
           
           //repeated cases
           string aa25[SIZE] = {"d", "d", "b", "a"};
           
           order(aa25, SIZE);
           assert(aa25[0] == "a" && aa25[1] == "b" && aa25[2] == "d" && aa25[3] == "d");
           
           //odd elements cases
           string a2[SIZE1] = {"a", "b", "c"};
           string a3[SIZE1] = {"a", "c", "b"};
           string a4[SIZE1] = {"c", "a", "b"};
           string a5[SIZE1] = {"c", "b", "a"};
           string a6[SIZE1] = {"b", "c", "a"};
           string a7[SIZE1] = {"b", "a", "c"};

           order(aa1, SIZE);
           assert(aa1[0] == "a" && aa1[1] == "b" && aa1[2] == "c" && aa1[3] == "d");
           
           order(aa2, SIZE);
           assert(aa2[0] == "a" && aa2[1] == "b" && aa2[2] == "c" && aa2[3] == "d");
           
           order(aa3, SIZE);
           assert(aa3[0] == "a" && aa3[1] == "b" && aa3[2] == "c" && aa3[3] == "d");
           
           order(aa4, SIZE);
           assert(aa4[0] == "a" && aa4[1] == "b" && aa4[2] == "c" && aa4[3] == "d");
           
           order(aa5, SIZE);
           assert(aa5[0] == "a" && aa5[1] == "b" && aa5[2] == "c" && aa5[3] == "d");
           
           order(aa6, SIZE);
           assert(aa6[0] == "a" && aa6[1] == "b" && aa6[2] == "c" && aa6[3] == "d");
           
           order(aa7, SIZE);
           assert(aa7[0] == "a" && aa7[1] == "b" && aa7[2] == "c" && aa7[3] == "d");
           
           order(aa8, SIZE);
           assert(aa8[0] == "a" && aa8[1] == "b" && aa8[2] == "c" && aa8[3] == "d");
           
           order(aa9, SIZE);
           assert(aa9[0] == "a" && aa9[1] == "b" && aa9[2] == "c" && aa9[3] == "d");
           
           order(aa10, SIZE);
           assert(aa10[0] == "a" && aa10[1] == "b" && aa10[2] == "c" && aa10[3] == "d");
           
           order(aa11, SIZE);
           assert(aa11[0] == "a" && aa11[1] == "b" && aa11[2] == "c" && aa11[3] == "d");
           
           order(aa12, SIZE);
           assert(aa12[0] == "a" && aa12[1] == "b" && aa12[2] == "c" && aa12[3] == "d");
           
           order(aa13, SIZE);
           assert(aa13[0] == "a" && aa13[1] == "b" && aa13[2] == "c" && aa13[3] == "d");
           
           order(aa14, SIZE);
           assert(aa14[0] == "a" && aa14[1] == "b" && aa14[2] == "c" && aa14[3] == "d");
           
           order(aa15, SIZE);
           assert(aa15[0] == "a" && aa15[1] == "b" && aa15[2] == "c" && aa15[3] == "d");
           
           order(aa16, SIZE);
           assert(aa16[0] == "a" && aa16[1] == "b" && aa16[2] == "c" && aa16[3] == "d");
           
           order(aa17, SIZE);
           assert(aa17[0] == "a" && aa17[1] == "b" && aa17[2] == "c" && aa17[3] == "d");
           
           order(aa18, SIZE);
           assert(aa18[0] == "a" && aa18[1] == "b" && aa18[2] == "c" && aa18[3] == "d");
           
           order(aa19, SIZE);
           assert(aa19[0] == "a" && aa19[1] == "b" && aa19[2] == "c" && aa19[3] == "d");
           
           order(aa20, SIZE);
           assert(aa20[0] == "a" && aa20[1] == "b" && aa20[2] == "c" && aa20[3] == "d");
           
           order(aa21, SIZE);
           assert(aa21[0] == "a" && aa21[1] == "b" && aa21[2] == "c" && aa21[3] == "d");
           
           order(aa22, SIZE);
           assert(aa22[0] == "a" && aa22[1] == "b" && aa22[2] == "c" && aa22[3] == "d");
           
           order(aa23, SIZE);
           assert(aa23[0] == "a" && aa23[1] == "b" && aa23[2] == "c" && aa23[3] == "d");
           
           order(aa24, SIZE);
           assert(aa24[0] == "a" && aa24[1] == "b" && aa24[2] == "c" && aa24[3] == "d");
           
           order(a2, SIZE1);
           assert(a2[0] == "a" && a2[1] == "b" && a2[2] == "c");
           
           order(a3, SIZE1);
           assert(a3[0] == "a" && a3[1] == "b" && a3[2] == "c");
          
           order(a4, SIZE1);
           assert(a4[0] == "a" && a4[1] == "b" && a4[2] == "c");
           
           order(a5, SIZE1);
           assert(a5[0] == "a" && a5[1] == "b" && a5[2] == "c");

           order(a6, SIZE1);
           assert(a6[0] == "a" && a6[1] == "b" && a6[2] == "c");

           order(a7, SIZE1);
           assert(a7[0] == "a" && a7[1] == "b" && a7[2] == "c");
    
    cout << "Passed!" << endl;
    
    return 1;
}

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).
//The empty sequence appears in a sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
// then for this value of a2            the function must return
//    "john" "ketanji" "elena"                     1
//    "john" "elena" "samuel"                      2
//    "ketanji" "john" "elena"                     0
//    "sonia" "elena" "samuel"                     3
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0)
    {
        n1 = 0;
    }
    
    if (n2 < 0)
    {
        n2 = 0;
    }
    
    
    if ( n2 > n1 || n1 <= 0)
    {
        return 0;
    }
    
    if ( n2 <= 0 )
    {
        return 1;
    }
    
    if( n1==1 && n2==1 )
    {
        if (a1[0] == a2[0])
            return 1;
        return 0;
    }
    
    if ( a1[n1-1] == a2[n2-1] )
    {
        return countIncludes( a1, n1-1, a2, n2-1) + countIncludes(a1, n1-1, a2, n2);
    }
    
    else
    {
        return countIncludes( a1, n1-1, a2, n2);
    }
}

// Exchange two strings
void exchange(string& x, string& y)
{
  string t = x;
  x = y;
  y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < separator come before all the other elements,
// and all the elements whose value is > separator come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= separator, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < separator
//   * for firstNotLess <= i < firstGreater, a[i] == separator
//   * for firstGreater <= i < n, a[i] > separator
// All the elements < separator end up in no particular order.
// All the elements > separator end up in no particular order.
void separate(string a[], int n, string separator, int& firstNotLess, int& firstGreater)
{
    
  if (n < 0)
  {
      n = 0;
  }

    // It will always be the case that just before evaluating the loop condition:
    
    //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
    
    //  Every element earlier than position firstNotLess is < separator
    
    //  Every element from position firstNotLess to firstUnknown-1 is
    //    == separator
    
    //  Every element from firstUnknown to firstGreater-1 is not known yet
    
    //  Every element at position firstGreater or later is > separator

  firstNotLess = 0;
  firstGreater = n;
  int firstUnknown = 0;
  while (firstUnknown < firstGreater)
  {
      if (a[firstUnknown] > separator)
      {
          firstGreater--;
          exchange(a[firstUnknown], a[firstGreater]);
      }
      else
      {
          if (a[firstUnknown] < separator)
          {
              exchange(a[firstNotLess], a[firstUnknown]);
              firstNotLess++;
          }
          firstUnknown++;
      }
  }
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
    if ( n <= 1 )
        return;
    
    string sep = a[n/2];
    int less = 0;
    int greater = 0;
    
    separate(a, n, sep, less, greater);

    // Recursively call 'order' on the left partition (elements less than separator)
    order(a, less);

    // Recursively call 'order' on the right partition (elements greater than separator)
    order(a + greater, n - greater);
    
    
  return;
}
