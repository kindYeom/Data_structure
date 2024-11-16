#include "TermsBST.h"

TermsBST::TermsBST() : root(nullptr)
{

}
TermsBST::~TermsBST()
{

}


TermsBSTNode* TermsBST::getRoot() //시작 반환
{
	return root;
}


void TermsBST::insert(MemberQueueNode* Q) {
	if (root == nullptr) { // If this is the first value to come in
		root = new TermsBSTNode; // Create a new node
		root->setdata(Q->getname(), Q->getage(), Q->getdate(), Q->gettype()); //	The node becomes root.
	}
	else {
		TermsBSTNode* leaf = new TermsBSTNode; // Create a New Subnode
		TermsBSTNode* branch = root;
		leaf->setdata(Q->getname(), Q->getage(), Q->getdate(), Q->gettype()); // date input

		while (1) {
			if (branch->getenddate().compare(leaf->getenddate()) > 0) { // When the dictionary order is faster
				if (branch->getLeft() == nullptr) {//Check the presence or absence of the left
					branch->setLeft(leaf);
					break;
				}
				else {
					branch = branch->getLeft(); //Move to that node
				}

			}
			else {
				if (branch->getRight() == nullptr) {// Check the right node exist.
					branch->setRight(leaf);
					break;
				}
				else {
					branch = branch->getRight(); // Go to that node
				}
			}
		}
	}
};


void  TermsBST::print(TermsBSTNode* branch, ofstream* x) {// print

	if (branch->getLeft() != nullptr) { //Verifying the presence of the left node.
		print(branch->getLeft(), x); // Recursive after moving

	}
	*x << branch->getname() << "/" << branch->getage() << "/" << branch->getstartdate() << "/" << branch->
		getenddate() << "/" << endl;// print self

	if (branch->getRight() != nullptr) {//Verifying the presence of the right node.
		print(branch->getRight(), x);
	}
	return;
}

void TermsBST::level_travel_distory(TermsBSTNode* node,int *count, NameBST * N_BST){
	if (node->getLeft() != nullptr) { // Check the presence of the left node
		level_travel_distory(node->getLeft(),count,N_BST); // Destruction
	}
	if (node->getRight() != nullptr) {//Check the existence of the right node
		level_travel_distory(node->getRight(),count,N_BST);// Destruction
	}
	N_BST->delete_name(node->getname());

	free(node);
	node = nullptr;
	*count = *count + 1;
	return;
}

int  TermsBST::delete_Term(string date,NameBST *N_BST) {
	int cout = 0;
	TermsBSTNode* temp = root;
	TermsBSTNode* temp_parent= root;
	do {
		if (temp->getenddate().compare(date) < 0) { // When the node has a previous date.
			if (temp == root) {// If it's a start address, move the start address and set it up
				if (temp->getRight() != nullptr)// Check whether the right node exists.
					root = temp->getRight(); // Change root node
				else
					root = nullptr; //If the right node does not exist, all nodes are released.
				if(temp->getLeft() != nullptr)// Check left node exist
				level_travel_distory(temp->getLeft(),&cout,N_BST);//Release all left nodes
				N_BST->delete_name(temp->getname()); // Remove its name from nameBST

				free(temp);
				temp = nullptr;
				cout++;
				temp = root;
			}
			else { // When it's not starting node,
				if (temp->getLeft() != nullptr) // Verify that the left node exists.
				level_travel_distory(temp->getLeft(),&cout,N_BST); // Release all nodes
				temp_parent->setLeft(temp->getRight()); // Connection
				N_BST->delete_name(temp->getname());
				
				free(temp);//Turn off the current address value
				temp = nullptr;
				cout++;
				temp = temp_parent->getLeft(); // Turn off the current address value
			}
			///Remove bst when there is no value left on the node
		}
		else { //When the node has a later date
			temp_parent = temp;
			temp = temp->getLeft();
		}
	
	} while (temp != nullptr);

	
		return cout;
}



void  TermsBST::delete_term_name(string name,string date) {//Delete data deleted from the name from the term
	TermsBSTNode* temp = root;
	TermsBSTNode* parent = root;
	while (temp->getname() != name) { //Check by name.
		if (temp->getenddate().compare(date) < 0) { //// When the node has a previous date.
			parent = temp; // Followed by temp
			temp = temp->getRight();// Go to the right node
		}
		else { //When the node has a later date
			parent = temp;
			temp = temp->getLeft();
		}
	}


	if (temp->getLeft() == nullptr && temp->getRight() == nullptr) {//You do not have any child nodes.
		
		free(temp); // memory free
		temp = nullptr;
	}
	else if ((temp->getLeft() == nullptr) ^ (temp->getRight() == nullptr)) {//If there is only one child node

		if (temp->getLeft() != nullptr) { // temp If the left node
			if (temp == root) {
				root = temp->getLeft();
			}
			if (parent->getLeft() == temp) { // Determine whether to insert on the left or right side of the parent node.
				parent->setLeft(temp->getLeft()); //Insert on the left
		
				free(temp);// memory free
				temp = nullptr;
				return;
			}
			else {
				parent->setRight(temp->getLeft());//Insertion on the right side
				
				(temp);
				temp = nullptr;
				return;
			}
		}
		else {// Temp If the right node exists
			if (temp == root) { // Verify temp is root
				root = temp->getRight();
			
				free(temp);
				temp = nullptr;
				return;
			}
			if (parent->getLeft() == temp) {//Determine if the parent node is left or right

				parent->setLeft(temp->getRight());//On the left side of the parent node
				
				free(temp);
				temp = nullptr;
				
				return;
			}
			else {
				parent->setRight(temp->getRight());//On the right side of the parent node
			
				free(temp);
				temp = nullptr;
				return;
			}
		}
	}
	else { // If you have two child nodes
		TermsBSTNode* tempR = temp; // TempR2 is a function that will change the value.
		TermsBSTNode* save = new TermsBSTNode;
		temp = temp->getLeft(); // Move to left node
		while (temp->getRight() != nullptr) {// Find the largest value.
			temp = temp->getRight();
		}
		
		save->dataCopy(temp->getname(), temp->getage(), temp->getstartdate(), temp->getenddate());
		// Copy and temporarily save values
		delete_term_name(temp->getname(), temp->getenddate());
		tempR->dataCopy(save->getname(), save->getage(), save->getstartdate(), save->getenddate());
		//Reflect Value
		if (tempR->getLeft()->getage() < 0)
			tempR->setLeft(nullptr);
		if (tempR->getRight()->getage() < 0)
			tempR->setRight(nullptr);
		free(save);
		save = nullptr;
	}

}