#include "commonUse.h"

//void HashBlock::add2Block(char * name)
//{
//	this->Vec.push_back(name);
//}
//
//void HashBlock::printHashBlock()
//{
//	vector<char*>::iterator i = this->Vec.begin();
//	while (i!= this->Vec.end())
//	{
//		cout<<((char*) *i)<<" - ";
//		i++;
//	}
//}
//
//bool HashBlock::findMember(char * name)
//{
//	vector<char*>::iterator i = this->Vec.begin();
//	while (i!= this->Vec.end())
//	{
//		char * n = ((char*) *i);
//		if ( strcmp(n,name)==0)
//			return true;
//		i++;
//	}
//	return false;
//}
//
//void HashTable::add2Hash(char * name)
//{
//		this->hashBlock[getHash(name)].add2Block(name);
//}
//
//bool HashTable::found(char * name)
//{
//	return this->hashBlock[getHash(name)].findMember(name);
//}
//
//int HashTable::getHash(char * name)
//{
//	return (*name)%size::BIG_SIZE;
//}
//
//void HashTable::printHashTable()
//{
//	for (int i=0;i<size::BIG_SIZE;i++)
//		this->hashBlock[i].printHashBlock();
//}

string commonUse::int2string (int num)
{
	switch (num){
	case 0: return "0"; break;
	case 1: return "1"; break;
	case 2: return "2"; break;
	case 3: return "3"; break;
	case 4: return "4"; break;
	case 5: return "5"; break;
	case 6: return "6"; break;
	case 7: return "7"; break;
	case 8: return "8"; break;
	case 9: return "9"; break;
	default:
		return int2string(num/10).append(int2string(num%10));
	}
}

bool commonUse::equal_char(list <char*> L,list <char*> P)
{
	list<char*>::iterator i1=L.begin();
	list<char*>::iterator i2=P.begin();

	if (L.size()!=P.size())
		return false;
	else if ((L.empty()) && (P.empty()))
		return true;
	else
	{
		while ((i1!=L.end())&&(i2!=P.end()))
		{
			char * temp1=(char*)*i1;
			char * temp2=(char*)*i2;
			if (strcmp (temp1,temp2)!=0)
				return false;
			i1++;  i2++;
		}
		return true;
	}
}

void commonUse::divEndList(list <char*>& a, char*& b)
{
	b = *a.end();
	a.pop_back();
}

void commonUse::divBegList(list <char*>& a, char*& b)
{
	b = *a.begin();
	a.pop_front();
}

bool commonUse::exist(list <char *>L ,char * c)
{
	list<char *>::iterator i=L.begin();
	while (i!=L.end())
	{
		if (c == (char *)*i)
			return true;
		i++;
	}
	return false;
}