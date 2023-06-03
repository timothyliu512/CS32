//
//  main.cpp
//  Project 4
//
//  Created by Timothy Liu on 5/31/23.
//

#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cassert>
#include <vector>

using namespace std;


void printWord(string w)
{
    cout << w << endl;
}

vector<string> v;  // global variable

void appendWord(string w)
{
    v.push_back(w);
}


//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

class Timer
{
  public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {
        std::chrono::duration<double,std::milli> diff =
                            std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
  private:
    std::chrono::high_resolution_clock::time_point m_time;
};

void outputCallback(string anagram);
void emptyCallback(string anagram);

int main()
    {
    
    Dictionary d;
    d.insert("cat");
    d.insert("dog");
    d.lookup("tca", printWord);  // writes  cat
    assert(v.empty());
    d.lookup("tca", appendWord);
    assert(v.size() == 1  &&  v[0] == "cat");
    
    Dictionary dict;

      // Build dictionary
    /*
     cout << "Enter name of dictionary file: ";
     // /Users/timothyliu/Documents/32/Project 4/Project 4/words.txt
     string filename = "/Users/timothyliu/Documents/32/Project 4/Project 4/";
     string readInFileName;
     getline(cin, readInFileName);
     
     filename += readInFileName;
     */
    string test = "team";
    sort(test.begin(), test.end());
    
    string filename = "/Users/timothyliu/Documents/32/Project 4/Project 4/words.txt";
    ifstream wordFile(filename);
    if ( !wordFile )
    {
        cout << "Cannot open " << filename << endl;
        return 1;
    }
    
    string word;
    while (getline(wordFile, word))
        dict.insert(word);
        
    // Find and print anagrams
    for (;;)
    {
        cout << "Enter a set of letters: ";
        string letters;
        getline(cin,letters);
        if ( ! cin  ||  letters.empty())
            break;
        
        cout << "Anagrams of " << letters << ":\n";
        
        dict.lookup(letters, outputCallback); // Calls lookup
        
        cout << endl;
        
        Timer t;
        dict.lookup(letters, emptyCallback);
        double result = t.elapsed();
        
        cout << "The lookup of anagrams takes " << result << " milliseconds." << endl;
    }
}

void outputCallback(string anagram)
{
    cout << "  " << anagram;
}

void emptyCallback(string)
{
      // For timing purposes, we use a callback function that does nothing,
      // so that the cost of doing output or whatever else a callback function
      // might do doesn't enter into the timing of the lookup functionality.
}
