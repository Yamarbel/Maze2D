#pragma once
#include "../Maze/Maze2dGenerator.h"

class Demo {
public:
	void run() {
		MyMaze2dGenerator generator;
		Maze2D maze = generator.generate(20, 20);
		maze.printMaze();
	}
};