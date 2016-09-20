#pragma once

#include <string>
#include <fstream>

using namespace std;

class BinaryFileOpera
{
public:
	BinaryFileOpera();
	~BinaryFileOpera();

	static char* read(string path);
	static bool write(string path, string content);
	static long long getSize();

private:
	static long long fsize;
};

