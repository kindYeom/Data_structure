#include "SelectionTree.h"
#include "LoanBookData.h"
#include "LoanBookHeap.h"

bool SelectionTree::Insert(LoanBookData* newData) {// Add selection tree data from bptree
	SelectionTreeNode* temp2 = Selectionmap.find(newData->getCode())->second;
	if (Selectionmap.find(newData->getCode())->second->getHeap() == NULL) {// Check heap data in the corresponding selection tree
		Selectionmap.find(newData->getCode())->second->setHeap(new LoanBookHeap); //Create if none exists
		Selectionmap.find(newData->getCode())->second->getHeap()->Insert(newData);// Add Data
 		Selectionmap.find(newData->getCode())->second->setBookData(
		Selectionmap.find(newData->getCode())->second->getHeap()->getRoot()->getBookData()//Update Selection Tree Data
		);
	}
	else {
		Selectionmap.find(newData->getCode())->second->getHeap()->Insert(newData); //Add as is if present
		Selectionmap.find(newData->getCode())->second->setBookData(
			Selectionmap.find(newData->getCode())->second->getHeap()->getRoot()->getBookData()// Data update
		);
	}
	SelectionTreeNode* temp;
	temp = Selectionmap.find(newData->getCode())->second->getParent();
 	while (temp != NULL) {
	
		if (temp->getLeftChild()->getBookData() == NULL) { //If the opposite value is the value of you, you win
			temp->setBookData(temp->getRightChild()->getBookData());
			temp = temp->getParent();
		
		}
		else if (temp->getRightChild()->getBookData() == NULL) {//If the opposite value is the value of you, you win
			temp->setBookData(temp->getLeftChild()->getBookData());
			temp = temp->getParent();

		}
		else {
			int i = 0;
			while ((temp->getLeftChild()->getBookData()->getName()[i])// Start Comparison
				==
			(temp->getRightChild()->getBookData()->getName()[i]))
				i++;
			if ((temp->getLeftChild()->getBookData()->getName()[i]) // Compare left node to right node
					>
				(temp->getRightChild()->getBookData()->getName()[i])) {
				temp->setBookData(temp->getRightChild()->getBookData()); // Copy right data
				temp = temp->getParent(); // Go to parent node

			}
			else {
				temp->setBookData(temp->getLeftChild()->getBookData()); //Copy left data
				temp = temp->getParent();//Go to parent node

			}
		}
	}
	return 0;
}

bool SelectionTree::Delete() {

	if (root->getBookData()==NULL)
		return false;
	LoanBookHeap* heap;
	LoanBookHeapNode* heapnode;
	heap = Selectionmap.find(root->getBookData()->getCode())->second->getHeap(); //Delete from the top node
	if (heap->getCount() == 1) { // Delete root node and release memory if there is one data
		heap->getRoot()->setBookData(NULL);// 
		free(heap->getRoot()); // free to memory
		heap->setRoot(NULL);
		heap->countdown(); /// count --
		Selectionmap.find(root->getBookData()->getCode())->second->setBookData(NULL); // Reflect to selection tree
	}
	else {
		heapnode = heap->div(heap->getCount());//Alignment of Heap Nodes

		if (heap->getLast() == 0) { // last is  0-> left
			heapnode = heapnode->getLeftChild(); // move left
			heap->getRoot()->setBookData(heapnode->getBookData());// insert root
			heapnode->getParent()->setLeftChild(NULL);
			free(heapnode); //free to memory
			heap->countdown(); // count down

		}
		else {
			heapnode = heapnode->getRightChild(); // other is right
			heap->getRoot()->setBookData(heapnode->getBookData()); // insert root
			heapnode->getParent()->setRightChild(NULL);
			free(heapnode);// free to memort
			heap->countdown();// count down
		}
		heap->heapifyDown(heap->getRoot()); // sort by down
		Selectionmap.find(root->getBookData()->getCode())->second->setBookData(heap->getRoot()->getBookData());
	}

	///Delete data and change ranking in heap

	/// Rearrangement of the selection tree


	SelectionTreeNode* temp;
	temp = Selectionmap.find(root->getBookData()->getCode())->second->getParent();
	while (temp != NULL) {

		if (temp->getLeftChild()->getBookData() == NULL) { // Winner if opposite value is null
			temp->setBookData(temp->getRightChild()->getBookData());
			temp = temp->getParent();

		}
		else if (temp->getRightChild()->getBookData() == NULL) {	// Winner if opposite value is null
			temp->setBookData(temp->getLeftChild()->getBookData());
			temp = temp->getParent();

		}
		else {
			int i = 0;
			while ((temp->getLeftChild()->getBookData()->getName()[i])
				==
				(temp->getRightChild()->getBookData()->getName()[i]))
				i++;
			if ((temp->getLeftChild()->getBookData()->getName()[i])
					>
				(temp->getRightChild()->getBookData()->getName()[i])) {
				///comapre
				temp->setBookData(temp->getRightChild()->getBookData());// if right winner
				temp = temp->getParent();// go to parent

			}
			else {
				temp->setBookData(temp->getLeftChild()->getBookData());// if left winner
				temp = temp->getParent(); // go to parent

			}
		}
	}

	return true;

}

bool SelectionTree::printBookData(int bookCode) { // print book data by code
	LoanBookHeapNode *copy_root, *temp,*temp2;
	LoanBookHeap * Heapnode = new LoanBookHeap;

	if (Selectionmap.find(bookCode)->second->getHeap() == NULL) // make copide heap
		return false;
	copy_root = Selectionmap.find(bookCode)->second->
		deepCopy(Selectionmap.find(bookCode)->second->getHeap()->getRoot());
	Heapnode->setRoot(copy_root); // setting
	Heapnode->setCount(Selectionmap.find(bookCode)->second->getHeap()->getCount());

	*fout << "========PRINT_ST========" << endl; // print root data
	while (Heapnode->getRoot() != NULL) {
		*fout << Heapnode->getRoot()->getBookData()->getName() << "/"
			<< Heapnode->getRoot()->getBookData()->getCode() << "/"
			<< Heapnode->getRoot()->getBookData()->getAuthor() << "/"
			<< Heapnode->getRoot()->getBookData()->getYear() << "/"
			<< Heapnode->getRoot()->getBookData()->getLoanCount() << endl;
	
			if(Heapnode->getCount() == 1) { // count =  1 oprint root
				Heapnode->getRoot()->setBookData(NULL);
			free(Heapnode->getRoot());
			Heapnode->setRoot(NULL);
			Heapnode->countdown();// count down
			}
			else {
				temp = Heapnode->div(Heapnode->getCount()); /// find where last data insert

				if (Heapnode->getLast() == 0) { //left
					temp2 = temp; // to make child null
					temp =temp->getLeftChild();
					temp2->setLeftChild(NULL);// is empty
					Heapnode->getRoot()->setBookData(temp->getBookData());
					free(temp);
					Heapnode->countdown();

				}
				else {
					temp2 = temp;// to make child null
					temp = temp->getRightChild();
					temp2->setRightChild(NULL); // is empty
					Heapnode->getRoot()->setBookData(temp->getBookData());
					free(temp);
					Heapnode->countdown(); // count down
				}
				Heapnode->heapifyDown(Heapnode->getRoot());
				
			}
	}
	*fout << "========================" << endl;

		return true;
	
}