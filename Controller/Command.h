#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include <filesystem>
#include <fstream>
#include "../Model/Maze/Maze2D.h"
#include "../Model/compress/mazeCompression.h"
#include "../Model/Maze/Maze2dGenerator.h"

using namespace std;

namespace fs = experimental::filesystem;
static map<string, Maze2D> _mazes;

class Command {
public:
	virtual int run(vector<string> args) = 0;
};


class DirRequest : public Command {
public:
	DirRequest() {};
	int run(vector<string> args);
};

class GenerateRequest : public Command {
public:
	GenerateRequest() {}
	int run(vector<string> args);
};

class DisplayRequest : public Command {
public:
	DisplayRequest() {}
	int run(vector<string> args);
};

class SaveRequest : public Command {
public:
	SaveRequest() {}
	int run(vector<string> args);
};

class LoadRequest : public Command {
public:
	LoadRequest() {}
	int run(vector<string> args);
};

class SizeRequest : public Command {
public:
	SizeRequest() {}
	int run(vector<string> args);
};

class FileSizeRequest : public Command {
public:
	FileSizeRequest() {}
	int run(vector<string> args);
};

class SolveRequest : public Command {
public:
	SolveRequest() {}
	int run(vector<string> args);
};

class SolutionRequest : public Command {
public:
	SolutionRequest() {}
	int run(vector<string> args);
};

class ExitRequest : public Command {
public:
	ExitRequest() {}
	int run(vector<string> args);
};
