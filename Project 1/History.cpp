//
//  History.cpp
//  Project 1
//
//  Created by Timothy Liu on 4/5/23.
//

#include "History.h"
#include <iostream>
#include "globals.h"

using namespace std;

// The constructor initializes a History object that corresponds to an Arena with nRows rows and nCols columns.
// You may assume (i.e., you do not have to check) that it will be called with a first argument that does not exceed MAXROWS and a second that does not exceed MAXCOLS, and that neither argument will be less than 1.

History::History(int nRows, int nCols)
: mRows(nRows), mCols(nCols) {
    // Make the History grid (which should be same dimensions as Arena grid)
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            mGrid[i][j] = '.';
        }
    }
}

bool History::record(int r, int c){
    
    // function returns false if row r, column c is not within the bounds specified by the History constructor; otherwise, it returns true after recording what it needs to. This function expects its parameters to be expressed in the same coordinate system as an Arena (e.g., row 1, column 1 is the upper-left-most position)
    
    if ( r > mRows || c > mCols
    ||   r <= 0     || c <= 0      )
    {
        return false;
    }
    
    if (mGrid[r-1][c-1] == '.') // If first time rabbit is starting turn poisoned here
    {
        mGrid[r-1][c-1] = 'A';
    }
    
    else
    {
        if (mGrid[r-1][c-1] >= 'Z')
        {
            // Do nothing if rabbit started its turn poisoned more than 26 times at this position
        }
        else{
            mGrid[r-1][c-1] += 1; // Go from A-Z to represent 1-26
        }
    }
    return true;
}


void History::display() const{
    // Clears screen
    clearScreen();
    
    // Displays the History grid
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mCols; j++)
        {
            cout << mGrid[i][j];
        }
        cout << endl;
    }
    cout << endl;
    
    // clears the screen and displays the history grid as the posted programs do. This function does clear the screen, display the history grid, and write an empty line after the history grid; it does not print the Press enter to continue. after the display (That should be done somewhere else in the program).
    // (Note to Xcode users: It is acceptable that clearScreen() just writes a newline instead of clearing the screen if you launch your program from within Xcode, since the Xcode output window doesn't have the capability of being cleared.)
}
