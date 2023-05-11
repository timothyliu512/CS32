//
//  maze.cpp
//  Homework 3
//
//  Created by Timothy Liu on 5/7/23.
//

#include <stdio.h>
#include <stack>
#include <iostream>
using namespace std;

class Coord
        {
          public:
            Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
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
        std::cerr << "Solvable!" << std::endl;
    else
        std::cerr << "Out of luck!" << std::endl;
    return 0;
}

bool pathExists(char maze[][10], int sr, int sc, int er, int ec){
    if ( sr == er && sc == ec )
        return true;
    
    maze[sr][sc] = '*';
    
    int r = sr;
    int c = sc;
    
    if( r+1 < 10 && maze[r+1][c] == '.' )
    {
         if ( pathExists(maze, r+1, c, er, ec) )
             return true;
    }

    // Check EAST
    if( c+1 < 10 && maze[r][c+1] == '.' )
    {
        if ( pathExists(maze, r, c+1, er, ec) )
            return true;
    }

    // Check NORTH
    if( r-1 > 0 && maze[r-1][c] == '.' )
    {
        if ( pathExists(maze, r-1, c, er, ec) )
            return true;
    }
    
    // Check WEST
    if( c-1 > 0 && maze[r][c-1] == '.' )
    {
        if ( pathExists(maze, r, c-1, er, ec) )
            return true;
    }
    
    return false;
}
