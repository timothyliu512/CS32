//
//  Player.hpp
//  Project3
//
//  Created by Timothy Liu on 5/16/23.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"
#include "Side.h"

//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#include <chrono>

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
        std::chrono::duration<double, std::milli> diff =
                          std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
  private:
    std::chrono::high_resolution_clock::time_point m_time;
};



////////////////////////////////////////
// (BASE) PLAYER
////////////////////////////////////////

class Player
{
public:
    Player(std::string name);
    // Create a Player with the indicated name.
    std::string name() const;
    //Return the name of the player.
    virtual bool isInteractive() const;
    // Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Side s) const = 0;
    // Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~Player();
    // Since this class is designed as a base class, it should have a virtual destructor.
private:
    std::string mPlayerName;
};

////////////////////////////////////////
// HUMAN PLAYER
////////////////////////////////////////

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~HumanPlayer();
private:
};

////////////////////////////////////////
// BAD PLAYER
////////////////////////////////////////

class BadPlayer : public Player
{
public:
    BadPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~BadPlayer();
private:
};

////////////////////////////////////////
// SMART PLAYER
////////////////////////////////////////

class SmartPlayer : public Player
{
public:
    SmartPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~SmartPlayer();
private:
    int evaluatePos(const Board& board, Side evaluatingSide) const;
    void chooseMoveHelper(const Board& b, Side s, int&bestHole, int& value, int depth, Timer& clock) const;
    
    
};

#endif /* PLAYER_H */
