//
//  main.cpp
//  Project3
//
//  Created by Timothy Liu on 5/16/23.
//

#include "Board.h"
#include "Side.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

void doBoardTests()
{
    Board b(3, 2);
    assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
                    b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
    b.setBeans(SOUTH, 1, 1);
    b.moveToPot(SOUTH, 2, SOUTH);
    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
                b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
        b.beansInPlay(SOUTH) == 3);
    Side es;
    int eh;
    b.sow(SOUTH, 3, es, eh);
    assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
                b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
        b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
}

void doPlayerTests()
    {
        HumanPlayer hp("Marge");
        assert(hp.name() == "Marge"  &&  hp.isInteractive());
        BadPlayer bp("Homer");
        assert(bp.name() == "Homer"  &&  !bp.isInteractive());
        SmartPlayer sp("Lisa");
        assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
        Board b(3, 2);
        b.setBeans(SOUTH, 2, 0);
        cout << "=========" << endl;
        int n = hp.chooseMove(b, SOUTH);
        cout << "=========" << endl;
        assert(n == 1  ||  n == 3);
        n = bp.chooseMove(b, SOUTH);
        assert(n == 1  ||  n == 3);
        n = sp.chooseMove(b, SOUTH);
        assert(n == 1  ||  n == 3);
    }

void doGameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(3, 0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
      //    Homer
      //   0  1  2
      // 0         0
      //   2  0  0
      //    Bart
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
      //   0  1  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(NORTH);
      //   1  0  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
      //   1  0  0
      // 0         3
      //   0  0  1
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

    g.move(NORTH);
      //   0  0  0
      // 1         4
      //   0  0  0
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(hasWinner && winner == SOUTH);
}

void myTests()
{
    
    
    /////////////////////////////
    ///  Board Tests
    ////////////////////////////
    
    
    // Original board
    Board original(3,5);
    for(int hole = 0; hole <= original.holes(); hole++)
    {
        original.setBeans(NORTH, hole, hole+2*hole);
        original.setBeans(SOUTH, hole, original.holes()-hole+2);
    }
    
    // Copy constructor
    Board copy(original);
    assert(copy.totalBeans()==original.totalBeans());
    
    for(int hole = POT; hole <= copy.holes(); hole++)
    {
        assert(copy.beans(NORTH, hole)==original.beans(NORTH, hole));
        assert(copy.beans(SOUTH, hole)==original.beans(SOUTH, hole));
    }
    
    // Assignment operator
    Board assigned(5,1);
    assigned = copy;
    
    assert(assigned.totalBeans()==original.totalBeans()
           && assigned.totalBeans() == copy.totalBeans());
    for(int hole = POT; hole <= copy.holes(); hole++)
    {
        assert(assigned.beans(NORTH, hole)==original.beans(NORTH, hole) && assigned.beans(NORTH, hole)==copy.beans(NORTH, hole));
        assert(assigned.beans(SOUTH, hole)==original.beans(SOUTH, hole) && assigned.beans(SOUTH, hole)==copy.beans(SOUTH, hole));
    }

    
    Side endS;
    int eHole;
    
    // South player sows and doesn't go into North's pot
    Board sow1(3,14);
    sow1.sow(SOUTH, 1, endS, eHole);
    assert(sow1.totalBeans()==14*3*2);
    assert(sow1.beans(NORTH, POT)==0);
    assert(sow1.beans(SOUTH, POT)==2);
    assert(sow1.beans(SOUTH, 1)==2);
    assert(endS == SOUTH && eHole == 1);
    
    // South player sows and ends up in own pot
    Board sow2(3,2);
    sow2.sow(SOUTH, 2, endS, eHole);
    assert(endS == SOUTH && eHole == POT);
    assert(sow2.beans(SOUTH, POT)==1);
    assert(sow2.totalBeans()==12);
    
    // Sowing, but doesn't end up in opponent's pot after
    Board sow3(3,5);
    sow3.display();
    sow3.sow(NORTH, 1, endS, eHole);
    assert(sow3.beans(NORTH, POT)==1);
    assert(sow3.beans(SOUTH, POT)==0);
    assert(endS==NORTH && eHole==3);
    sow3.display();
    sow3.sow(SOUTH, 2, endS, eHole);
    assert(endS==SOUTH && eHole==1);
    assert(sow3.beans(NORTH, POT)==1);
    assert(sow3.beans(SOUTH, POT)==1);
    
    // Testing other board functions
    Board basics(3,4);
    // Out of bounds hole
    assert(basics.moveToPot(NORTH, 4, NORTH)==false);
    // Valid hole
    assert(basics.moveToPot(NORTH, 1, NORTH)==true);
    assert(basics.beans(NORTH, 1)==0);
    assert(basics.beans(NORTH, POT)==4);
    assert(basics.moveToPot(NORTH, 2, NORTH)==true);
    assert(basics.beans(NORTH, 2)==0);
    assert(basics.beans(NORTH, POT)==8);
    assert(basics.totalBeans()==3*4*2);
    assert(basics.beansInPlay(SOUTH)==3*4);
    assert(basics.beansInPlay(NORTH)==3*4-8);
    
    
    /////////////////////////////
    ///  Player Tests
    ////////////////////////////
    BadPlayer bPlayer("BadBot");
    SmartPlayer sPlayer("Einstein");
    HumanPlayer hPlayer("You");
    
    // Bad Player vs Smart Player

    // Smart player should win vs Bad Player
    Board BadvsSmartBoard(4, 3);
    Game BadvsSmartGame(BadvsSmartBoard, &bPlayer, &sPlayer);
    bool isOver;
    bool hasWinner;
    Side winner;
    BadvsSmartGame.play();
    BadvsSmartGame.status(isOver, hasWinner, winner);
    //assert(isOver == true && hasWinner == true && winner == NORTH);
    
    // Only performs capture if on your side

    //    0 0 0 0 0
    // 0            0
    //    0 0 5 5 0
    Board captureTest(5,0);
    captureTest.setBeans(SOUTH, 3, 5);
    captureTest.setBeans(SOUTH, 4, 5);
    Game captureTestGame(captureTest, &bPlayer, &hPlayer);
    captureTestGame.move(SOUTH);
    assert(captureTestGame.beans(SOUTH, POT)==1);
    assert(captureTestGame.beans(NORTH, 4)==1);

    //    0 0 1 1 1
    // 0            1
    //    0 0 0 6 1

    // Successful capture

    //   0 0 2
    // 0       0
    //   2 0 0
    Board captureTest2(3,0);
    captureTest2.setBeans(SOUTH, 1, 2);
    captureTest2.setBeans(NORTH, 3, 2);
    Game captureTestGame2(captureTest2, &bPlayer, &sPlayer);
    captureTestGame2.move(SOUTH);
    assert(captureTest2.totalBeans()==4);
    assert(captureTestGame2.beans(SOUTH, POT) == 3);

    //   0 0 0
    // 0       3
    //   0 1 0

    // Multiple successive turns (land in pot)
    
    //   0 1 3
    // 0       0
    //   0 0 2
    
    Board multipleTurns(3,0);
    multipleTurns.setBeans(NORTH, 2, 1);
    multipleTurns.setBeans(NORTH, 3, 3);
    multipleTurns.setBeans(SOUTH, 3, 2);
    assert(multipleTurns.totalBeans()==6);
    Game mTurnsGame(multipleTurns, &sPlayer, &bPlayer);
    mTurnsGame.move(NORTH);
    assert(mTurnsGame.beans(NORTH, POT) == 3);
    assert(mTurnsGame.beans(SOUTH, 1) == 1);
    assert(mTurnsGame.beans(NORTH, 1) == 0);
    assert(multipleTurns.totalBeans()==6);
    //   0 0 0
    // 3       0
    //   1 0 2
    
    // Picks Capture
    
    //   0 0 3
    // 0       0
    //   3 1 0
     
    Board bTest1(3,0);
    bTest1.setBeans(NORTH, 3, 3);
    bTest1.setBeans(SOUTH, 1, 3);
    bTest1.setBeans(SOUTH, 2, 1);
    
    Game gTest1(bTest1, &sPlayer,&bPlayer);
    gTest1.move(SOUTH);
    assert(gTest1.beans(NORTH, 3)==0);
    assert(gTest1.beans(SOUTH, 3)==0);
    assert(gTest1.beans(SOUTH, POT)==4);
    assert(gTest1.beans(SOUTH, 1)==3);
    
    //   0 0 0
    // 0       4
    //   3 0 0
     
    // Avoid letting opponent capture
    Board bTest2(5,0);
    bTest2.setBeans(SOUTH, 1, 4);
    bTest2.setBeans(SOUTH, 2, 9);
    bTest2.setBeans(NORTH, 3, 1);
    bTest2.setBeans(NORTH, 5, 1);
    bTest2.display();
    //   0 0 1 0 2
    // 0           0
    //   4 9 0 0 0
    
    cout << sPlayer.chooseMove(bTest2, SOUTH)<<endl;
    
    

    // Doesn't recognize this move
    
    // Land in pot then do capturing instead of capturing right away
    Board bTest3(4,0);
    bTest3.setBeans(SOUTH, 3, 2);
    bTest3.setBeans(SOUTH, 1, 1);
    bTest3.setBeans(NORTH, 2, 2);

    //   0 2 0 0
    // 0         0
    //   1 0 2 0


    /////////////////////////////
    ///  Game Tests
    ////////////////////////////
    
    Game gTest3(bTest3, &sPlayer, &bPlayer);
    cout << gTest3.move(SOUTH);
    
    // No beans on one side (game ends)
    Board b1(3,0);
    b1.setBeans(NORTH, 2, 3);
    Game g1(b1, &sPlayer, &bPlayer);
    g1.play();
    assert(g1.move(SOUTH)==false);
    

//    bool isOver;
//    bool hasWinner;
//    Side winner;
    
    // Tie game
    Board b2(3,0);
    b2.setBeans(NORTH, 1, 1);
    b2.setBeans(SOUTH, 3, 1);
    Game g2(b2, &bPlayer, &sPlayer);
    g2.play();
    assert(g2.beans(NORTH, POT)==1);
    assert(g2.beans(SOUTH, POT)==1);
    g2.status(isOver, hasWinner, winner);
    assert(isOver);
    assert(!hasWinner);
    
    // One side wins
    Board b3(3,0);
    b3.setBeans(NORTH, POT, 3);
    Game g3(b3, &bPlayer, &sPlayer);
    g3.play();
    g3.status(isOver, hasWinner, winner);
    assert(isOver);
    assert(hasWinner);
    assert(winner == NORTH);
    
}

int main()
{
    //doBoardTests();
    //doPlayerTests();
    //doGameTests();
    //myTests();
    
    /*
     SmartPlayer sPlayer("S");
     BadPlayer bPlayer("B");
     Board b(3,2);
     Game g(b, &sPlayer, &bPlayer);
     g.play();
     
     */
    //cout << endl << "Success" << endl;
    return 1;

}
