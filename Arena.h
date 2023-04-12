//
//  Arena.h
//  Project 1
//
//  Created by Timothy Liu on 4/5/23.
//

#ifndef ARENA_H
#define ARENA_H

#include <stdio.h>

#include "globals.h"
#include "History.h"
#include <string>

class Player;
class Rabbit;

class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     rabbitCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfRabbitsAt(int r, int c) const;
    void    display(std::string msg) const;

      // Mutators
    void setCellStatus(int r, int c, int status);
    bool addRabbit(int r, int c);
    bool addPlayer(int r, int c);
    void moveRabbits();

      // History
    History& history();
    
  private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Rabbit* m_rabbits[MAXRABBITS];
    int     m_nRabbits;
    int     m_turns;
    
    //History
    History m_History;

      // Helper functions
    void checkPos(int r, int c, std::string functionName) const;
    bool isPosInBounds(int r, int c) const;
};

#endif /* ARENA_H */
