#include "stdafx.h"
#include "SDES.h"


SDES::SDES()
{
}


SDES::~SDES()
{
}


bool SDES::setKey(string key){
	if (key.c_str() != NULL && key.size() == 10){
		this->key = key;
		return true;
	}
	return false;
}


bool SDES::setPlaintext(char plain){
	if (plain != NULL){
		this->plain = bitset<8>(plain).to_string();
		return true;
	}
	return false;
}


bool SDES::setCiphertext(char cipher){
	if (cipher != NULL){
		this->cipher = bitset<8>(cipher).to_string();
		return true;
	}
	return false;
}


string* SDES::getKeys(){
	return keys;
}


char SDES::encrypt(){
	if (key.size() == 10 && plain.size() == 8){
		string tmpPlain = this->initIP(plain);
		string left = tmpPlain.substr(0, 4);
		string right = tmpPlain.substr(4, 4);

		left = procFK(left, right, 0);

		string tmp = left;
		left = right;
		right = tmp;

		left = procFK(left, right, 1);
		
		this->cipher = this->inverseIP(left + right);
		return (char)bitset<8>(this->cipher).to_ulong();
	}
	return '\0';
}


char SDES::decrypt(){
	if (key.size() == 10 && cipher.size() == 8){
		string tmpCipher = this->initIP(this->cipher);
		string left = tmpCipher.substr(0, 4);
		string right = tmpCipher.substr(4, 4);

		left = procFK(left, right, 1);

		string tmp = left;
		left = right;
		right = tmp;

		left = procFK(left, right, 0);

		this->plain = this->inverseIP(left + right);
		return (char)bitset<8>(this->plain).to_ulong();
	}
	return '\0';
}


void SDES::generateKeys(){
	if (key.size() == 10){
		string tmpKey = this->transformP10(key);
		tmpKey = this->leftShift(tmpKey, 1, 1);

		this->keys[0] = this->transformP8(tmpKey);
		tmpKey = this->leftShift(tmpKey, 2, 1);
		this->keys[1] = this->transformP8(tmpKey);
	}
}


string SDES::transformP4(string data){
	int perm4[] = { 1, 3, 2, 0 };
	string newData = "";
	for (int i = 0; i < 4; i++){
		newData += data[perm4[i]];
	}
	return newData;
}


string SDES::transformP8(string data){
	int perm8[] = { 5, 2, 6, 3, 7, 4, 9, 8 };
	string newData = "";
	for (int i = 0; i < 8; i++){
		newData += data[perm8[i]];
	}
	return newData;
}


string SDES::transformP10(string data){
	int perm10[] = { 2, 4, 1, 6, 3, 9, 0, 8, 7, 5 };
	string newData = "";
	for (int i = 0; i < 10; i++){
		newData += data[perm10[i]];
	}
	return newData;
}


string SDES::transformEP(string data){
	int perm4[] = { 3, 0, 1, 2, 1, 2, 3, 0 };
	string newData = "";
	for (int i = 0; i < 8; i++){
		newData += data[perm4[i]];
	}
	return newData;
}


string SDES::procFK(string leftData, string rightData, int keyIndex){
	if (leftData.size() != 4 && rightData.size() != 4)
		return NULL;

	string EP = this->transformEP(rightData);
	EP = (bitset<8>(EP) ^ bitset<8>(keys[keyIndex])).to_string();
	string leftSBox = this->procSBox(EP.substr(0, 4), 0);
	string rightSBox = this->procSBox(EP.substr(4, 4), 1);
	string P4 = this->transformP4(leftSBox + rightSBox);
	string xor = (bitset<8>(leftData) ^ bitset<8>(P4)).to_string().substr(4, 4);
	return xor;
}


string SDES::procSBox(string data, int index){
	vector<vector<string>> sBox;

	if (data.size() != 4){
		return data;
	}

	if (index == 0){
		vector<string> row;

		row.push_back("01");
		row.push_back("00");
		row.push_back("11");
		row.push_back("10");
		sBox.push_back(row);

		row.clear();
		row.push_back("11");
		row.push_back("10");
		row.push_back("01");
		row.push_back("00");
		sBox.push_back(row);

		row.clear();
		row.push_back("00");
		row.push_back("10");
		row.push_back("01");
		row.push_back("11");
		sBox.push_back(row);

		row.clear();
		row.push_back("11");
		row.push_back("01");
		row.push_back("11");
		row.push_back("10");
		sBox.push_back(row);
	}
	else if (index == 1) {
		vector<string> row;

		row.push_back("00");
		row.push_back("01");
		row.push_back("10");
		row.push_back("11");
		sBox.push_back(row);

		row.clear();
		row.push_back("10");
		row.push_back("00");
		row.push_back("01");
		row.push_back("11");
		sBox.push_back(row);

		row.clear();
		row.push_back("11");
		row.push_back("00");
		row.push_back("01");
		row.push_back("00");
		sBox.push_back(row);

		row.clear();
		row.push_back("10");
		row.push_back("01");
		row.push_back("00");
		row.push_back("11");
		sBox.push_back(row);
	}
	else {
		return NULL;
	}

	string col_box = "";
	col_box += data[1];
	col_box += data[2];
	int col = bitset<8>(col_box).to_ulong();

	string row_box = "";
	row_box += data[0];
	row_box += data[3];
	int row = bitset<8>(row_box).to_ulong();

	return sBox[row][col];
}


string SDES::initIP(string data){
	int ip[] = { 1, 5, 2, 0, 3, 7, 4, 6 };
	string newData = "";
	for (int i = 0; i < 8; i++){
		newData += data[ip[i]];
	}
	return newData;
}


string SDES::inverseIP(string data){
	int iip[] = { 3, 0, 2, 4, 6, 1, 7, 5 };
	string newData = "";
	for (int i = 0; i < 8; i++){
		newData += data[iip[i]];
	}
	return newData;
}


string SDES::leftShift(string data, int bits, int sep){
	int size = data.size();
	int mid = size / 2;
	
	if (sep == 0 && bits < size){
		string firstPart = data.substr(0, bits);
		string secondPart = data.substr(bits, size);
		return secondPart + firstPart;
	}
	else if (sep == 1 && size % 2 == 0 && bits < mid){
		string fisrtHalf = data.substr(0, mid);
		string secondHalf = data.substr(mid, mid);

		string firstPart = fisrtHalf.substr(0, bits);
		string secondPart = fisrtHalf.substr(bits, mid - bits);
		fisrtHalf = secondPart + firstPart;

		firstPart = secondHalf.substr(0, bits);
		secondPart = secondHalf.substr(bits, mid - bits);
		secondHalf = secondPart + firstPart;

		return fisrtHalf + secondHalf;
	}
	return data;
}