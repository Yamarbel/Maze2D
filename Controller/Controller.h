#pragma once
#include <vector>
#include <map>
#include "../Model/Maze/Maze2D.h"
#include "Command.h"

using namespace std;

class Controller
{
public:
	Controller();
	~Controller();
	virtual void InitializeCommand(const string& str) = 0;
protected:
	map<string, Command*> Commands;
	vector<string> Args;
};
