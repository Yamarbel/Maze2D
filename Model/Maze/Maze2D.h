#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <Windows.h>
#include "Position.h"

#define Horizonal 0
#define Vertical 1

class Maze2D {
	char** _maze;
	int _width;
	int _height;
	
public:
	Maze2D() : _maze(nullptr), _width(NULL) , _height(NULL) {};
	Maze2D(int _row, int _column);
	Maze2D(const Maze2D& _maze);
	int getWidth() const { return _width; };
	int getHeight() const { return _height; };
	char** getData() const { return _maze; };
	void setMaze(char** _maze);
	void printMaze() const { std::cout << *this; };
	friend ostream& operator<<(ostream& out, const Maze2D& maze);
	Position getStartPosition() const;
	string getPossibleMoves(const Position& p) const;
	Position getGoalPosition();
};
