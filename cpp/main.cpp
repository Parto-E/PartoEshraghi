#include "maze.h"
#include <iostream>
#include <unistd.h>

int main(void){


   int ROWS;
   int COLS;
   int solvation;

    //cout << "\033[1;31mbold red text\033[0m\n";

   std::cout << "\033[1;34mPlease enter the number of ROWS and COLOUMNS respectively\033[0m\n";
   std::cin >> ROWS >> COLS;
   std::cout << "\033[1;34mNow choose the solvation algorithm:\033[0m" << "\033[1;35m1)DFS 2)BFS\033[0m\n";
   std::cin >> solvation;

   std::cout << "\033[1;34mNow you're going to see the maze you wanted :)\033[0m\n";
   usleep(3000000);
   Maze m{ROWS, COLS, solvation};

   m.start();

   return 0;
} 