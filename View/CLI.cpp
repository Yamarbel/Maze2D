#include "CLI.h"

using namespace std;

void CLI::menu() {
	cout <<
		"\n"
		"		Maze2d by Yam Arbel & Chen Yafe"
		"\n\n";

    string options =   "\n";
	cout <<
		"    Usage:		\n\n"
		" 1. To shows all files in path, type:		\n"
		"	dir <path>	\n\n"

		" 2. To generate a new maze, choose algorithm- 'prim' or 'random' and type:	\n"
		"	generate_maze <name> <algorihtm> <rows> <columns>	\n\n"

		" 3. To display a specific maze, type:		\n"
		"	display <name>	\n\n"

		" 4. To save a specific maze to file, type:	\n"
		"	save_maze <name> <file name>	\n\n"

		" 5. To load specific maze from file, type:	\n"
		"	load_maze <file name> <name>	\n\n"

		" 6. To see memory size of specific maze, type:		\n"
		"	maze_size <name>	\n\n"

		" 7. To see the size of specific file, type:		\n"
		"	file_size <file name>	\n\n"

		" 8. To solve the maze with specific algorithm,		\n"
		"    choose algorithm-'BFS' or 'A*' and type:		\n"
		"	solve <name> <algorithm>	\n\n"

		" 9. To shows solution steps, type:					\n"
		"	display_solution <name>	\n\n"

		" 10. To exit the program, type:					\n"
		"	exit	\n\n";
		
    cout << "Please enter the selected command \n\n";
}
