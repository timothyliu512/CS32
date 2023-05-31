//
//  Game.cpp
//  Project3
//
//  Created by Timothy Liu on 5/16/23.
//

#include "Game.h"
#include <iostream>
using namespace std; // Get rid of later

Game::Game(const Board& b, Player* south, Player* north)
: mBoard(b),
  mSouthPlayer(south),
  mNorthPlayer(north),
  mCurrentPlayer(south),
  mCurrentSide(SOUTH),
  mOver(false),
  mHasWinner(false)
{
    // Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
}

void Game::display() const
{
    int spaces = mBoard.holes() * 3;
    
    // North Player's Name
    for(int i = 0; i < (spaces/2); i++)
    {
        cout << " ";
    }
    cout << mNorthPlayer->name() << endl;
    
    
    
    // North Player's Holes
    cout << "   ";
    for(int i = 1; i <= mBoard.holes(); i++)
    {
        cout << mBoard.beans(NORTH,i) << "   ";
    }
    cout << endl;
    
        
    
    // Player Pots
    cout << " ";
    cout << mBoard.beans(NORTH,POT);
    for(int i = 0; i < mBoard.holes(); i++)
        cout << "    ";
    cout << mBoard.beans(SOUTH,POT);
    cout << endl;
    
    
    // South Player's Holes
    cout << "   ";
    for(int i = 1; i <= mBoard.holes(); i++)
    {
        cout << mBoard.beans(SOUTH,i) << "   ";
    }
    cout << endl;
    
    
    // South Player's Name
    for(int i = 0; i < (spaces/2); i++)
    {
        cout << " ";
    }
    cout << mSouthPlayer->name() << endl;
    
    // Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    
    if ( mBoard.beansInPlay(NORTH) == 0 || mBoard.beansInPlay(SOUTH) == 0 )
    {
        // Sow beans
        over = true;
        
        // If North's pot has more beans
        if (beans(NORTH, 0) > beans(SOUTH, 0))
        {
            hasWinner = true;
            winner = NORTH;
            return;
        }
        
        // If South's pot has more beans
        else if (beans(SOUTH, 0) > beans(NORTH, 0))
        {
            hasWinner = true;
            winner = SOUTH;
            return;
        }
        else
        {
            hasWinner = false;
            return;
        }
    }
    
    over = false;
    return;
    
    
    
    // If the game is over (i.e., the move member function has been called and returned false), set over to true; otherwise, set over to false and do not change anything else. If the game is over, set hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
}



bool Game::move(Side s)
{
    // Attempt to make a complete move for the player playing side s.
    // "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture.
    // Whenever the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.
    //If the move can be completed, return true;
    // if not, because the move is not yet completed but side s has no holes with beans to pick up and sow, sweep any beans in s's opponent's holes into that opponent's pot and return false.
    
    if(s == SOUTH)
    {
        mCurrentPlayer = mSouthPlayer;
    }
    else{
        mCurrentPlayer = mNorthPlayer;
    }
    
    
    // No possible moves able to be chosen by player (meaning no beans left on their side) (GAME ENDS)
    if(mBoard.beansInPlay(s) == 0)
    {
        cout << mCurrentPlayer->name() << " has no beans left to sow." << endl;
        // Sweep South's remaining beans into pot message
        if( mCurrentPlayer == mNorthPlayer)
        {
            cout << "Sweeping remaining beans into " << mSouthPlayer->name() << "'s pot." << endl;
        }
        // Sweep North's remaining beans into pot message
        else if( mCurrentPlayer == mSouthPlayer)
        {
            cout << "Sweeping remaining beans into " << mNorthPlayer->name() << "'s pot." << endl;
        }
        
        // Put remaining beans into each side's pot
        for(int hole = 0; hole <= mBoard.holes(); hole++)
        {
            int beansLeftNorth = 0; // Count beans in North's holes
            int beansLeftSouth = 0; // Count beans in South's holes
            
            beansLeftNorth += mBoard.beans(NORTH, hole); // Add up beans in each of North's holes
            mBoard.setBeans(NORTH,hole,0); // Erase the beans in that hole
            
            beansLeftSouth += mBoard.beans(SOUTH, hole); // Add up beans in each of South's holes
            mBoard.setBeans(SOUTH,hole,0); // Erase the beans in that hole
            
            // Add all the beans gathered from holes and put into North's pot
            mBoard.setBeans(NORTH, POT, ( mBoard.beans(NORTH,POT) + beansLeftNorth ) );
            
            // Add all the beans gathered from holes and put into South's pot
            mBoard.setBeans(SOUTH, POT, ( mBoard.beans(SOUTH,POT) + beansLeftSouth ) );
        }
        
        status(mOver,mHasWinner,mWinner); // Update status to indicate which side wins
        return false;
    }
    
    ///////////////////////////////////////////////////////////////
    /////////////////       VALID MOVE      ////////
    //////////////////////////////////////////////////////////////
    
    Side endSide;
    int endHole;
    
    // Current player attempts to choose a hole to move
    int moveHole = mCurrentPlayer->chooseMove(mBoard, s); // User chooses this hole
    mBoard.sow(s, moveHole, endSide, endHole); // Sow that hole

    
    // Keep track of which side you're on and what side opponent is on
    Side opponentSide;
    if(s == NORTH)
    {
        opponentSide = SOUTH;
    }
    else
    {
        opponentSide = NORTH;
    }
    
    // Say what hole current player chooses.
    if( !mCurrentPlayer->isInteractive() )
    {
        cout << mCurrentPlayer->name() << " chooses hole " << moveHole << endl;
    }
    
    // CAPTURE Scenario (end turn)
    if (endSide == s &&
             mBoard.beans(s, endHole) == 1 &&
             mBoard.beans(opponentSide, endHole) > 0 &&
             endHole != POT)
    {
        int totalBeansCaptured = mBoard.beans(mCurrentSide,endHole) + mBoard.beans(opponentSide,endHole); // Add up beans in both holes
        mBoard.setBeans(mCurrentSide, POT, ( mBoard.beans(mCurrentSide,POT) + totalBeansCaptured ) ); // Add them to your pot
        mBoard.setBeans(mCurrentSide,endHole, 0); // Remove your beans from that hole
        mBoard.setBeans(opponentSide,endHole, 0); // Remove opponent's beans that hole

        // End turn here
        // Swap side and current player
        mCurrentSide = opponentSide;

        if(mCurrentPlayer == mNorthPlayer)
        {
            mCurrentPlayer = mSouthPlayer;
        }
        else if (mCurrentPlayer == mSouthPlayer)
        {
            mCurrentPlayer = mNorthPlayer;
        }
        //cerr << "Capture" << endl; // State that a captured has been performed.
        display();
        return true;
    }
    

    // Last bean ends up in current player's pot (Another turn OR end game)
    if ( endSide == s && endHole == POT )
    {
        display();
        cout << mCurrentPlayer->name() << " gets another turn." << endl;
        return move(s); // Give player another turn
    }
    
    display();
    
    // SWAP CURRENT PLAYER (and end turn for current player)
    mCurrentSide = opponentSide;
    if(mCurrentPlayer == mNorthPlayer)
    {
        mCurrentPlayer = mSouthPlayer;
    }
    else if (mCurrentPlayer == mSouthPlayer)
    {
        mCurrentPlayer = mNorthPlayer;
    }
    return true;
    
}


void Game::play()
{
    display();
    bool southTurn = true;
    
    // Both ROBOTS
    if( mNorthPlayer->isInteractive()==false && mSouthPlayer->isInteractive()==false )
    {
        while (mOver == false) // As long as game's not over
        {
                if(southTurn) // South's turn
                {
                    move(SOUTH); // South make move
                    status(mOver, mHasWinner, mWinner); // Check if South's move ended game
                    if( !mOver ) // Game not over
                    {
                        // Prompt user
                        cout << "Press ENTER to continue";
                        cin.ignore(1000,'\n');
                        //cout << endl;
                        southTurn = false; // Swap turns
                    }
                    continue;
                }
                
                else // North's turn
                {
                    move(NORTH); // North make move
                    status(mOver, mHasWinner, mWinner); // Check if North's move ended game
                    if ( !mOver ) // Game not over
                    {
                        // Prompt user
                        cout << "Press ENTER to continue";
                        cin.ignore(1000,'\n');
                        //cout << endl;
                        southTurn = true; // Swap turns
                    }
                    continue;
                }
            }
    }
    
    // Human vs ROBOT       or      Human vs Human
    else if( (mNorthPlayer->isInteractive() == false && mSouthPlayer->isInteractive()==true) ||
             (mNorthPlayer->isInteractive() == true && mSouthPlayer->isInteractive()==false) ||
             (mNorthPlayer->isInteractive() == true && mSouthPlayer->isInteractive()==true)     )
    {
        while (mOver == false) // While game's not over
        {
                if(southTurn) // South's turn
                {
                    move(SOUTH); // Make move
                    //status(mOver, mHasWinner, mWinner); // Did that move end the game or not
                    southTurn = false; // Change turns
                    continue;
                }
                
                else // North's turn
                {
                    move(NORTH); // Make move
                    //status(mOver, mHasWinner, mWinner); // Did that move end the game or not
                    southTurn = true; // Change turns
                    continue;
                }
            }
    }
    
    
    
    if(mHasWinner && mWinner == NORTH) // North wins
    {
        display();
        cout << "The winner is ";
        cout << mNorthPlayer->name();
        cout << "." << endl;
    }
    else if( mHasWinner && SOUTH) // South wins
    {
        display();
        cout << "The winner is ";
        cout << mSouthPlayer->name();
        cout << "." << endl;
    }
    else // Neither wins
    {
        display();
        cout << "There is a tie." << endl;
    }
    
    // Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function.
    
    
    
//    for(int hole = 0; hole <= mBoard.holes(); hole++)
//    {
//        int beansLeftNorth = 0; // Count beans in North's holes
//        int beansLeftSouth = 0; // Count beans in South's holes
//
//        beansLeftNorth += mBoard.beans(NORTH, hole); // Add up beans in each of North's holes
//        mBoard.setBeans(NORTH,hole,0); // Erase the beans in that hole
//
//        beansLeftSouth += mBoard.beans(SOUTH, hole); // Add up beans in each of South's holes
//        mBoard.setBeans(SOUTH,hole,0); // Erase the beans in that hole
//
//        // Add all the beans gathered from holes and put into North's pot
//        mBoard.setBeans(NORTH, POT, ( mBoard.beans(NORTH,POT) + beansLeftNorth ) );
//
//        // Add all the beans gathered from holes and put into South's pot
//        mBoard.setBeans(SOUTH, POT, ( mBoard.beans(SOUTH,POT) + beansLeftSouth ) );
//    }
}
    
int Game::beans(Side s, int hole) const
{
    return mBoard.beans(s, hole);
    
    // Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
}
