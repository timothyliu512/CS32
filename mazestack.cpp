//
//  mazestack.cpp
//  Homework 2
//
//  Created by Timothy Liu on 4/30/23.
//

#include <stdio.h>
#include <iostream>
#include <stack>
#include <string>
#include <cassert>

using namespace std;

class Coord
        {
          public:
            Coord(int rr, int cc)
            : m_r(rr), m_c(cc)
            { }
            int r() const { return m_r; }
            int c() const { return m_c; }

          private:
            int m_r;
            int m_c;
        };

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

int main(){
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','X','.','.','.','.','X' },
        { 'X','.','.','X','X','.','X','X','.','X' },
        { 'X','.','X','.','.','.','.','X','X','X' },
        { 'X','X','X','X','.','X','X','X','.','X' },
        { 'X','.','.','X','.','.','.','X','.','X' },
        { 'X','.','.','X','.','X','.','.','.','X' },
        { 'X','X','.','X','.','X','X','X','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3,4, 8,1))
        std::cout << "Solvable!" << std::endl;
    else
        std::cout << "Out of luck!" << std::endl;
    return 0;
}


bool pathExists(char maze[][10], int sr, int sc, int er, int ec){

    // Can you start on an X?
    
    std::stack <Coord> coordStack;
    coordStack.push( Coord(sr,sc) );        // Push starting coord to stack
    maze[sr][sc] = '*';                     // Mark starting cell as visited
    
    while ( !coordStack.empty() )           // As long as there's a possible coordinate
    {
        Coord end = Coord(er,ec);           // Ending coordinates
        Coord current = coordStack.top();   // Get current coord
        coordStack.pop();                   // Make room for new coord
        int r = current.r();                // Store current coord's row and column index
        int c = current.c();
        
        // If current coord = ending coord
        if( r == end.r() && c == end.c() )
        {
            return true;
        }

        // Check SOUTH
        if( r+1 < 10 && maze[r+1][c] == '.' )
        {
            coordStack.push(Coord(r+1,c));  // New coord will be current coord
            maze[r+1][c] = '*';             // Mark cell as visited
        }

        // Check EAST
        if( c+1 < 10 && maze[r][c+1] == '.' )
        {
            coordStack.push(Coord(r,c+1));  // New coord will be current coord
            maze[r][c+1] = '*';             // Mark cell as visited
        }

        // Check NORTH
        if( r-1 > 0 && maze[r-1][c] == '.' )
        {
            coordStack.push(Coord(r-1,c));  // New coord will be current coord
            maze[r-1][c] = '*';             // Mark cell as visited
        }
        
        // Check WEST
        if( c-1 > 0 && maze[r][c-1] == '.' )
        {
            coordStack.push(Coord(r,c-1));  // New coord will be current coord
            maze[r][c-1] = '*';             // Mark cell as visited
        }
    }

    return false;
}

