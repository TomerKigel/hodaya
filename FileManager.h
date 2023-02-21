#pragma once

#include <iostream>
#include <fstream>
#include "Dynamic_array.h"

using std::ofstream;
using std::fstream;

class FileManager
{
private:
	ofstream writefile;
	fstream readfile;
	char file_name[100];
public:
	FileManager(const char filename[100])
	{
		strcpy_s(file_name, filename);
	}
	~FileManager()
	{
		if (writefile.is_open()) {
			writefile.close();
		}
		if (readfile.is_open()) {
			readfile.close();
		}
	}

	void write_to_file(char *data,int size)
	{
		writefile.open(file_name, std::ios_base::app);
		if (writefile.is_open()) {
			for (int i = 0; i < size; i++)
				writefile << *(data + i);
		}
		writefile << ",";
		writefile.close();
	}

	void write_to_file_new_entry()
	{
		writefile.open(file_name, std::ios_base::app);
		writefile << "\n";
		writefile.close();
	}

	Dynamic_array<char*> read_lines_from_file()
	{
		int num = 0;
		Dynamic_array<char*> lines;
		readfile.open(file_name, std::ios_base::in);
		if (readfile.is_open()) {
			
			char c = -1;
			while (readfile) {
				char* line = new char[1000];
				int loc = 0;
				while (readfile && c != ',')
				{
					readfile >> c;
					line[loc++] = c;
				}
				c = -1;
				line[loc-1] = '\0';
				lines.add(line);
			}
		}
		readfile.close();
		return lines;
	}
};

