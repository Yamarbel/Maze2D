#pragma once
#include "Compression.h"
#include <vector>
#include "../Maze/Maze2D.h"

class mazeCompression : public Compression {
private:
	Maze2D maze;
	string maze_Name;
	string file_Name;
	ofstream write_file;
	ifstream read_file;

	char** charMaze;
	vector<int> arr;
	vector<int> compressionArray;
	vector<int> expansionArray;
	vector<vector<int>> expansionMaze;

public:
	mazeCompression(string mazeName, string fileName, Maze2D getData) : maze_Name(mazeName), file_Name(fileName), maze(getData)  {
		charMaze = maze.getData();
		int counterArray = 0;
		for (int i = 0; i < maze.getHeight(); i++) {
			for (int j = 0; j < maze.getWidth(); j++, counterArray++) {
				if (charMaze[i][j] == '0')
					arr.push_back(0);
				else if (charMaze[i][j] == '1')
					arr.push_back(1);
				else if (charMaze[i][j] == 'S')
					arr.push_back(-2);
				else 
					arr.push_back(-3);
			}
		}	
		vector<vector<int>> vec(maze.getHeight());
		for (int i = 0; i < maze.getHeight(); i++) {
			vec[i] = vector<int>(maze.getWidth());
			for (int j = 0; j < maze.getWidth(); j++)
				vec[i][j] = -1;
		}
		expansionMaze = vec;
	}
	mazeCompression(string mazeName, Maze2D get_maze) : maze_Name(mazeName) , maze(get_maze) {
		charMaze = maze.getData();
		int counterArray = 0;
		for (int i = 0; i < maze.getHeight(); i++) {
			for (int j = 0; j < maze.getWidth(); j++, counterArray++) {
				if (charMaze[i][j] == '0')
					arr.push_back(0);
				else if (charMaze[i][j] == '1')
					arr.push_back(1);
				else if (charMaze[i][j] == 'S')
					arr.push_back(-2);
				else
					arr.push_back(-3);
			}
		}
		vector<vector<int> > vec(maze.getHeight());
		for (int i = 0; i < maze.getHeight(); i++) {
			vec[i] = vector<int>(maze.getWidth());
			for (int j = 0; j < maze.getWidth(); j++)
				vec[i][j] = -1;
		}
		expansionMaze = vec;
	}
	~mazeCompression() {}

	void Compress();
	virtual void Expansion();
	virtual int getCompressedSize() { updatingCompressedArray();
		cout << "Compressed Size: " << int(compressionArray.size()) * sizeof(char) << endl;
		return int(compressionArray.size()) * sizeof(char);
	}

	virtual int getExpansionSize() {
		cout << "Expansion Size: " << sizeof(charMaze[0][0]) * maze.getHeight() * maze.getWidth() << endl;
		return sizeof(charMaze[0][0]) * maze.getHeight() * maze.getWidth();
	}

private:
	int existMaze(string name, string FileName);
	void updatingCompressedArray();
};

class MazeCompressor
{
public:
	string Compress(const Maze2D& maze);
	Maze2D Depress(string str);
};
