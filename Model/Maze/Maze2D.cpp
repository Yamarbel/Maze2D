#include "Maze2D.h"

using namespace std;

////////////////////////////////////////
/////		   Maze setting		   /////
////////////////////////////////////////
Maze2D::Maze2D(int _row, int _column) {
	_height = _column;
	_width = _row;
	_maze = new char*[_column];
	for (int i = 0; i < _column; i++)
		_maze[i] = new char[_row];
}

Maze2D::Maze2D(const Maze2D& maze) {
	_height = maze._height;
	_width = maze._width;
	_maze = new char*[_height];
	for (int i = 0; i < _height; i++)
		_maze[i] = new char[_width];
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			_maze[i][j] = maze._maze[i][j];
}

void Maze2D::setMaze(char** maze) {
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			_maze[i][j] = maze[i][j];
}

ostream& operator<<(ostream& out, const Maze2D& maze) {

	for (int i = 0; i < maze._width * 2 + 2; i++)
		out << "0";
	out << endl;
	for (int i = 0; i < maze._height; i++) {
		out << "0";
		for (int j = 0; j < maze._width; j++) {
			if (maze._maze[i][j] == '1')
				out << "||";
			else if (maze._maze[i][j] == 'S')
				out << "S ";
			else if (maze._maze[i][j] == 'F')
				out << "F ";
			else
				out << "  ";
		}
		out << "0" << endl;
	}
	for (int i = 0; i < maze._width * 2 + 2; i++)
		out << "0";
	out << endl;
	return out;
};


Position Maze2D::getStartPosition() const {
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			if (_maze[i][j] == 'S')
				return Position(j, i);
	return Position();
}

string Maze2D::getPossibleMoves(const Position& _p) const {
	string str = "";
	if (_p.getY() > _height - 1 && _p.getX() <= 0)
		return str;
	if (!(_p.getY() == 0))
		if (_maze[_p.getY() - 1][_p.getX()] != '1')
			str += "Up ";
	if (!(_p.getY() >= _height - 1))
		if (_maze[_p.getY() + 1][_p.getX()] != '1')
			str += "Down ";
	if (!(_p.getX() == 0))
		if (_maze[_p.getY()][_p.getX() - 1] != '1')
			str += "Left ";
	if (!(_p.getX() >= _width - 1))
		if (_maze[_p.getY()][_p.getX() + 1] != '1')
			str += "Right ";
	return str;
}

Position Maze2D::getGoalPosition() {
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			if (_maze[i][j] == 'F')
				return Position(j, i);
	return Position();
}
