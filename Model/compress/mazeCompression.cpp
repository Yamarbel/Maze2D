#include "mazeCompression.h"

using namespace std;

////////////////////////////////////////////////////////////////
/////	Gets maze data, compresses it & write it to file   /////
////////////////////////////////////////////////////////////////
void mazeCompression::Compress() {
	int check = existMaze(maze_Name, file_Name);
	if (check == 1) {
		cout  << "The Maze '" << maze_Name << "' already exist"  << endl;
		updatingCompressedArray();
		return;
	}
	size_t file = file_Name.find(".txt");
	if (file)
		write_file.open(file_Name, ios_base::app);
	else {
		string fileName = file_Name + ".txt";
		write_file.open(fileName, ios_base::app);
	}
	int counter = 1;
	int index = 0;
	write_file << maze_Name << endl;
	int size = maze.getHeight() * maze.getWidth() - 2;
	for (int i = 0; i < size; i++) {
		compressionArray.push_back(arr[i]);
		write_file << arr[i];
		while (arr[i] == arr[i + 1] && i < size) {
			counter++;
			i++;
		}
		write_file << " " << counter << endl;
		compressionArray.push_back(counter);
		counter = 1;
	}
	compressionArray.push_back(arr[size]);
	compressionArray.push_back(counter);
	write_file << arr[size] << " " << counter << endl;
	write_file << "End" << endl;

	cout  << "Compression of "  << maze_Name  << " - Succeeded"  << endl;
	cout << endl << endl;
	arr.clear();
	write_file.close();
}

/////////////////////////////////////////////////////////////////////
/////	Reading compressed maze data from a file & decoding it	/////
/////////////////////////////////////////////////////////////////////
void mazeCompression::Expansion() {
	size_t found = file_Name.find(".txt");
	if (found)
		read_file.open(file_Name);
	else {
		string fname = file_Name + ".txt";
		read_file.open(fname);
	}
	string line;
	int one, two, countIteration = 1;
	int answer = 1;

	while (read_file && answer) {
		getline(read_file, line);
		if (line == maze_Name)
			answer = 0;
	}
	answer = 1;
	while (read_file && answer) {
		getline(read_file, line);
		if (line == "End") {
			answer = 0;
		}
		else if (int(line.length()) == 3) {
			one = int(line[0]) - 48;
			two = int(line[2]) - 48;
		}
		else if (int(line.length()) == 4 && line[0] == '-') {
			one = (int(line[1]) - 48) * -1;
			two = int(line[3]) - 48;
		}
		else if (int(line.length()) == 4 && line[0] != '-') {
			one = int(line[0]) - 48;
			two = ((int(line[2]) - 48) * 10) + (int(line[3]) - 48);
		}
		else if (int(line.length()) == 5 && line[0] != '-') {
			one = int(line[0]) - 48;
			two = ((int(line[2]) - 48) * 100) + ((int(line[3]) - 48) * 10) + (int(line[4]) - 48);
		}
		else {
			break;
		}

		while (countIteration <= two) {
			expansionArray.push_back(one);
			countIteration++;
		}
		countIteration = 1;
	}

	int counterArray = 0;
	for (int i = 0; i < maze.getHeight(); i++)
		for (int j = 0; j < maze.getWidth(); j++, counterArray++)
			expansionMaze[i][j] = expansionArray[counterArray];
	cout << endl << endl;
	cout  << "Expansion Array 2D" << endl;
	for (int i = 0; i < maze.getHeight(); i++) {
		for (int j = 0; j < maze.getWidth(); j++, counterArray++) {
			cout << expansionMaze[i][j];}
		cout << endl;}
	cout << endl;
	cout  << "Expansion of "  << maze_Name  << " - Succeeded"  << endl;
	read_file.close();
}

int mazeCompression::existMaze(string name, string FileName) {
	int answer = -1;
	size_t found = FileName.find(".txt");
	if (found)
		read_file.open(FileName);
	else {
		string fname = FileName + ".txt";
		read_file.open(fname);
	}
	string line;
	while (read_file) {
		getline(read_file, line);
		if (line == name) {
			read_file.close();
			return 1;
		}
	}
	read_file.close();
	return 0;
}

void mazeCompression::updatingCompressedArray() {
	int counter = 1;
	int index = 0;
	int size = maze.getHeight() * maze.getWidth() - 2;
	for (int i = 0; i < size; i++) {
		compressionArray.push_back(arr[i]);
		while (arr[i] == arr[i + 1] && i < size) {
			counter++;
			i++;
		}
		compressionArray.push_back(counter);
		counter = 1;
	}
	compressionArray.push_back(arr[size]);
	compressionArray.push_back(counter);
}

string MazeCompressor::Compress(const Maze2D& maze) {
	string str;
	string extended_str;
	char** temp_maze = maze.getData();
	for (int i = 0; i < maze.getHeight(); i++)
		for (int j = 0; j < maze.getWidth(); j++)
			extended_str += temp_maze[i][j];
	char temp_char = '\0';
	int counter = 0;
	str += to_string(maze.getHeight()) + " " + to_string(maze.getWidth());
	for (char c : extended_str) {
		if (temp_char != c) {
			if (temp_char != '\0') {
				str += " ";
				str += temp_char;
				str += to_string(counter);
			}
			counter = 1;
			temp_char = c;
		}
		else
			counter++;
	}
	str += " ";
	str += temp_char;
	str += to_string(counter);
	return str;
}

Maze2D MazeCompressor::Depress(string str) {
	int height = (int)atoi(str.substr(0, str.find(" ")).c_str());
	str = str.substr(str.find(" ") + 1, str.size() - str.find(" "));
	int width = atoi(str.substr(0, str.find(" ")).c_str());
	str = str.substr(str.find(" ") + 1, str.size() - str.find(" "));
	Maze2D* maze = new Maze2D(height, width);
	string extended_str;
	while (1) {
		string temp_str = str.substr(1, str.find(" "));
		for (int i = 0; i < atoi(temp_str.c_str()); i++)
			extended_str += str[0];
		if (str.find(" ") == str.npos)
			break;
		str = str.substr(str.find(" ") + 1, str.size() - str.find(" "));
	}
	char** temp_maze = maze->getData();
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			temp_maze[i][j] = extended_str[i * height + j];
	return *maze;
}
