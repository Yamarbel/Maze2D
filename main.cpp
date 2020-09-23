#include <iostream>
#include "Model/Maze/Maze2D.h"
#include "View/CLI.h"
#include "Model\Demo\Demo.h"

using namespace std;

class TestMazeGenarator {
public:
	TestMazeGenarator() {};

	void testMazeGenarator(Maze2dGenerator& mg) {

		// prints the time it takes the algorithm to run.
		cout << mg.measureAlgorithmTime(200, 200) << endl;

		// generate another 2d maze.
		Maze2D maze = mg.generate(30, 30);

		// get the maze entrance
		Position p = maze.getStartPosition();

		// print the position - format (x, y).
		cout << maze.getPossibleMoves(p) << endl;

		cout << maze.getGoalPosition() << endl;

		cout << maze << endl;
	}
};

int main() {
	TestMazeGenarator t;
	MyMaze2dGenerator mg;
	t.testMazeGenarator(mg);
	Demo d;
	d.run();
	CLI(cout, cin).start();
}
