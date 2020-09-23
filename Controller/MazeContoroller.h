#pragma once
#include "Controller.h"

using namespace std;

class MazeContoroller : public Controller {
public:
	MazeContoroller();
	~MazeContoroller();
	virtual void InitializeCommand(const string& str);

private:
	Maze2D* _myMaze;
};


