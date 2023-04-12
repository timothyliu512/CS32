//
//  History.h
//  Project 1
//
//  Created by Timothy Liu on 4/5/23.
//

#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include "globals.h"

class History
    {
      public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
        
    private:
        char mGrid[MAXROWS][MAXCOLS];
        int mRows;
        int mCols;
    };

#endif /* HISTORY_H */
