//
//  Board.cpp
//  Project3
//
//  Created by Timothy Liu on 5/16/23.
//

#include "Board.h"

#include <iostream>
using namespace std;


// Need to override all the elements in vector if holes < 1
Board::Board(int nHoles, int nInitialBeansPerHole)
 : mHoles(nHoles),
   mInitialBeansPerHole(nInitialBeansPerHole)
{
    if (nInitialBeansPerHole < 0) // Check for invalid # Beans per hole
    {
        mInitialBeansPerHole = 0;
    }
    
    if (mHoles < 1) // Check for invalid # holes
    {
        mHoles = 1;
    }
    
    // Put the beans into each hole
    mBoard = std::vector< std::vector<int> >(2, std::vector<int>(mHoles + 1, mInitialBeansPerHole));
    
    // Initialize pots
    mBoard[NORTH][POT] = 0;
    mBoard[SOUTH][POT] = 0;
}

int Board::holes() const
{
    return mHoles;
}

int Board::beans(Side s, int hole) const
{
    // Bounds check
    if( hole < 0 || hole > mHoles )
    {
        return -1;
    }
    
    // Returns # beans in that specific coordinate
    return mBoard[s][hole];
}

int Board::beansInPlay(Side s) const
{
    int beansInPlayTotal = 0;
    for(int hole = 1; hole <= mHoles; hole++) // Iterates through all holes on one side only
    {
        beansInPlayTotal += mBoard[s][hole]; //Counts # beans in play
    }
    
    return beansInPlayTotal;
}

int Board::totalBeans() const
{
    int total = 0; // Running total of beans counted
    
    for(int side = 0; side < NSIDES; side++) // Go through north and south side
    {
        for(int hole = POT; hole <= mHoles; hole++) // Go through each hole
        {
            total += mBoard[side][hole]; // Add # beans in that hole to total
        }
    }
    
    return total; // Return total beans
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    
    // Bounds check
    if( hole == POT                  ||
        hole < 0                     ||
        hole > mHoles                )
    {
        return false;
    }
    
    if( mBoard[s][hole] == 0)
    {
        return false;
    }

    int beansToSow = mBoard[s][hole];
    mBoard[s][hole] = 0;

    Side currentSide = s;
    bool justSwitchedSides = false;

    while (beansToSow > 0)
        {
            if (justSwitchedSides)
            {
                // Switch sides
                if (s == SOUTH)
                {
                    s = NORTH;
                    hole = mHoles;
                }
                else
                {
                    s = SOUTH;
                    hole = 1;
                }
                justSwitchedSides = false;
            }
            else
            {
                if (s == SOUTH)
                {
                    hole++;
                }
                else
                {
                    hole--;
                }
            }

            // Player reached opponent's pot
            if ((s == SOUTH && hole > mHoles) || (s == NORTH && hole < 1))
            {
                if (s == currentSide)
                {
                    mBoard[s][POT]++;
                    beansToSow--;
                }

                justSwitchedSides = true;
            }
            else
            {
                mBoard[s][hole]++;
                beansToSow--;
            }
        }

        endSide = s;
        if (hole > mHoles)
        {
            endHole = POT;
        }
        else
        {
            endHole = hole;
        }
    return true;
    




    
    
    
    
    
    
    
//    Side currentSide = s;
//
//    int beansToSow = mBoard[s][hole];
//
//    mBoard[s][hole] = 0;
//
//    bool comingFromPot = false; // Checks whether you just switched sides so you don't decrement 1 extra
//
//    // As long as there are beans to sow
//    while(beansToSow > 0)
//    {
//        // If NORTH Player sowing
//        if(s == NORTH)
//        {
//            if(comingFromPot)
//            {
//                mBoard[currentSide][hole]++;
//                beansToSow--;
//                comingFromPot = false;
//            }
//            // On NORTH side
//            if(currentSide == NORTH)
//            {
//                hole--;
//                mBoard[NORTH][hole]++;
//                beansToSow--;
//                // NORTH Player Reached NORTH POT
//                if(hole == 0 && beansToSow > 1)
//                {
//                    currentSide = SOUTH;
//                    hole = 1;
//                    comingFromPot = true;
//                    continue;
//                }
//            }
//            // On SOUTH side
//            else if(currentSide == SOUTH)
//            {
//                hole++;
//                // NORTH Player reached SOUTH POT
//                if(hole > mHoles)
//                {
//                    currentSide = NORTH;
//                    hole = mHoles;
//                }
//                mBoard[currentSide][hole]++;
//                beansToSow--;
//            }
//        }
//        // If SOUTH Player sowing
//        else if(s == SOUTH)
//        {
//            if(comingFromPot)
//            {
//                currentSide = NORTH;
//                hole = mHoles;
//                comingFromPot = false;
//                hole++;
//            }
//            // On NORTH side
//            if(currentSide == NORTH)
//            {
//                hole--;
//                // SOUTH Player Reached NORTH POT
//                if(hole == 0)
//                {
//                    currentSide = SOUTH;
//                    hole = 1;
//                }
//                mBoard[currentSide][hole]++;
//                beansToSow--;
//            }
//            // On SOUTH side
//            else if(currentSide == SOUTH)
//            {
//                hole++;
//                // SOUTH Player Reached SOUTH POT
//                if(hole > mHoles)
//                {
//                    hole = POT;
//                    comingFromPot = true;
//                }
//                mBoard[SOUTH][hole]++;
//                beansToSow--;
//                // SOUTH Player Reached SOUTH POT
//            }
//        }
//
//
//    }
    
//    while (beansToSow > 0) // As long as there are beans to sow
//    {
//        if(justSwitchedSides) // Player still at their own POT but has beans to sow
//        {
//            if(s == NORTH) // If NORTH player just finished at their own POT
//            {
//                s = SOUTH; //Start sowing from opposite side
//                hole = 1;
//            }
//            else if(s == SOUTH) // If SOUTH player just finished at their own POT
//            {
//                s = NORTH; // Start sowing from opposite side
//                hole = mHoles;
//            }
//        }
//
//        if(s == SOUTH && justSwitchedSides == false) // If on SOUTH side
//        {
//            hole++;
//        }
//        else if(s == NORTH && justSwitchedSides == false) // If on NORTH side
//        {
//            hole--;
//        }
//
//        if ( hole > mHoles && s == SOUTH) // Reached SOUTH POT
//        {
//
//            if(currentSide == NORTH) // If NORTH player just finished at SOUTH POT
//            {
//                if(beansToSow==0) // Has no beans to sow
//                {
//                    s = NORTH;
//                    hole = mHoles;
//                }
//                justSwitchedSides = true;
//                continue;
//            }
//            beansToSow--;       // Decrement # beans sowing
//            hole = POT;             // Go to POT
//            mBoard[SOUTH][POT]++;   // Increment SOUTH POT
//            justSwitchedSides = true; // Now switched sides (But staying at POT)
//            continue;
//        }
//
//        else if( hole < 1 && s == NORTH) // Reached NORTH POT
//        {
//            if(currentSide == SOUTH) // If SOUTH player in NORTH POT
//            {
//                if(beansToSow==0) // Has no beans to sow
//                {
//                    s = SOUTH;
//                    hole = mHoles;
//                }
//                justSwitchedSides = true;
//                continue;
//            }
//
//            beansToSow--;       // Decrement # beans sowing
//            mBoard[NORTH][POT]++;  // Increment NORTH POT
//            justSwitchedSides = true; // Now switched sides (But staying at POT)
//            continue;
//        }
//
//        mBoard[s][hole]++; // Add beans to that hole
//        beansToSow--; // Decrement # beans to sow
//        justSwitchedSides = false;
//    }
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    // Bounds check
    if ( hole <= 0 || hole > mHoles || potOwner < 0 || potOwner > 1 )
    {
        return false;
    }
    
    mBoard[potOwner][POT] += mBoard[s][hole]; // Add beans from hole onto pot
    mBoard[s][hole] -= mBoard[s][hole]; // Remove beans from that hole
    
    return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
    // Bounds check
    if(hole > mHoles || hole < 0 || s > 1 || s < 0 || beans < 0)
    {
        return false;
    }
    mBoard[s][hole] = beans;
    return true;
}

// COPY CONSTRUCTOR

Board::Board(const Board& other)
: mHoles(other.mHoles),
  mInitialBeansPerHole(other.mInitialBeansPerHole)
{
    // Create board with other's dimensions
    mBoard = std::vector< std::vector<int> >(2, std::vector<int>(mHoles + 1, mInitialBeansPerHole));
    
    // Copy beans into NORTH's holes
    for(int hole = 0; hole <= mHoles; hole++)
    {
        mBoard[NORTH][hole] = other.mBoard[NORTH][hole];
    }
    
    // Copy beans into SOUTH's holes
    for(int hole = 0; hole <= mHoles; hole++)
    {
        mBoard[SOUTH][hole] = other.mBoard[SOUTH][hole];
    }
}


// ASSIGNMENT OPERATOR
Board& Board::operator=(const Board &other)
{
    if(this != &other)
    {
        mHoles = other.mHoles;
        mInitialBeansPerHole = other.mInitialBeansPerHole;
        mBoard = std::vector<std::vector<int>>(2, std::vector<int>(mHoles + 1, mInitialBeansPerHole));

        // Copy beans into NORTH's holes
        for (int hole = 0; hole <= mHoles; hole++)
        {
            mBoard[NORTH][hole] = other.mBoard[NORTH][hole];
        }

        // Copy beans into SOUTH's holes
        for (int hole = 0; hole <= mHoles; hole++)
        {
            mBoard[SOUTH][hole] = other.mBoard[SOUTH][hole];
        }
    }

    return *this;
}



// DISPLAY BOARD
void Board::display()
{
    cerr << endl;
    cerr << "  ";
    for(int k=0; k<holes(); k++)
        cout<<k+1<<"  "; //Print indices for NORTH
    cerr << endl;
    cerr << "  ";
    for(int k=0; k<holes(); k++)
    {
        cerr<<beans(Side::NORTH, k+1)<<"  "; //Print NORTH playable holes
    }
    
    cerr << endl;
    
    cerr << " " << beans(Side::NORTH, 0);
    for(int k=0; k<holes()+2;k++)
    {
        cerr<<"  ";
    }
    cerr << beans(Side::SOUTH, 0)<<endl;
    cerr << "  ";
    for(int k=0; k<holes(); k++)
    {
        cerr<<beans(Side::SOUTH, k+1)<<"  "; //Print SOUTH playable holes
    }
    cerr << endl;
    cerr << "  ";
    for(int k=0; k<holes(); k++)
    {
        cerr << k+1 << "  "; // Print indices for SOUTH
    }
    cerr << endl;
}
