#include "TermsList.h"
TermsLIST::TermsLIST()
{
	head = nullptr;
};
TermsLIST::~TermsLIST()
{

};

TermsListNode* TermsLIST::getHead()	{return head;};

void TermsLIST::insert(char type, MemberQueueNode* Q) { // Add a value to the term list
	if (head == nullptr) { // If the first value was entered
		head = new TermsListNode; //	Save that value in the header.
		head->settype(type); //Save type of type
		head->setTermBST(new TermsBST); // bst generation
		head->gettermbst()->insert(Q);//Create bst root

	}
	else {
		TermsListNode* temp = head; // Start position
		do {
			if (temp->gettype() == type) { // Verify that the type is already in.
				temp->increase_member(); // an increase in membership.
				temp->gettermbst()->insert(Q);
				break;
			}
			else if (temp->getNext() == nullptr) { // Check the end of the node -> No such type does not exist
				temp->setNext(new TermsListNode); // Create a new node, point to view new nodes
				temp = temp->getNext(); // Connect created nodes
				temp->settype(type);// Type Setting
				temp->setTermBST(new TermsBST); // Create bst
				temp->gettermbst()->insert(Q);// bst root »ý¼º
				break;
			}
			else {
				temp = temp->getNext(); // Use for node navigation
			}
		} while (1); // Shutdown due to break

	}

};

TermsListNode *TermsLIST::search(string type){
	TermsListNode* temp = head; // Termlist Start Address
	while (temp != nullptr) {
		if (temp->gettype() != type.at(0)) { //	I'm sure the data type..	
			temp = temp->getNext();
		}
		else {
			return temp;
		}
	}
	return nullptr; // If it doesn't exist
}

void TermsLIST::delete_list(string date,NameBST *N_BST) {
	TermsListNode* temp = head;
	TermsListNode* temp2 = head;
	while (temp!= nullptr) {
		temp->setmember(temp->gettermbst()->delete_Term(date,N_BST)); // deleting, reflecting the number of members
		if (temp->getmember()==0) { // When there are 0 members
			if (temp == head) { //Replace the head if it is a head node
				head = temp->getNext();
			}
			else {
				while (temp2->getNext() != temp) { // temp go to parent
					temp2 = temp2->getNext();//go next node
				}
				temp2->setNext(temp->getNext()); //link node
			}

			free(temp); //Clearing Empty Termlist
			temp = temp2;
		}


		temp = temp->getNext(); // Move to next node
	}
		return;

	}


void TermsLIST::delete_list_name(string data, char type,string enddate) {
	TermsListNode* temp = head;
	TermsListNode* temp2 = head;
	while (temp->gettype() != type) { //Move to Type Position
		temp = temp->getNext();
	}
	temp->gettermbst()->delete_term_name(data,enddate); // Run Data Delete

	temp->setmember(1); // reduce the number of members

	if (temp->getmember() == 0) { //When there are 0 members
		if (temp == head) { // Replace the head if it is a head node
			head = temp->getNext();
		}
		else {
			while (temp2->getNext() != temp) { //	Move to the temp parents
				temp2 = temp2->getNext();// Move to the next node
			}
			temp2->setNext(temp->getNext()); // node connection
		}

		free(temp); //Remove blank tum list;
		temp = temp2;
	}


	

}