#include "Command.h"

using namespace std;

////////////////////////////////////////////////////////////////////
/////	Displays all the files & folders under the given path	////
////////////////////////////////////////////////////////////////////
int DirRequest::run(vector<string> var) {
	string str;
	for (string s:var) {
		if (s == "dir")
			continue;
		str += s + " ";
	}
	str.pop_back();
	const fs::path Path = str;
	for (auto itEntry = fs::recursive_directory_iterator(Path);
		itEntry != fs::recursive_directory_iterator();
		++itEntry) {
		const auto file_name = itEntry->path().filename().string();
		cout << setw((int)itEntry.depth() * (int)3) << "";
		cout << "Files:  " << file_name << '\n';
	}
	cout << endl;
	return 1;
}


////////////////////////////////////////
/////		Generate custom maze		////
////////////////////////////////////////
int GenerateRequest::run(vector<string> var) {
	Maze2D Maze;
	Maze2dGenerator* generator;
	if (var[2] == "prim")
		generator = new MyMaze2dGenerator();
	else if (var[2] == "random")
		generator = new SimpleMaze2dGenerator();
	else
		return 1;
	Maze = generator->generate(stoi(var[3]), stoi(var[4]));
	cout << "Maze '" + var[1] + "' was created." << endl;
	_mazes[var[1]] = Maze;
	Sleep(100);

	return 1;
}


////////////////////////////////////////
/////		Display maze			////
////////////////////////////////////////
int DisplayRequest::run(vector<string> var) {
	
	if (_mazes.find(var[1]) != _mazes.end())
	{
		cout << "\n The maze '" + var[1] + "': \n\n";
		cout << _mazes[var[1]];
	}
	else
		cout << "\n The maze '" + var[1] + "' does not exist." << endl;
	
	return 1;
}


////////////////////////////////////////////
/////	Saved compressed maze to file	////
////////////////////////////////////////////
int SaveRequest::run(vector<string> var) {
	Maze2D Maze;
	if (_mazes.find(var[1]) != _mazes.end()) {
		MazeCompressor compressor;
		ofstream out_file;
		out_file.open(var[2], ios::app);
		if (!out_file.is_open()) {
			cout << "The file '" + var[2] + "' does not exsist. \n";
			return 1;
		}
		string compressed_maze = compressor.Compress(_mazes[var[1]]);
		out_file << var[1] << "\n" << compressed_maze << "\nS ";
		out_file << "\n";
		out_file.close();
		cout << "The maze '" + var[1] + "' saved succesfully to file '" + var[2] + "' \n";
	}
	else
		cout << "Maze '" + var[1] + "' does not exsist." << endl;
	return 1;
}

////////////////////////////////////////////////
/////	Loading and decoded maze from file	////
////////////////////////////////////////////////
int LoadRequest::run(vector<string> var) {
	ifstream in_file;
	in_file.open(var[1]);
	if (!in_file.is_open()) {
		cout << "The file '" + var[1] + "' does not exsist. \n";
		return 1;
	}
	string line;
	Maze2D maze;
	MazeCompressor compressor;
	while (!in_file.eof()) {
		getline(in_file, line);
		if (!line.compare(var[2])) {
			getline(in_file, line);
			maze = compressor.Depress(line);
			getline(in_file, line);
			if (!line.compare("S "))
				_mazes[var[2]] = maze;
			cout << "Maze '" + var[2] + "' loaded succesfully from '" + var[1] + "' \n";
			return 1;
		}
	}
	return 1;
}


////////////////////////////////////////////
/////	Return the size of given maze	////
////////////////////////////////////////////
int SizeRequest::run(vector<string> var) {
	if (_mazes.find(var[1]) != _mazes.end()) {
		int mazeWidth = _mazes[var[1]].getWidth();
		int mazehight = _mazes[var[1]].getHeight();
		auto temp = _mazes[var[1]].getData();
		int sizeCell = sizeof(temp[0][0]);
		int totalSize = mazehight * mazeWidth * sizeCell;
		cout << "The maze '" + var[1] + "' takes " << totalSize << " bits of the memory" << endl;
	}
	else
		cout << "Maze '" + var[1] + "' does not exsist." << endl;
	
	return 1;
}


////////////////////////////////////////////
/////	Return the size of given file	////
////////////////////////////////////////////
int FileSizeRequest::run(vector<string> var) {
		ifstream file;
		file.open(var[1]);
		if (!file.is_open()) {
			cout << "The file '" + var[1] + "' does not exsist. \n";
			return 1;
		}
		else {
			ifstream file(var[1], ios::binary | ios::ate);
			float file_size = file.tellg();
			cout << "The size of " + var[1] + " is: " << file_size << "bytes" << endl;
			return 1;
		}
}

int SolveRequest::run(vector<string> var) {
	return 1;
}

int SolutionRequest::run(vector<string> var) {
	return 1;
}

////////////////////////////////////
/////	Exit from the progrem	////
////////////////////////////////////
int ExitRequest::run(vector<string> var) {
	exit(0);
	return 0;
}
