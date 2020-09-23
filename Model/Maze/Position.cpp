#include "Position.h"

Position Position::reverse(const Position& p) {
	if (this->_x == p._x) {
		if (this->_y == p._y + 1)
			return  Position(this->_x, this->_y + 1);
		return Position(this->_x, this->_y - 1);
	}
	else {
		if (this->_x == p._x + 1)
			return Position(this->_x + 1, this->_y);
		return Position(this->_x - 1, this->_y);
	}
};

ostream& operator<<(ostream& out, const Position& p) {
	out << "( " << p._x << " , " << p._y << " )";
	return out;
};

bool Position::operator==(const Position& p) {
	return _x == p._x && _y == p._y ? true : false;
}

vector<int> Position::getVars() const {
	vector<int> v;
	v.push_back(_x);
	v.push_back(_y);
	return v;
}