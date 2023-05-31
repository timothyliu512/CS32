//
//  Player.cpp
//  Project3
//
//  Created by Timothy Liu on 5/16/23.
//

#include "Player.h"
#include <iostream>

using namespace std;

////////////////////////////////////////
// (BASE) PLAYER
////////////////////////////////////////

Player::Player(std::string name)
: mPlayerName(name)
{
    // Create a Player with the indicated name.
}

std::string Player::name() const
{
    //Return the name of the player.
    return mPlayerName;
}

bool Player::isInteractive() const
{
    // Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    return false;
}

int Player::chooseMove(const Board& b, Side s) const
{
    
    return -1;
}

Player::~Player()
{
    // Since this class is designed as a base class, it should have a virtual destructor.
}

////////////////////////////////////////
// HUMAN PLAYER
////////////////////////////////////////

HumanPlayer::HumanPlayer(std::string name)
: Player(name)
{
    // Create a Player with the indicated name.
}


bool HumanPlayer::isInteractive() const
{
    return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    int chosenHole = -1;
    bool prompt = true;
    
    while(prompt)
    {
        // User chooses a hole
        std::cout << "Select a hole, " << Player::name() << ": ";
        std::cin >> chosenHole;
        
        // Hole out of bounds
        if(chosenHole < 1 || chosenHole > b.holes())
        {
            std::cout << "The hole number must be from 1 to " << b.holes();
            std::cout << std::endl;
        }
        
        // Hole doesn't have enough beans
        else if ( b.beans(s, chosenHole) == 0)
        {
            std::cout << "There are no beans in that hole.";
            std::cout << std::endl;
        }
        
        // Valid hole, stop prompting user
        else
        {
            prompt = false;
        }
    }
    
    // A HumanPlayer chooses its move by prompting a person running the program for a move (reprompting if necessary until the person enters a valid hole number), and returning that choice. We will never test for a situation where the user doesn't enter an integer when prompted for a hole number. (The techniques for dealing with the issue completely correctly are a distraction to this project, and involve either a function like stoi or strtol, or the type istringstream.)
    
    // Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    return chosenHole;
}

HumanPlayer::~HumanPlayer()
{
    // Destructor
}

////////////////////////////////////////
// BAD PLAYER
////////////////////////////////////////

BadPlayer::BadPlayer(std::string name)
: Player(name)
{
    // Create a Player with the indicated name.
}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
    // Chooses an arbitrary valid move and returns that choice. "Arbitrary" can be what you like: leftmost, nearest to pot, fewest beans, random, etc.. The point of this class is to have an easy-to-implement class that at least plays legally.
    
    
    // Chooses hole that's farthest from pot with beans
    if(s == NORTH)
    {
        for(int hole = b.holes(); hole > POT; hole--) // Goes through hole
        {
            if (b.beans(s,hole) > 0 ) // Finds first hole that's not empty
            {
                return hole;
            }
        }
    }

    if(s == SOUTH)
    {
        for(int hole = 1; hole <= b.holes(); hole++) // Goes through each hole
        {
            if (b.beans(s,hole) > 0 ) // Finds first hole that's not empty
            {
                return hole;
            }
        }
    }
    
    // No holes available
    return -1;
    
}

BadPlayer::~BadPlayer()
{
    
}



////////////////////////////////////////
// SMARTPLAYER
////////////////////////////////////////

SmartPlayer::SmartPlayer(std::string name)
: Player(name)
{
    // Create a Player with the indicated name.
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{

    // A SmartPlayer chooses a valid move and returns it. For any game played on a board of up to six holes per side, with up to four initial beans per hole, SmartPlayer::chooseMove must return its choice in no more than five seconds on the SEASnet Linux server lnxsrv07.seas.ucla.edu or lnxsrv09.seas.ucla.edu: (We'll give you a way of determining the time soon; until then, you can meet this requirement by limiting the depth of your game tree search or the number of game tree positions you explore to a limit you determine experimentally.) SmartPlayer::chooseMove will be worth about 15-20% of the points for this project.

    // 1. Determine what all the legal moves are from a given board configuration, including determining whether the game is finished.

    // 2. Decide just how "good" a particular board configuration is for a player.

    // 3. Organize the previous two tasks so that possible good moves are not overlooked and time is not wasted considering many useless moves.
    
    // Unable to make any valid moves:
    if(b.beansInPlay(s)==0)
    {
        return -1;
    }
    
    int bestHole = -1;
    int value = 0;
    int depth = 7;
    Timer clock;
    // evaluation function that, given a position, returns a number that measures how good that position is for the player


    chooseMoveHelper(b, s, bestHole, value, depth, clock);

    if(bestHole == -1) // If guaranteed win (Any hole is a win)
    {
        for(int hole = 1; hole <= b.holes(); hole++) //Find first valid hole
        {
            if(b.beans(s, hole) > 0)
            {
                bestHole = hole;
                break;
            }
        }
    }
    // cerr << clock.elapsed() / 1000 << endl;
    return bestHole;
}


int SmartPlayer::evaluatePos(const Board& board, Side evaluatingSide) const
{
    // evaluation function that, given a position, returns a number that measures how good that position is for the player


    Side opposingSide;
    if(evaluatingSide == NORTH)
    {
        opposingSide = SOUTH;
    }
    else
    {
        opposingSide = NORTH;
    }

    // Game is over
    if(board.beansInPlay(evaluatingSide) == 0 || board.beansInPlay(opposingSide) == 0)
    {
        // Current side wins
        if ( (board.beans(evaluatingSide, POT) + board.beansInPlay(evaluatingSide)) > board.beans(opposingSide, POT) + board.beansInPlay(opposingSide) )
        {
            return 9999;
        }

        // Opposing side wins
        else if ( (board.beans(opposingSide, POT) + board.beansInPlay(opposingSide) ) > board.beans(evaluatingSide, POT) + board.beansInPlay(evaluatingSide)   )
        {
            return -9999;
        }

        // Tie
        return 0;
    }

    // No possible chance for you to lose
    if(board.beans(evaluatingSide, 0) > board.totalBeans()/2)
    {
        return 9999;
    }
    // No possible chance for you to win
    else if(board.beans(opposingSide, 0) > board.totalBeans()/2)
    {
        return -9999;
    }

    // Game not over
    return ( board.beans(evaluatingSide, POT) - board.beans(opposingSide, POT) );

    // The greater the difference between the number of beans in my pot and the number in my opponent's, the better" is probably a better one. These rules of thumb are called heuristics. Our evaluation functions should reflect the heuristics we believe are good, perhaps giving more weight to some more than others.

    // For many two-player games, Kalah among them, the same evaluation function that measures how good a position is for one player also measures how bad that position is for the other. If the function gives high numbers to positions that are good for South, then South will try to get into positions that evaluate to high numbers, while North will try to move into positions rated low by the same function (since bad for South is good for North).

}

// void chooseMove(in: player, board; out: bestHole, value):
//    if the criterion says we should not search below this node
//        bestHole = -1
//        value = value of this position
//        return
//    for every hole h the player can choose
//        "make" the move h
//        chooseMove(opponent, board, h2, v2)
//        "unmake" the move
//        if v2 is better for the player than best seen so far,
//            bestHole = h
//            value = v2
//    return
void SmartPlayer::chooseMoveHelper(const Board& b, Side s, int& bestHole, int& value, int depth, Timer& clock) const
{
        
    
    // Whos' who
    Side evaluatingSide = s;
    Side opposingSide;
    if (s == SOUTH)
    {
        opposingSide = NORTH;
    }
    else
    {
        opposingSide = SOUTH;
    }
    
    // Keep track of current position's value
    int curValue = evaluatePos(b, evaluatingSide);
    
    // If time limit reached:
    if( clock.elapsed() >= 4900)
    {
        bestHole = -1;
        value = curValue;
        return;
    }
    
    // Base cases: No beans left in play or max depth reached
    if(b.beansInPlay(evaluatingSide) == 0 || b.beansInPlay(opposingSide) == 0 || depth == 0)
    {
        bestHole = -1;
        value = curValue;
        return;
    }

    
    // Current position guaranted win/lose/tie
    if(curValue == 9999 || curValue == -9999 || curValue == 0)
    {
        bestHole = -1;
        value = curValue;
    }
    
    // Arbitrary values
    int bestValue;
    if (s == SOUTH)
    {
        bestValue = -9999;
    }
    else
    {
        bestValue = 9999;
    }


    
    // Go through each possible hole
    for(int hole = 1; hole <= b.holes(); hole++)
    {
        // Hole is empty so no valid possibilites
        if(b.beans(evaluatingSide, hole) == 0)
        {
            continue;
        }

        // "Make" the move
        Board boardCopy(b);
        Side endSide;
        int endHole;
        boardCopy.sow(evaluatingSide, hole, endSide, endHole);
        
        // Keep track of possible better moves
        int nextBestHole;
        int nextValue = 0;
        
        // If you get another turn
        if(endSide == evaluatingSide && endHole == POT)
        {

            chooseMoveHelper(boardCopy, evaluatingSide, nextBestHole, nextValue, depth, clock);
        }
        
        // If move ends with capture
        if(endSide == evaluatingSide && boardCopy.beans(evaluatingSide, endHole) == 1 &&
           boardCopy.beans(opposingSide, endHole) > 0 && endHole != POT)
        {
            // Move the beans to pot
            boardCopy.moveToPot(evaluatingSide, endHole, evaluatingSide);
            boardCopy.moveToPot(opposingSide, endHole, evaluatingSide);
            // Evaluate the position from there
            bestHole = hole;
            value = evaluatePos(boardCopy, evaluatingSide);
            return;
        }

        // Opponent's turn (Recursive call)
        chooseMoveHelper(boardCopy, opposingSide, bestHole, nextValue, depth - 1, clock);
        
        // Compare whether that led to better value
        if((s == SOUTH && nextValue > bestValue) || (s == NORTH && nextValue < bestValue))
        {
            bestHole = hole;
            bestValue = nextValue;
        }
    }

    // Set value to best one found
    value = bestValue;
    return;
}



SmartPlayer::~SmartPlayer()
{
    
}
