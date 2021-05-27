#include "maze.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

void Maze::Cell::init(const int r, const int c, const int walls, const bool v) {
    setPosition(r, c);
    setWalls(walls);
    setVisited(v);
}
Maze::Cell::Cell() { init(0, 0, 0); }
Maze::Cell::Cell(const int r, const int c) { init(r, c, 0); }
Maze::Cell::Cell(const int r, const int c, const int walls) { init(r, c, walls); }
bool Maze::Cell::visited() const { return visit; }
void Maze::Cell::setVisited(const bool v) { visit = v; }
int Maze::Cell::getRow() const { return row; }
int Maze::Cell::getColumn() const { return col; }
void Maze::Cell::removeWall(const int w) {
    if (w!=WALL_NORTH && w!=WALL_EAST && w!=WALL_SOUTH && w!=WALL_WEST)
        throw std::string("Illegal wall argument");
    walls &= ~w;
}
int Maze::Cell::getWalls() const { return walls & WALL_ALL; }
void Maze::Cell::setWalls(const int w) { walls = w & WALL_ALL; }
void Maze::Cell::setPosition(const int r, const int c) { row = r; col = c; }

std::ostream& operator<<(std::ostream& strm, const Maze::Cell& c) {
            if ((c.getWalls() & Maze::Cell::WALL_WEST) != 0) strm << '|';
            else strm << ' ';
            if ((c.getWalls() & Maze::Cell::WALL_SOUTH) != 0) strm << '_';
            else strm << ' ';

    return strm;
}

Maze::Maze(int _ROWS, int _COLS)
    : ROWS{ _ROWS }
    , COLS{ _COLS }
{}

void Maze::start()
{
    // Randomize the random number function. 
   srand(time(NULL));

      // Create a 2-D array ([ROWS][COLS]) of Cell objects.
   Cell maze[ROWS][COLS];

   // For each Cell in the maze:
   for(int row = 0; row < ROWS; row++)
      for(int col = 0; col < COLS; col++) { 
         // set visited to false
         maze[row][col].setVisited(false);
         // set its position to its row and column in the maze
         maze[row][col].setPosition(row, col);
         // set the Cell's walls to Cell::WALL_ALL
         maze[row][col].setWalls(Cell::WALL_ALL);
   }

   //Create curX and curY variables and set them to a random position in the maze.
   int curX = 0;
   int curY = 0;

   // Create a vector of Cell objects named trail which will be used as a stack.
   vector<Cell> trail;

   // Create a vector of DIR values named live.
   vector<DIR> live;

   // Grab the Cell at the curX, curY position and push it on the trail stack.
   trail.push_back(maze[curX][curY]);

   // While the trail stack is not empty do the following:
   while(trail.empty()==false) { // stay in here till display
      // Empty the live vector.
      live.clear();
      // Check the neighbors of the current cell to the north, east, south, and west.
      // If any of the neighbors have all four walls, add the direction to that 
      // neighbor to the live vector.
      if(curY)
         if(maze[curX][curY-1].getWalls()==Cell::WALL_ALL) // West has all walls
            live.push_back(WEST);
      if(curY<COLS-1)
         if(maze[curX][curY+1].getWalls()==Cell::WALL_ALL) // east has all walls
            live.push_back(EAST);
      if(curX)
         if(maze[curX-1][curY].getWalls()==Cell::WALL_ALL) // North has all walls
            live.push_back(NORTH);
      if(curX<ROWS-1)
         if(maze[curX+1][curY].getWalls()==Cell::WALL_ALL) // South has all walls
            live.push_back(SOUTH);
      // If the live vector is not empty:
      if(live.empty()==false) {
         // Choose one of the directions in the live vector at random
         // Remove the walls between the current cell and the neighbor in that direction
         // and Change curX and curY to refer to the neighbor
         maze[curX][curY].setVisited(true);
         switch(live[rand() % live.size()]) {
            case 0: //NORTH
               maze[curX][curY].removeWall(Cell::WALL_NORTH);
               maze[--curX][curY].removeWall(Cell::WALL_SOUTH);
               break;
            case 1: //SOUTH
               maze[curX][curY].removeWall(Cell::WALL_SOUTH);
               maze[++curX][curY].removeWall(Cell::WALL_NORTH);
               break;
            case 2: //EAST
               maze[curX][curY].removeWall(Cell::WALL_EAST);
               maze[curX][++curY].removeWall(Cell::WALL_WEST);
               break;
            case 3: //WEST
               maze[curX][curY].removeWall(Cell::WALL_WEST);
               maze[curX][--curY].removeWall(Cell::WALL_EAST);
               break;
         }
         // Push the new current cell onto the trail stack
         trail.push_back(maze[curX][curY]);
      } //If the live vector was emtpy:
      else {
         // Pop the top item from the trail stack
         trail.pop_back();
         //maze[curX][curY].setWalls(Cell::WALL_ALL);
         // position of the top item in the trail stack.
         if(trail.empty()==false) {
               int n = trail.size();
               curX=trail[n-1].getRow();
               curY=trail[n-1].getColumn();
            }

      }
   }

   // Do the following to display the maze:
    int r, c;
    for (c=0; c<COLS; c++) {
        if (c == 0) cout << " _";
        else cout << "__";
    }
    cout << '\n';
    for (r=0; r<ROWS; r++) {
        for (c=0; c<COLS; c++) {
            cout << maze[r][c];
        }
        cout << "|\n";
    }
}