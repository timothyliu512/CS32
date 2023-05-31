//
//  Board.hpp
//  Project3
//
//  Created by Timothy Liu on 5/16/23.
//

#ifndef BOARD_H
#define BOARD_H

#include "Side.h"
#include <vector>

class Board {
public:
    Board(int nHoles, int nInitialBeansPerHole);
    Board(const Board& other);
    Board &operator = (const Board &other);
    
    
    int holes() const;
    int beans(Side s, int hole) const;
    int beansInPlay(Side s) const;
    int totalBeans() const;
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    bool moveToPot(Side s, int hole, Side potOwner);
    bool setBeans(Side s, int hole, int beans);
    void display();
    
private:
    int mHoles;
    int mInitialBeansPerHole;
    std::vector< std::vector<int> > mBoard;
};

#endif /* BOARD_H */
