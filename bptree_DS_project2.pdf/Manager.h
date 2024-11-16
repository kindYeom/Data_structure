#pragma once
#include "SelectionTree.h"
#include "BpTree.h"
#include <string>
#include <sstream>
#include<algorithm>
using namespace std;

class Manager
{
private:
	//char* cmd;
	BpTree* bptree;
	string book_data;
	SelectionTree* stree;
	int s;
	string line;// read function
	string cmd; // divid line


public:
	Manager(int bpOrder)	//constructor
	{
		bptree = new BpTree(&flog,bpOrder); // create bp tree
		stree = new SelectionTree(&flog);
		/* You must fill here */
	}


	~Manager()//destructor
	{
		free(bptree);
		free(stree);
	}
	ifstream floan_book;
	ifstream fin;
	ofstream flog;
	

	void run(const char* command);
	bool LOAD();
	bool ADD();

	bool SEARCH_BP_BOOK(string book);
	bool SEARCH_BP_RANGE(string start, string end);

	bool PRINT_BP();
	bool PRINT_ST();

	bool DELETE();
	
	void BP_DELETE(string name);
	void printErrorCode(int n);
	void printSuccessCode();

};

