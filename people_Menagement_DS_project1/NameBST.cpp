#include "NameBST.h"
#include "MemberQueue.h"
NameBST::NameBST() : root(nullptr) //	Initializing root
{

}
NameBST::~NameBST()
{

}

NameBSTNode* NameBST::getRoot()
{
	return root; // Return root
}

void NameBST::insert(MemberQueueNode *Q) {
	if (root == nullptr) { // If this is the first value to come in
		root = new NameBSTNode; //Create a New Node
		root->setdata(Q->getname(), Q->getage(), Q->getdate(), Q->gettype()); //The node becomes root.
	}
	else {
		NameBSTNode* leaf = new NameBSTNode; // Create a New Subnode
		NameBSTNode* branch = root;
		leaf->setdata(Q->getname(), Q->getage(), Q->getdate(), Q->gettype()); // Data entry

		while (1) {
			if (branch->getname().compare(leaf->getname()) > 0) { // When the dictionary order is faster
				if (branch->getLeft() == nullptr) {//Check the presence or absence of the left
					branch->setLeft(leaf);
					break;
				}
				else {
					branch = branch->getLeft(); //
				}
			}
			else {
				if (branch->getRight() == nullptr) {// Check the presence or absence of the right node.
					branch->setRight(leaf);
					break;
				}
				else {
					branch = branch->getRight(); //Go to that node
				}
			}
		}
	}
}

NameBSTNode *NameBST::search(string name) { // Search for names
	NameBSTNode* temp = root;
	do {
		if (temp->getname().compare(name) == 0) { // if the same print
			return temp;
		}
		else if (temp->getname().compare(name) > 0) { // Left if alphabetical order is fast
			temp = temp->getLeft();
		}
		else {
			temp = temp->getRight();// Left if alphabetical order is slow
		}
	} while (temp != nullptr); // Repeat until it's over
	return nullptr; // Output nullptr if no data
}

NameBSTNode* NameBST::search_p(string name) { // Exploring Parent Nodes
	NameBSTNode* temp = root;
	if (root->getname().compare(name) == 0) {// When it's the root node
		return root;
	}
	do {
		if (temp->getname().compare(name) == 0) { // When I found it
			return temp;
		}
		else if (temp->getname().compare(name) > 0) {//If the dictionary is forward, to the left node
			if (temp->getLeft()->getname().compare(name) == 0) //Existence verification
				return temp;
			else
				temp = temp->getLeft();
		}
		else {
			if (temp->getRight()->getname().compare(name) == 0) // If the dictionary is behind, to the right node
				return temp;
			else
				temp = temp->getRight();
		}
	} while (temp != nullptr);
	return nullptr; // Return nullptr if none exists
}

void  NameBST::print(NameBSTNode * branch,ofstream *x) { // namebst print

		if (branch->getLeft() != nullptr) { // Move if left node exists
		print(branch->getLeft(),x);//Recursive on the left
	}
		*x << branch->getname()<<"/" << branch->getage() << "/" << branch->getstartdate() << "/" << branch-> 
			getenddate()<<"/"<<endl;
		//output from the left node node
	if (branch->getRight() != nullptr) {//Verifying the presence of the right node
		print(branch->getRight(),x); // move
	}
	return; //return
}

void  NameBST::delete_name(string name) {// Delete values by name
	NameBSTNode* temp = search(name);
	NameBSTNode* temp_p = search_p(name);
	if (temp->getLeft() == nullptr && temp->getRight() == nullptr) {// not have any child nodes.
		if (temp_p->getLeft() == temp)
			temp_p->setLeft(nullptr);
		if (temp_p->getRight() == temp)
			temp_p->setRight(nullptr);
		free(temp); // Release Memory
		temp = nullptr;
	}
	else if ((temp->getLeft() == nullptr) ^ (temp->getRight() == nullptr)) {//If there is only one child node
		NameBSTNode* parent = search_p(name);
		if (temp->getLeft() != nullptr) { // temp If the left node
			if (temp == root) {
				root = temp->getLeft();
			}
			if (parent->getLeft() == temp) { // Determine whether to insert on the left or right side of the parent node.
				parent->setLeft(temp->getLeft()); //Insert on the left
				
				free(temp);// Release Memory
				temp = nullptr;
				return;
			}
			else {
				parent->setRight(temp->getLeft());//the right side of the right side
				free(temp); 
				temp = nullptr;
				return;
			}
		}
		else {// If you have a right node exists,
			if (temp == root) { // Verify temp is root
				root = temp->getRight(); 
				
				free(temp);
				temp = nullptr;
				return;
			}
			if (parent->getLeft() == temp) {//Determine if the parent node is left or right

				parent->setLeft(temp->getRight());
				
				free(temp);
				temp = nullptr;
				return;
			}
			else {
				parent->setRight(temp->getRight());
				
				free(temp);
				temp = nullptr;
				return;
			}
		}
	}
	else { // If you have two children,
		NameBSTNode* tempR = temp; // TempR2 is a function that will change the value.
		NameBSTNode* save = new NameBSTNode;
		temp = temp->getLeft(); // Move to left node
		
		while (temp->getRight() != nullptr) {// Find the largest value.
			temp = temp->getRight();
		}


	
		save->dataCopy(temp->getname(), temp->getage(), temp->getstartdate(), temp->getenddate());
		//Save the value after copying value
		delete_name(temp->getname());
		tempR->dataCopy(save->getname(), save->getage(), save->getstartdate(), save->getenddate());
		//Reflect Value	
		
		free(save);
		save = nullptr;
	}
}
