#include "stdafx.h"
#include "BinaryFileOpera.h"

long long BinaryFileOpera::fsize = 0;

BinaryFileOpera::BinaryFileOpera()
{
}


BinaryFileOpera::~BinaryFileOpera()
{
}


char* BinaryFileOpera::read(string path){
	fstream file(path, ios::in | ios::binary);
	if (file.is_open()){
		file.seekg(0, file.end);
		BinaryFileOpera::fsize = file.tellg();
		file.seekg(0, file.beg);
		char* buffer = new char[(long)(fsize + 1)];
		file.read(buffer, fsize);
		file.close();
		buffer[fsize] = '\0';
		return buffer;
	}
	return NULL;
}


bool BinaryFileOpera::write(string path, string content){
	fstream file(path, ios::out | ios::trunc | ios::binary);
	if (file.is_open()){
		file.write(content.c_str(), content.size());
		file.close();
		return true;
	}
	return false;
}


long long BinaryFileOpera::getSize(){
	return BinaryFileOpera::fsize;
}