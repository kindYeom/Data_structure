#include "BpTree.h"

using namespace std;
//complete//
bool BpTree::Insert(LoanBookData* newData) { // insert data
 	if (this->root == NULL) { // insert new data node
		root = new BpTreeDataNode; // set root
		root->insertDataMap(newData->getName(), newData);//make new node
	}
	else {
		BpTreeNode* temp;
		temp = searchDataNode(newData->getName()); // find DATA node to insert

			temp->insertDataMap(newData->getName(), newData); // if met data node new data insert
			
			if (excessDataNode(temp) == true) {// map over 3 divide
			
				splitDataNode(temp); //split data node
			}
		}
	return true;
}


	bool BpTree::excessDataNode(BpTreeNode * pDataNode) {
		if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
		else return false;
	}

	bool BpTree::excessIndexNode(BpTreeNode * pIndexNode) {
		if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
		else return false;
	}

	void BpTree::splitDataNode(BpTreeNode* pDataNode) { // split data node
		BpTreeNode* temp;
		auto element = std::next(pDataNode->getDataMap()->begin(), (order - 1) / 2); // get second location 

		BpTreeDataNode* new_data = new BpTreeDataNode; //map to divide

		new_data->setNext(pDataNode->getNext());//send pointer i point

		pDataNode->setNext(new_data); //point to divded data node
		new_data->setPrev(pDataNode);//point to divded node
		new_data->getDataMap()->insert(element, pDataNode->getDataMap()->end()); 
		//divde to new node
		pDataNode->getDataMap()->erase(element, pDataNode->getDataMap()->end());
		// erase data we divide
		
		if (pDataNode->getParent() == NULL) { //if it doesn't have upper index
			temp = new BpTreeIndexNode; // make new index
			pDataNode->setParent(temp); // set parent
			new_data->setParent(temp); // set parent.
			temp->setMostLeftChild(pDataNode); // set child.
			temp->insertIndexMap(new_data->getDataMap()->begin()->first, new_data); 
			//insert data in index map
			root = temp; //it will be root node
		}
		else { // already has index node plus
			new_data->setParent(pDataNode->getParent()); // get parent
			temp = pDataNode->getParent(); // get child
			temp->insertIndexMap(new_data->getDataMap()->begin()->first, new_data); // add index node
			
			if (excessIndexNode(temp) == true) { //when over size 3
				splitIndexNode(temp); // split node
			}

		}
	}


	void BpTree::splitIndexNode(BpTreeNode * pIndexNode) { //split index node
		auto element = pIndexNode->getIndexMap()->begin();

		BpTreeNode *new_index = new BpTreeIndexNode;//get splited data
		advance(element, 1);//middle data
		element->second->setParent(new_index); // to chage parent
		new_index->setMostLeftChild(element->second);//left side of parent


		element = pIndexNode->getIndexMap()->begin();
		advance(element, 2); //move data
		new_index->insertIndexMap(element->first, element->second);
		new_index->getIndexMap()->begin()->second->setParent(new_index);
		pIndexNode->deleteMap(element->first); // delete last data
	

		if (pIndexNode->getParent() == NULL) {//if no data in index node 
			BpTreeNode* new_parent = new BpTreeIndexNode; // make new node
			new_index->setParent(new_parent); // parent
			pIndexNode->setParent(new_parent);// parent
			element = pIndexNode->getIndexMap()->begin();
			advance(element, 1);//middle node
			new_parent->insertIndexMap(element->first, new_index); // give data
			new_parent->setMostLeftChild(pIndexNode); // set most left child
			root = new_parent;// set root
			pIndexNode->deleteMap(element->first); //delete middle data
		}
		else {
			BpTreeNode* temp;
			temp = pIndexNode->getParent();
			new_index->setParent(temp); // link with parent
		
			element = pIndexNode->getIndexMap()->begin();
			advance(element, 1);//middle data
			temp->insertIndexMap(element->first, new_index); //insert index map
			pIndexNode->deleteMap(element->first); //delete middle data
			if (excessIndexNode(pIndexNode->getParent()) ==true) { //if pareent index need split
				splitIndexNode(pIndexNode->getParent());
			}
		}
	}

	BpTreeNode* BpTree::searchDataNode(string name) {
			BpTreeNode* pCur = root;

		if (pCur->getMostLeftChild() == NULL) { // to check index or datanode
			return pCur;//if data node insert here

		}
		else { // if index node find data node to store
			
			string key; //key of node
			

				while (pCur->getMostLeftChild() != NULL) { //  find data node exit
				while (1) {
					int i = 0;
					auto it = pCur->getIndexMap()->begin(); // start index node

 					key = it->first; // get key of first map
 						while ((key[i]) == (name[i])&&key[i] != NULL&& name[i] != NULL)//compare
						i++;

						if (key[i] == NULL && name[i] == NULL) {
						//it is same (is used search)
								pCur = it->second;//go second
								break;
						}
						else if ((key[i]) > (name[i])) { //key is bigger than name
						if (key.compare(it->first) == 0) {// when it is first map data
							pCur = pCur->getMostLeftChild();// most left node
							break;
						}
						else {// second map
							pCur =  it->second; // go second
							break;
						}
					}
					else { // ket is small
						if (pCur->getIndexMap()->size() == 1) { // in map one data
							pCur =   it->second; // go second
							break;
						}
						else {
							advance(it, 1); // go next
						}

						key = it->first; // call key of first
						i = 0;
						while ((key[i]) == (name[i]) && key[i] != NULL && name[i] != NULL)// compare
							i++;
						if (key[i] == NULL && name[i] == NULL) { // when it same
							if (pCur->getMostLeftChild()->getMostLeftChild() == NULL) {
								pCur = it->second;// go second
								break;
							}
							pCur = pCur->getIndexMap()->begin()->second;
							break;
						}
						else if((key[i]) > (name[i])) {//key is bgigger
							pCur = pCur->getIndexMap()->begin()->second; // go second
							break;
						}
						else {
							pCur =  it->second; // go last map
							break;
						}
					}
				}
			}
		}
		return pCur;
	}

	bool BpTree::searchBook(string name) { 
		BpTreeNode* temp = searchDataNode(name);// go node mabye name stroe
		if(temp->getDataMap()->find(name)== temp->getDataMap()->end()) // exist?
		return false;

		return true;
	}
	
	bool BpTree::searchRange(string start, string end,ofstream *print) {
		BpTreeNode* temp = searchDataNode(start);// go data node maybe start
		LoanBookData* data;

			auto it = temp->getDataMap()->begin();
			while (it->first[0] !=start[0]&&it->first[0]<=end[0]) { //to find data satisfying the conditions
				advance(it, 1);
				if (it == temp->getDataMap()->end()) {
					if (temp->getNext() == NULL)
						return false; // no data
					temp = temp->getNext();
					 it = temp->getDataMap()->begin();
				}


			}
			if (it->first[0] > end[0]) // print 
				return false;
			*print << "========SEARCH_BP========"<<endl;
			while (temp != NULL) {
				if (it->first[0] > end[0])
					break;

				data = it->second; // print
				*print << data->getName() << "/" << data->getCode() << "/" << data->getAuthor() << "/" << data->getYear() << "/"
					<< data->getLoanCount() << endl;
				advance(it, 1);
				if (it == temp->getDataMap()->end()) {
					temp = temp->getNext();
					if (temp == NULL)//no more data
						break;
					it = temp->getDataMap()->begin();
				}

			}
		
			*print << "=========================="<<endl; 
			return true;

	}
	bool BpTree::print() {
		if (root == NULL) // no data-> false
			return false;

		BpTreeNode* temp = root; // go root
			while (temp->getMostLeftChild() != NULL)  // move first data of bpnode
				temp = temp->getMostLeftChild();
		
			while (temp != NULL) { // print all data Circulating Data Nodes
				auto it = temp->getDataMap()->begin();
				while (it != temp->getDataMap()->end()) {
					
					*fout << it->second->getName() << "/" << it->second->getCode() << "/" <<
						it->second->getAuthor() << "/" << it->second->getYear()<< "/" << it->second->getLoanCount()<<endl;
					advance(it, 1);
				}
				temp = temp->getNext();
			}
			return true; // end
	}

	bool BpTree::deletenode(string name) {
		BpTreeNode* data = searchDataNode(name), * p_data;// move data node
		BpTreeNode* merge;
		BpTreeNode* Index = data->getParent(); // parents of data node
		int cases;
		/////////////////////case1 it is not the fisrt node////////////////////////////////
		if (data->getDataMap()->begin()->first.compare(name) != 0) { // name is not fisrst node
			data->deleteMap(name);
			return true;
		}
		///////case2 : it is first node but size is over 1//////////////////////
		if (data->getDataMap()->size() > 1) {
			data->deleteMap(name);//delete map-
			change_indexdata(data, name); // chage parent
			return true;
		}

		/////////////////////case3 data node only has one node////////////////////////////////

		if (data->getDataMap()->size() == 1) {
			if (Index == NULL) { // only one data remain
				data->deleteMap(name);
				std::free(data);
				root = NULL;
				return true;
			}

			///which node share parent
			if (data->getNext() == NULL)
				cases = 2; // p is pre
			else	if (data->getPrev() == NULL)
				cases = 3; // p is next
			else if (data->getNext()->getParent() == Index && data->getPrev()->getParent() == Index)
				cases = 1; // both is p
			else if (data->getPrev()->getParent() == Index)
				cases = 2; // p is pre
			else
				cases = 3; // p is next


			if (cases == 1) { // both is partner parent has two index
				if (data->getNext()->getDataMap()->size() > 1) {
					del_data_next_size2(data, name); // divdie other data node
					return true;
				}
				if (data->getPrev()->getDataMap()->size() > 1) {
					del_data_pre_size2(data, name); // divide other data node
					return true;
				}
				//line data node
				data->getPrev()->setNext(data->getNext()); 
				data->getNext()->setPrev(data->getPrev());
				data->deleteMap(name); // delete data map
				std::free(data); // memory free
				Index->deleteMap(name);//delete in index node
			}

			else	if (cases == 3) { // partner is next
				p_data = data->getNext();
				if (data->getNext()->getDataMap()->size() > 1) { // partner has 2 node
					del_data_next_size2(data, name);
					return true;
				}
				else {//has just one data
					if (Index->getIndexMap()->size() > 1) { // inedx data got two data
						data->setNext(p_data->getNext());
						p_data->setPrev(data);//link both data node
						data->insertDataMap(p_data->getDataMap()->begin()->first, p_data->getDataMap()->begin()->second);
						//get new data
						std::free(p_data);
						data->deleteMap(name);
						Index->deleteMap(data->getDataMap()->begin()->first); // delete in data
						change_indexdata(data, name); // parent has deleted data key the change
						return true;
					}
					else {
						//under flow happend
						underflow_happend(data,p_data);
					}
				}
			}

			else {// prev is partner
				p_data = data->getPrev();
				if (data->getPrev()->getDataMap()->size() > 1) { // partner has over two node
					del_data_pre_size2(data, name);
					return true;
				}
				else {//partner has just one data
					
					if (Index->getIndexMap()->size() > 1) { // parent index got two index
						data->getPrev()->setNext(data->getNext()); // link both side data node
						data->getNext()->setPrev(data->getPrev());
						data->deleteMap(name); // delete data node
						std::free(data); //free memory
						Index->deleteMap(name); // delete in index
						return true;
					}
					else {
						// underflow happend 
						underflow_happend(data,p_data);	
					}
				}
			}
		}
	};


	void BpTree::del_data_pre_size2(BpTreeNode* data, string name) {
		BpTreeNode* p_data;// move to deleted data
		BpTreeNode* merge;
		BpTreeNode* Index = data->getParent(); // parents of data node
		string s1;
		p_data = data->getPrev();//partner is Prev
		// partner has two node
		data->insertDataMap(p_data->getDataMap()->rbegin()->first,
			p_data->getDataMap()->rbegin()->second); // give last node to data

		data->deleteMap(name);
		change_indexdata(data, name);
		p_data->deleteMap(data->getDataMap()->begin()->first);

	};

void BpTree::del_data_next_size2(BpTreeNode* data, string name) {
	BpTreeNode* p_data;// move to deleted data
	BpTreeNode* merge;
	BpTreeNode* Index = data->getParent(); // parents of data node
	string s1;
	p_data = data->getNext(); // partner is next

	// partner has two node
	data->insertDataMap(p_data->getDataMap()->begin()->first,
		p_data->getDataMap()->begin()->second); // give first node to data
	data->deleteMap(name);

	s1 = p_data->getDataMap()->begin()->first; // 
	p_data->deleteMap(s1);//delete data  node
	change_indexdata(p_data, s1);
	//Since the first node of the split node becomes the first node, 
	//execution starts from the split node to prevent duplication.
	change_indexdata(data, name);
}

void BpTree::change_indexdata(BpTreeNode* data, string name) {

 	BpTreeNode* Index=data->getParent();
	BpTreeNode* merge;
	while (Index != NULL) { // Explore to the end
		if (Index->getIndexMap()->find(name) != Index->getIndexMap()->end()) { // Change only key values when data exists on index nodes
			merge = Index->getIndexMap()->find(name)->second; // Only data pointed at existing index nodes is taken out
			Index->deleteMap(name); // Delete data from that index
			//To keep the data and take out the key value only.
			Index->insertIndexMap(data->getDataMap()->begin()->first, merge); // \

			break;
		}
		Index = Index->getParent();// Move to the next parent node.
	}
	return;
}

void BpTree::underflow_happend(BpTreeNode* data, BpTreeNode* p_data) {
	string find = data->getDataMap()->begin()->first;//Gets the name to delete
	BpTreeNode* parent = data->getParent(); // parents of the data node
	BpTreeNode* merge; // 
	BpTreeNode*G_parent = data->getParent()->getParent(); // Parent of the parent of that data node
	//*Combining Data Nodes
	if (parent->getMostLeftChild() == data) {
		data->insertDataMap(p_data->getDataMap()->begin()->first, p_data->getDataMap()->begin()->second);//insert parnet data
		data->setNext(p_data->getNext());
		p_data->getNext()->setPrev(data);
		free(p_data);
	}
	else// Data stored in msb of parent
	{
		p_data->insertDataMap(data->getDataMap()->begin()->first, data->getDataMap()->begin()->second);//insert partner datad
		p_data->setNext(data->getNext());
		data->getNext()->setPrev(p_data);
		free(data);
	}
	data = parent->getMostLeftChild();

	data->deleteMap(find); // Delete its name from the data node
	//** Empty parent node
	parent->getIndexMap()->clear();

	change_indexdata(data, find);// Change the name when a node with its data name exists in the parent index

	G_parent = data->getParent()->getParent();// See if the ancestors exist.
	if (G_parent == NULL) { // An index node exists and there are only two data nodes left
		free(data->getParent());
		root = data; // Change root node to data node
		return;
	}
	///////////////////////////////////////////////////////////////////////////////////

	if (G_parent->getIndexMap()->size() > 1) {// Ancestor(s exist, check the number of indexes.
		//case
		if (parent == G_parent->getMostLeftChild()) {//first
			if (G_parent->getIndexMap()->begin()->second->getIndexMap()->size() > 1) { //If there are two opposite nodes
				merge_front_index(parent, G_parent->getIndexMap()->begin()->second, G_parent->getIndexMap()->begin()->first);
				return;
			}
		}
		if (parent == G_parent->getIndexMap()->begin()->second) {
			if (G_parent->getMostLeftChild()->getDataMap()->size() > 1) {
			merge_back_index(parent, G_parent->getMostLeftChild(), G_parent->getIndexMap()->begin()->first);
				return;
			}
			if (G_parent->getIndexMap()->rbegin()->second->getIndexMap()->size() > 1) {
				merge_front_index(parent, G_parent->getIndexMap()->rbegin()->second, G_parent->getIndexMap()->rbegin()->first);
				return;
			}
		
		}// middle

			if (parent == G_parent->getIndexMap()->rbegin()->second) {
				if (G_parent->getIndexMap()->begin()->second->getIndexMap()->size() > 1) { //If there are two opposite nodes
					merge_back_index(parent, G_parent->getIndexMap()->begin()->second, G_parent->getIndexMap()->rbegin()->first);
					return;
				}
			} // last



		return;
	}
	else { //
		if (G_parent->getMostLeftChild() == parent) { // If it's the left node of the left node.
			if (G_parent->getIndexMap()->begin()->second->getIndexMap()->size() > 1) { //If there are two opposite nodes

				merge_front_index(parent,G_parent->getIndexMap()->begin()->second, G_parent->getIndexMap()->begin()->first);
				return;
			}else { // If there is only one opposite node
				*fout << "sorry i can't consider this " << endl;
				return;
			}
		}
		else { ///For the right node of the ancestor.
			if (G_parent->getMostLeftChild()->getIndexMap()->size() > 1) { //If there are two opposite nodes
				merge_back_index(parent, G_parent->getMostLeftChild(), G_parent->getIndexMap()->begin()->first);
				return;
			}
			else { // If there is only one opposite node
				*fout << "sorry i can't consider this "<<endl;
				return;
			}

		}
		return;
	}
		
}

void  BpTree::merge_back_index(BpTreeNode* parent, BpTreeNode* Before,string name) {
	BpTreeNode* G_parent = parent->getParent();

	parent->insertIndexMap(name, parent->getMostLeftChild()); //inset index node
	parent->setMostLeftChild(Before->getIndexMap()->rbegin()->second); // set most left child  before data node

	G_parent->deleteMap(name); // delete G parent
	G_parent->insertIndexMap(Before->getIndexMap()->rbegin()->first, parent);// Create a new ancestors
	Before->deleteMap(Before->getIndexMap()->rbegin()->first);
	//delete data in divided node

	return;
}

void  BpTree::merge_front_index(BpTreeNode* parent, BpTreeNode* next, string name) {
	BpTreeNode* G_parent = parent->getParent();
	parent->insertIndexMap(name, next->getMostLeftChild());// send next parent's most left child to current parent
	//child data nodes connecting to each other
	G_parent->deleteMap(name);
	G_parent->insertIndexMap(next->getIndexMap()->begin()->first, next);// Creating a new ancestor
	parent->getMostLeftChild()->setNext(next->getMostLeftChild()); // Connect between data nodes
	next->getMostLeftChild()->setPrev(parent->getMostLeftChild()); //Connect between data nodes
	next->setMostLeftChild(next->getIndexMap()->begin()->second);//MLC chabge
	next->deleteMap(next->getIndexMap()->begin()->first); // delete data
	return;
}
