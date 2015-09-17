CXX = g++ -std=c++11 -Wall -g

%.o : %.cpp 
	$(CXX) -c $< 

testMaze: utils.o testMaze.o maze.o
	$(CXX) -o $@ testMaze.o maze.o utils.o

main: utils.o main.o maze.o
	$(CXX) -o $@ main.o maze.o utils.o

clean:
	$(RM) main testMaze *.o
