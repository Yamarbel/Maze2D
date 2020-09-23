#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>     
#include <time.h>      
#include <fstream>
#include <vector>

using namespace std;

class Compression
{
private:
	ofstream write_file;
	ifstream read_file;
public:
	Compression() {}
	~Compression() {}
	virtual void Compress() = 0;
	virtual void Expansion() = 0;
	virtual int getCompressedSize() = 0;
	virtual int getExpansionSize() = 0;
}; 
