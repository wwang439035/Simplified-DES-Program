// SimplifiedDES_TCN5080.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

#include "BinaryFileOpera.h"
#include "CipherBlockChaining.h"

using namespace std;

void encryption(string mode, string key, string vector, string pFile, string cFile);
void decryption(string mode, string key, string vector, string pFile, string cFile);
void ouputSummary(char *cont, vector<string> res, int size, int type, string path);

int main(int argc, char* argv[])
{
	//char c;
	if (argc != 11){
		cerr << "\nNot enough parameters." << endl << endl;
		cout << "Parameters Format:\n-m [mode: encrypt|decrypt]\n-k [initial_key]\n-i [initial_vector]\n-p [plaintext_file]\n-c [ciphertext_file]\n\n" << endl;
		//cin >> c;
		return 1;
	}
	
	string mode = argv[2];
	string key = argv[4];
	string vector = argv[6];
	string pFile = argv[8];
	string cFile = argv[10];
	
	if (mode.compare("encrypt") == 0){
		encryption(mode, key, vector, pFile, cFile);
	}
	else if (mode.compare("decrypt") == 0){
		decryption(mode, key, vector, pFile, cFile);
	}

	//cin >> c;
	return 0;
}


void encryption(string mode, string key, string vector, string pFile, string cFile){
	char *cont = BinaryFileOpera::read(pFile);
	long long size = BinaryFileOpera::getSize();
	
	CipherBlockChaining cbc;
	cbc.setKey(key);
	cbc.setVector(vector);
	cbc.setPlaintext(cont);
	std::vector<string> res = cbc.encrypt();

	ouputSummary(cont, res, size, 0, cFile);
}


void decryption(string mode, string key, string vector, string pFile, string cFile){
	char *cont = BinaryFileOpera::read(cFile);
	long long size = BinaryFileOpera::getSize();

	CipherBlockChaining cbc;
	cbc.setKey(key);
	cbc.setVector(vector);
	cbc.setCiphertext(cont);
	std::vector<string> res = cbc.decrypt();

	ouputSummary(cont, res, size, 1, pFile);
}


void ouputSummary(char *cont, vector<string> res, int size, int type, string path){
	string summary = "\n\n---------------------------------------------------\n";
	summary += type == 0 ? " Encryption" : " Decryption";
	summary += " Summary of Simplified DES in CBC mode\n";
	summary += "---------------------------------------------------\n\n";
	summary += " KEY 1: " + res[1] + "\n";
	summary += " KEY 2: " + res[2] + "\n";
	string plain = "\n Plaintext: ";
	for (int i = 0; i < size; i++){
		if (type == 0)
			plain += bitset<8>(cont[i]).to_string() + " ";
		else if (type == 1)
			plain += bitset<8>(res[0][i]).to_string() + " ";
	}
	string cipher = "\n Ciphertext: ";
	for (int i = 0; i < size; i++){
		if (type == 0)
			cipher += bitset<8>(res[0][i]).to_string() + " ";
		else if (type == 1)
			cipher += bitset<8>(cont[i]).to_string() + " ";
	}

	if (type == 0)
		summary += plain + cipher;
	else if (type == 1){
		summary += cipher + plain;
	}

	summary += "\n\n---------------------------------------------------\n\n";
	cout << summary << endl;
	BinaryFileOpera::write(path, res[0]);
}