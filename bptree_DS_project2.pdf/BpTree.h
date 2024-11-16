
#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <map>

//bptree can used by indexnode and datanode
class BpTree {
private:
	BpTreeNode* root; // root of B +tree
	int			order;		// m children
	ofstream* fout; // file out
public:
	BpTree(ofstream* fout, int order = 3) { //constructor
		root = NULL; // root
		this->order = order; // order 3
		this->fout = fout;
	}
	~BpTree() {
		
	}
	/* essential */
	bool		Insert(LoanBookData* newData); // insert function
	bool		excessDataNode(BpTreeNode* pDataNode); // 
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; } // out root
	BpTreeNode* searchDataNode(string name); // to find data node
	bool deletenode(string name); // delete node
	bool searchBook(string name); // print bptree by name
	bool searchRange(string start, string end,ofstream* print);//print bp tree by ranage
	bool print(); // print bp tree
	void del_data_next_size2(BpTreeNode* data, string name);
	void del_data_pre_size2(BpTreeNode* data, string name);
	void change_indexdata(BpTreeNode* data, string name);
	void underflow_happend(BpTreeNode* data, BpTreeNode* p_data);
	void merge_front_index(BpTreeNode* parent, BpTreeNode* next,string name);
	void merge_back_index(BpTreeNode* parent, BpTreeNode* before,string name);
};

#endif
