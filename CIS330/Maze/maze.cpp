#include <iostream>
using namespace std;
#include "maze.hpp"

// read maze from file, find starting location
void Maze::readFromFile(std::ifstream &f){
	std::string theline;
	this->size = size;
   std::string data;
	for (int i = 0; i < size; i++) {
      f >> theline;
      for(int j = 0; j < size; j++){
              this->maze[i][j] = theline[j];
              if(maze[i][j] == 'x'){
		            this->row = i;
		            this->col = j;
		            if (i == 0){
		                this->dirction_of_solving = DOWN;
		            }
		            else if(i == size - 1){
		                this->dirction_of_solving = UP;
		            }
		            else if(j == 0){
		                this->dirction_of_solving = RIGHT;
		            }
		            else if(j == size - 1){
		                this->dirction_of_solving = LEFT;
		            }
         }
         std::cout << maze[i][j];
      }
      std::cout << "" << std::endl;    
	}
}

// make a single step advancing toward the exit
void Maze::step(){
   if(this->dirction_of_solving == UP){
      mazeUp(this->row, this->col, this->dirction_of_solving, this->size);
   }
   else if(this->dirction_of_solving == LEFT){
      mazeLeft(this->row, this->col, this->dirction_of_solving, this->size);
   }
   else if(this->dirction_of_solving == DOWN){
      mazeDown(this->row, this->col, this->dirction_of_solving, this->size);
   }
   else if(this->dirction_of_solving == RIGHT){
      mazeRight(this->row, this->col, this->dirction_of_solving, this->size);
   }
}

// set row and col to current position of 'x'
void Maze::getCurrentPosition(int &row, int &col){
   row = this->row;
   col = this->col;
   }

bool Maze::atExit(){
      return this->row == 0 || this->row == this->size - 1 || this->col == 0 || this->col == this->size -1;
   }
   
void Maze::mazeUp(int row, int col, int dirction_of_solving, int size){
   if (maze[this->row][this->col + 1] == '.'){
      std::cout << "RIGHT" << std::endl;
      this->col +=1;
		this->dirction_of_solving = RIGHT;
		}
    else if (maze[this->row - 1][this->col] == '.'){
      std::cout << "UP" << std::endl;
      this->row -=1;
      this->dirction_of_solving = UP;
        }
    else if (maze[this->row][this->col - 1] == '.'){
      std::cout << "LEFT" << std::endl;
      //this->row-=1;
      this->col -=1;
      this->dirction_of_solving = LEFT;
        }
    else if (maze[this->row + 1][this->col] == '.'){
      std::cout << "DOWN" << std::endl;
      this->row+=1;
      this->dirction_of_solving = DOWN;
        }
   }
   
void Maze::mazeDown(int row, int col, int dirction_of_solving, int size){
	//this function would check if there is a road in any dirction and reset the dirction, i and j th pos for DOWN
	if (maze[this->row][this->col - 1] == '.'){
		std::cout << "LEFT" << std::endl;
      this->col-=1;
      this->dirction_of_solving = LEFT;
		}
   else if (maze[this->row + 1][this->col] == '.'){
      std::cout << "DOWN" << std::endl;
      this->row+=1;
      this->dirction_of_solving = DOWN;
		}
	else if (maze[this->row][this->col + 1] == '.'){
        std::cout << "RIGHT" << std::endl;
        this->col+=1;
        this->dirction_of_solving = RIGHT;
	    }
   else if (maze[this->row - 1][this->col] == '.'){
        std::cout << "UP" << std::endl;
        this->row-=1;
        this->dirction_of_solving = UP;
	    }
   }
void Maze::mazeLeft(int row, int col, int dirction_of_solving, int size){
	//this function would check if there is a road in any dirction and reset the dirction, i and j th pos for LEFT
   if (maze[this->row - 1][this->col] == '.'){
      std::cout << "UP" << std::endl;
      this->row-=1;
      this->dirction_of_solving = UP;
		}
	else if (maze[this->row][this->col - 1] == '.'){
      std::cout << "LEFT" << std::endl;
      this->col-=1;
      this->dirction_of_solving = LEFT;
		}
	else if (maze[this->row + 1][this->col] == '.'){
        std::cout << "DOWN" << std::endl;
        this->row+=1;
        this->dirction_of_solving = DOWN;
        }
    else if (maze[this->row][this->col + 1] == '.'){
      std::cout << "RIGHT" << std::endl;
      this->col+=1;
      this->dirction_of_solving = RIGHT;
        }
   }
void Maze::mazeRight(int row, int col, int dirction_of_solving, int size){
	//this function would check if there is a road in any dirction and reset the dirction, i and j th pos for RIGHT
	if (maze[this->row + 1][this->col] == '.'){
      std::cout << "DOWN" << std::endl;
      this->row+=1;
      this->dirction_of_solving = DOWN;
        }
	else if (maze[this->row][this->col + 1] == '.'){
        std::cout << "RIGHT" << std::endl;
        this->col+=1;
        this->dirction_of_solving = RIGHT;
		}
	else if (maze[this->row - 1][this->col] == '.'){
        std::cout << "UP" << std::endl;
        this->row-=1;
        this->dirction_of_solving = UP;
	    }
	else if (maze[this->row][this->col - 1] == '.'){
      std::cout << "LEFT" << std::endl;
      this->col-=1;
      this->dirction_of_solving = LEFT;
	    }
   }

