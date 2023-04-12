//
//  Rabbit.h
//  Project 1
//
//  Created by Timothy Liu on 4/5/23.
//

#ifndef RABBIT_H
#define RABBIT_H

#include <stdio.h>

class Arena;  // This is needed to let the compiler know that Arena is a type name, since it's mentioned in the Rabbit declaration.

class Rabbit
{
  public:
      // Constructor
    Rabbit(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
    int    m_idleTurnsRemaining;
};

#endif /* RABBIT_H */
