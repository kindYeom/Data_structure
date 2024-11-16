#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_
#include <map>
#include "BpTreeNode.h"

class BpTreeIndexNode : public BpTreeNode {
private:
	map <string, BpTreeNode*> mapIndex; // map index to store data

public:
	BpTreeIndexNode() {};
	~BpTreeIndexNode() {

	};


	void insertIndexMap(string name, BpTreeNode* pN) { // insert dara in index map
		mapIndex.insert(map<string, BpTreeNode*>::value_type(name, pN));

	}

	void deleteMap(string name) {// delete data in index map

		mapIndex.erase(name);
	}


	map <string, BpTreeNode*>* getIndexMap() { return &mapIndex; }

};

#endif