#include <iostream>  // needed
#include <fstream>   // needed to read from a file
#include "maze.hpp"
#include "utils.hpp"

int main(int argc, const char *argv[]) {
	if( argc != 2 ) //checks for the input file name
	{
		std::cerr << "Error: no input file name" << std::endl;
		std::cerr << "Usage: ./" << argv[0] << " someinput.txt" << std::endl;
		return 1;
	}
   else if (argc > 2)
   {
      std::cerr << "error; you are putting more than one file" << std::endl;
		std::cerr << "Usage: ./" << argv[0] << " someinput.txt" << std::endl;
	   return 1;
	}
   
	std::ifstream mazeInputFile ( argv[1] );	// open the input file
	int numberOfMazes = 0;
	mazeInputFile >> numberOfMazes; 			// read the number of mazes
   
	for (int currentMaze = 0; currentMaze < numberOfMazes; currentMaze++ ) {
		int mazeSize = 0;
		mazeInputFile >> mazeSize;				// read the maze size from the input file

		// Create a new maze object of the given size
		Maze maze(mazeSize);
      
		// Initialize the maze
		maze.readFromFile(mazeInputFile);
      
      std::cout << "ENTER" << std::endl;
		// Solve the maze
		do {
			// Advance one step in the maze
			maze.step();
		} while ( ! maze.atExit() );
      std::cout << "EXIT" << std::endl;
      std::cout << "***" << std::endl;
	}
   return 1;
}
