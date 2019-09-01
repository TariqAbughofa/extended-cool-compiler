#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

//enum size{
//BIG_SIZE=30,	//NAMESPACE, CLASS : 30
//NORMAL_SIZE=20,	//SCOPE, method  : 20
//SMALL_SIZE=10	//INTERFACE: 10
//};
//
//class HashBlock
//{
//private:
//	vector<char *> Vec;
//public:
//	void add2Block(char * );
//	void printHashBlock();
//	bool findMember(char *);
//};
//
//class HashTable
//{
//private:
//	HashBlock hashBlock[size::BIG_SIZE];
//public:
//	void add2Hash(char * name);
//	int getHash(char * name);
//	void printHashTable();
//	bool found(char * name);
//};

class commonUse
{
public:
	static string int2string (int );
	static bool equal_char(list <char*> ,list <char*>);
	static void divEndList(list <char*>&, char*&);
	static void divBegList(list <char*>&, char*&);
	static bool exist(list <char *>,char *);
};