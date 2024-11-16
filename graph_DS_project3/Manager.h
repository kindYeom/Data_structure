#ifndef _MANAGER_H_
#define _MANAGER_H_


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "GraphMethod.h"

using namespace std;

class Manager{	
private:
	Graph* graph;	
	ofstream fout;	
	string data1;
	string data2;

	char type;
	int load;
	int G_data[3];

public:
	Manager();	
	~Manager();	

	void run(const char * command_txt);
	
	bool LOAD(const char* filename);	
	bool PRINT();	
	bool mBFS(char option, int vertex);	
	bool mDFS(char option, int vertex);	
	bool mDIJKSTRA(char option, int vertex);	
	bool mKRUSKAL();	
	bool mBELLMANFORD(char option, int s_vertex, int e_vertex);	
	bool mFLOYD(char option); 
	bool mKwoonWoon(int vertex);
	void printErrorCode(int n); 
};

#endif