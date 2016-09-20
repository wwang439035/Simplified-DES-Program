#pragma once

#include <string>
#include <bitset>
#include <vector>
#include "SDES.h"

using namespace std;

class CipherBlockChaining
{
public:
	CipherBlockChaining();
	~CipherBlockChaining();

	bool setKey(string key);
	bool setVector(string vector);
	bool setPlaintext(string plain);
	bool setCiphertext(string cipher);
	vector<string> encrypt();
	vector<string> decrypt();

private:
	string key, vector, plain, cipher;
	SDES sdes;
};

