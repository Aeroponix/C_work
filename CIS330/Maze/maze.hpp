/*
 * maze.hpp
 *      Author: norris
 */

#ifndef MAZE_HPP_
#define MAZE_HPP_
#include <fstream>

class Maze
{
public:
	Maze(int size){
      this->size = size;
      this->row = 0;
      this->col = 0;
      for (int i = 0; i < size; i++) {
         for(int j = 0; j < size; j++){
            this->maze[i][j] = '.';
         }
      }
      this->dirction_of_solving =UP;
   }
	~Maze(){
    
   }
   
	//enum Direction { DOWN, RIGHT, UP, LEFT };
   typedef enum { DOWN, RIGHT, UP, LEFT } Direction;
         
	// Implement the following functions:

	// read maze from file, find starting location
	void readFromFile(std::ifstream &f);
   
	// make a single step advancing toward the exit
	void step();
   
	// return true if the maze exit has been reached, false otherwise
	bool atExit();

	// set row and col to current position of 'x'
	void getCurrentPosition(int &row, int &col);

	// You can add more functions if you like
private:
	// Private data and methods 
   int size;
   int row;
   int col;
   Direction dirction_of_solving;
   char maze[30][30];
   void mazeUp(int row, int col, int dirction_of_solving, int size);
   void mazeDown(int row, int col, int dirction_of_solving, int size);
   void mazeLeft(int row, int col, int dirction_of_solving, int size);
   void mazeRight(int row, int col, int dirction_of_solving, int size);
};
#endif /* MAZE_HPP_ */