#include "stdafx.h"
#include "CipherBlockChaining.h"


CipherBlockChaining::CipherBlockChaining()
{
}


CipherBlockChaining::~CipherBlockChaining()
{
}


bool CipherBlockChaining::setKey(string key){
	if (key.c_str() != NULL){
		this->key = key;
		return true;
	}
	return false;
}


bool CipherBlockChaining::setVector(string vector){
	if (vector.c_str() != NULL){
		this->vector = vector;
		return true;
	}
	return false;
}


bool CipherBlockChaining::setPlaintext(string plain){
	if (plain.c_str() != NULL){
		this->plain = plain;
		return true;
	}
	return false;
}


bool CipherBlockChaining::setCiphertext(string cipher){
	if (cipher.c_str() != NULL){
		this->cipher = cipher;
		return true;
	}
	return false;
}


vector<string> CipherBlockChaining::encrypt(){
	std::vector<string> res;
	this->cipher = "";
	unsigned long vector_tmp = bitset<8>(vector).to_ulong();
	sdes.setKey(key);
	sdes.generateKeys();

	for (int i = 0; i < plain.size(); i++){
		unsigned long pchar = (unsigned long)plain.at(i) ^ vector_tmp;
		//unsigned long pchar = (unsigned long)plain.at(i) 
		sdes.setPlaintext(pchar);
		char cipher = sdes.encrypt();
		this->cipher += cipher;
		vector_tmp = cipher;
	}

	this->cipher += "\0";
	res.push_back(this->cipher);
	res.push_back(sdes.getKeys()[0]);
	res.push_back(sdes.getKeys()[1]);
	
	return res;
}


vector<string> CipherBlockChaining::decrypt(){
	std::vector<string> res;
	this->plain = "";
	unsigned long vector_tmp = bitset<8>(vector).to_ulong();
	sdes.setKey(key);
	sdes.generateKeys();
	
	for (int i = 0; i < cipher.size(); i++){
		sdes.setCiphertext(cipher.at(i));
		char plain = sdes.decrypt();
		this->plain += plain ^ vector_tmp;
		//this->plain += plain;
		vector_tmp = cipher.at(i);
	}
	
	this->plain += "\0";
	res.push_back(this->plain);
	res.push_back(sdes.getKeys()[0]);
	res.push_back(sdes.getKeys()[1]);

	return res;
}