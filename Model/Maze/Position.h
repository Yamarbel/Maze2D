#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Position {
private:
	int _x;
	int _y;
public:
	Position() :_x(NULL), _y(NULL) {};
	Position(int x, int y) : _x(x), _y(y) {};
	int getX() const { return _x; };
	int getY() const { return _y; };
	Position reverse(const Position& p);
	friend ostream& operator<<(ostream& out, const Position& p);
	bool operator==(const Position& p);
	vector<int> getVars() const;
};