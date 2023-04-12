//
//  Game.hpp
//  Project 1
//
//  Created by Timothy Liu on 4/5/23.
//

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <string>

class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
};

#endif /* GAME_H */
