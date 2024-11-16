#pragma once
using namespace std;
#include "string"
#include "NameBSTNode.h"
#include "MemberQueueNode.h"
#include <fstream>

class NameBST
{
private:
	NameBSTNode * root;
	
public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot();

	void insert(MemberQueueNode* Q);
	NameBSTNode *search(string name);
	NameBSTNode* search_p(string name);

	void print(NameBSTNode *banch,ofstream *x);
	void delete_name(string name);
};