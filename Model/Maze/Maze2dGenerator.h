#pragma once
#include "Maze2D.h"

using namespace std;

////////////////////////////////////////////
/////	Creates instances of Maze2D	   /////
////////////////////////////////////////////
class Maze2dGenerator {
protected:
	Maze2D _maze;
public:
	virtual Maze2D generate(int _row, int _column) = 0;
	virtual string measureAlgorithmTime(int _row, int _column) = 0;
};

class Maze : public Maze2dGenerator {
public:
	virtual Maze2D generate(int row, int column) = 0;
	virtual string measureAlgorithmTime(int _row, int _column);
};


class SimpleMaze2dGenerator : public Maze {
public:
	Maze2D generate(int _row, int _column);
private:
	void Create(int rowStart, int rowEnd, int colStart, int colEnd, bool _direction, Maze2D& maze);
};

class MyMaze2dGenerator : public Maze {
public:
	Maze2D generate(int _row, int _column);
};