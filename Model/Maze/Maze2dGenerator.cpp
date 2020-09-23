#pragma once;
#include "Maze2dGenerator.h"

using namespace std;


/////////////////////////////////////////////////////////
/////	Calculates the time it took to run Generate /////
/////////////////////////////////////////////////////////
string Maze::measureAlgorithmTime(int row, int column) {
	auto start = chrono::high_resolution_clock::now();
	generate(row, column);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	return "It took " + to_string((double)duration.count() / 1000) + " Secs";
}


////////////////////////////////////////////////
///	Creates maze using Prim's algorithm	   /////
////////////////////////////////////////////////
Maze2D MyMaze2dGenerator::generate(int row, int column) {
	Maze2D maze(row, column);
	char** tempMaze = maze.getData();
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
			tempMaze[i][j] = '1';
	Position p(0, rand() % row);
	tempMaze[p.getY()][p.getX()] = '0';

	vector<pair<Position, Position>> wallList;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0 || i != 0 && j != 0)
				continue;
			if (!(p.getY() + i >= 0 && p.getY() + i <= column && p.getX() + j >= 0 && p.getX() + j <= row))
				continue;
			wallList.push_back(make_pair(Position(p.getX() + j, p.getY() + i), p));
		}

	Position last;
	while (!wallList.empty()) {
		int randNext = rand() % wallList.size();
		pair<Position, Position> _next(wallList[randNext]);
		wallList.erase(wallList.begin() + randNext);
		Position reverseWall = _next.first.reverse(_next.second);
		if (reverseWall.getY() < 0 || reverseWall.getY() >= column || reverseWall.getX() < 0 || reverseWall.getX() >= row)
			continue;
		if (tempMaze[_next.first.getY()][_next.first.getX()] == '1') {
			if (tempMaze[reverseWall.getY()][reverseWall.getX()] == '1') {
				tempMaze[_next.first.getY()][_next.first.getX()] = '0';
				tempMaze[reverseWall.getY()][reverseWall.getX()] = '0';

				last = reverseWall;

				for (int i = -1; i <= 1; i++)
					for (int j = -1; j <= 1; j++) {
						if (i == 0 && j == 0 || i != 0 && j != 0)
							continue;
						if (reverseWall.getY() + i < 0 || reverseWall.getY() + i >= column || reverseWall.getX() + j < 0 || reverseWall.getX() + j >= row)
							continue;
						if (tempMaze[reverseWall.getY() + i][reverseWall.getX() + j] == '0')
							continue;
						wallList.push_back(make_pair(Position(reverseWall.getX() + j, reverseWall.getY() + i), reverseWall));
					}
			}
		}
	}

	bool lastColumn = 1;
	for (int i = 0; i < column; i++)
		if (tempMaze[i][row - 1] == '0') {
			lastColumn = 0;
			break;
		}
	int f_Column = lastColumn ? row - 2 : row - 1;
	while (1) {
		int randRow = rand() % column;
		if (tempMaze[randRow][f_Column] == '1')
			continue;
		tempMaze[randRow][f_Column + 1] = 'F';
		break;

	}
	tempMaze[p.getY()][p.getX()] = 'S';
	return maze;
}


////////////////////////////////////////////
/////		Creates a random maze	   /////
////////////////////////////////////////////
Maze2D SimpleMaze2dGenerator::generate(int row, int column) {
	Maze2D maze(row, column);
	char** temp_maze = maze.getData();
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
			temp_maze[i][j] = '0';
	if (maze.getHeight() > maze.getWidth())
		Create(0, maze.getWidth(), 0, maze.getHeight(), Vertical, maze);
	else
		Create(0, maze.getWidth(), 0, maze.getHeight(), Horizonal, maze);
	Position start(0, rand() % row);
	Position goal(maze.getWidth() - 1, rand() % row);

	temp_maze[start.getY()][start.getX()] = 'S';
	temp_maze[goal.getY()][goal.getX()] = 'F';
	return maze;
}

void SimpleMaze2dGenerator::Create(int firstColumn, int lastColumn, int firstRow, int lastRow, bool direction, Maze2D& maze) {
	char** tempMaze = maze.getData();
	if (lastRow - firstRow <= 2 || lastColumn - firstColumn <= 2)
		return;
	if (direction) {
		int wall;
		while (1) {
			wall = firstColumn + rand() % (lastColumn - firstColumn - 1);
			wall == firstColumn ? wall++ : wall;
			if (wall % 2 == 0 || lastColumn - firstColumn == 2)
				break;
		}
		bool hasGap = false;
		for (int i = firstRow; i < lastRow; i++) {
			if (firstRow > 0)
				if (i == firstRow && tempMaze[firstRow - 1][wall] == '0') {
					hasGap = true;
					continue;
				}
			if (lastRow < maze.getWidth())
				if (i == lastRow - 1 && tempMaze[lastRow][wall] == '0') {
					hasGap = true;
					continue;
				}
			tempMaze[i][wall] = '1';
		}
		int _path;
		while (1) {
			_path = firstRow + rand() % (lastRow - firstRow);
			if (_path % 2 == 1)
				break;
		}
		hasGap ? NULL : tempMaze[_path][wall] = '0';
		Create(firstColumn, wall, firstRow, lastRow, Horizonal, maze);
		Create(wall + 1, lastColumn, firstRow, lastRow, Horizonal, maze);
	}
	else {
		int wall;
		while (1) {
			wall = firstRow + rand() % (lastRow - firstRow - 1);
			wall == firstRow ? wall++ : wall;
			if (wall % 2 == 0 || lastRow - firstRow == 2)
				break;
		}
		bool isEmpty = false;
		for (int i = firstColumn; i < lastColumn; i++) {
			if (firstColumn > 0)
				if (i == firstColumn && tempMaze[wall][firstColumn - 1] == '0') {
					isEmpty = true;
					continue;
				}
			if (lastColumn < maze.getHeight())
				if (i == lastColumn - 1 && tempMaze[wall][lastColumn] == '0') {
					isEmpty = true;
					continue;
				}
			tempMaze[wall][i] = '1';
		}
		int _path;
		while (1) {
			_path = firstColumn + rand() % (lastColumn - firstColumn);
			if (_path % 2 == 1)
				break;
		}
		isEmpty ? NULL : tempMaze[wall][_path] = '0';
		Create(firstColumn, lastColumn, firstRow, wall, Vertical, maze);
		Create(firstColumn, lastColumn, wall + 1, lastRow, Vertical, maze);
	}
	return;
}



////////////////////////////////////////////////////
/////	Creates maze using DFS algorithm	   /////
////////////////////////////////////////////////////
//Maze2D MyMaze2dGenerator::generate(int row, int column)
//{
//	Maze2D maze(row, column);
//	char** tempMaze = maze.getData();
//	vector<vector<int> >arr = {};
//	vector<vector<int> > arr2 = {};
//	vector<vector<int> > neigh = {};
//	vector<int> _next = {};
//	int count = 1;
//	//== counter to end recursive call quickly
//	if (count >= (column / 2)*(row / 2))
//	{
//		cout << "Invalid parameters" << endl;
//	}
//	//==== getting the unvisited neighbors
//	if (row + 2 < column - 1 && arr[row + 2][column] == 0) {
//		neigh.push_back({ row + 2,column });//down
//	}
//	if (row - 2 > 0 && arr[row - 2][column] == 0) {
//		neigh.push_back({ row - 2,column });//up
//	}
//	if (column + 2 < row - 1 && arr[row][column + 2] == 0) {
//		neigh.push_back({ row, column + 2 });//right
//	}
//	if (column - 2 > 0 && arr[row][column - 2] == 0) {
//		neigh.push_back({ row, column - 2 });//left
//	}
//	//=== forward
//	if (neigh.size() > 0) {
//		_next.clear();
//		_next = neigh[rand() % neigh.size()];
//		//mark it as visited
//		arr[_next[0]][_next[1]] = 2;
//		//counter to know if all cells are already visited
//		count++;
//		//push to the stack
//		arr2.push_back(_next);
//		//remove the walls
//		if (column - _next[1] < 0) {
//			arr[row][column + 1] = 0;
//			column += 2; create();
//		}
//		else if (column - _next[1] > 0) {
//			arr[row][column - 1] = 0;
//			column -= 2; create();
//		}
//		else if (row - _next[0] < 0) {
//			arr[row + 1][column] = 0;
//			row += 2; create();
//		}
//		else if (row - _next[0] > 0) {
//			arr[row - 1][column] = 0;
//			row -= 2; create();
//		}
//
//	}
//	//==== backtrack
//	else if (arr2.size() > 0) {
//		arr2.pop_back();
//		row = arr2[arr2.size() - 1][0];
//		column = arr2[arr2.size() - 1][1];
//		create();
//	}
//}
