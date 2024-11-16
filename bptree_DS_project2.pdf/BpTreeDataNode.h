#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_
#include <map>
#include "BpTreeNode.h"

class BpTreeDataNode : public BpTreeNode
{
private:
	map <string, LoanBookData*> mapData; // order 3 map
	BpTreeNode* pNext; // next node
	BpTreeNode* pPrev;// Prev node
public:
	BpTreeDataNode() {
		pNext = NULL; // set value null
		pPrev = NULL;
	}
	~BpTreeDataNode() {

	}

	void setNext(BpTreeNode* pN) { pNext = pN; }
	void setPrev(BpTreeNode* pN) { pPrev = pN; }
	BpTreeNode* getNext() { return pNext; }
	BpTreeNode* getPrev() { return pPrev; }



	void insertDataMap(string name, LoanBookData* pN) {//insert data in map
		mapData.insert(map<string, LoanBookData*>::value_type(name, pN)); // insert data

		
	}

	void deleteMap(string name) {//delete data in map
		mapData.erase(name);
	}
	map<string, LoanBookData*>* getDataMap() { return &mapData; } // 
};

#endif
