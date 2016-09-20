#pragma once

#include <string>
#include <bitset>
#include <vector>

using namespace std;

class SDES
{
public:
	SDES();
	~SDES();

	bool setKey(string key);
	bool setPlaintext(char plain);
	bool setCiphertext(char cipher);
	string* getKeys();
	void generateKeys();
	char encrypt();
	char decrypt();

private:
	string key, plain, cipher;
	string keys[2];

	string transformP4(string data);
	string transformP8(string data);
	string transformP10(string data);
	string transformEP(string data);
	string procFK(string leftData, string rightData, int keyIndex);
	string procSBox(string data, int index);
	string initIP(string data);
	string inverseIP(string data);
	string leftShift(string data, int bits, int sep);

};

