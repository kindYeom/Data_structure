#include "LoanBookHeap.h"
#include"string.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {// change with parent
	int i = 0;
	LoanBookData* swap;
	swap = pN->getBookData(); // get data to change

	//  swap with parent node
	if (pN->getParent() != NULL) {	
		while ((pN->getParent()->getBookData()->getName()[i]) == (pN->getBookData()->getName()[i]))// compare left child
			i++;
		if ((pN->getParent()->getBookData()->getName()[i]) > (pN->getBookData()->getName()[i])) {//swap
			pN->setBookData(pN->getParent()->getBookData());// parent to child
			pN->getParent()->setBookData(swap);// child to parent
			pN = pN->getParent(); // go parent
			heapifyUp(pN); // recursive	
			return;//end
		}
	}
	else {
		return;/// end
	}

	}


void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
	int i = 0;
	LoanBookData* swap;
	swap = pN->getBookData();
	if (pN->getLeftChild() == NULL && pN->getRightChild() == NULL) { // has no child
		return;// end
	}
	else if (pN->getLeftChild() != NULL && pN->getRightChild() != NULL) { // when both child got vaule
		
		while ((pN->getLeftChild()->getBookData()->getName()[i]) == (pN->getRightChild()->getBookData()->getName()[i]))// compare right and left child
			i++;
		if ((pN->getLeftChild()->getBookData()->getName()[i]) <(pN->getRightChild()->getBookData()->getName()[i])) {//when left more small
			i = 0;
			while ((pN->getLeftChild()->getBookData()->getName()[i]) ==(pN->getBookData()->getName()[i]))// compare left child
				i++;
			if ((pN->getLeftChild()->getBookData()->getName()[i]) < (pN->getBookData()->getName()[i])) {//swap
				pN->setBookData(pN->getLeftChild()->getBookData()); // swap parent to child
				pN->getLeftChild()->setBookData(swap);
				pN = pN->getLeftChild();//go left
				heapifyDown(pN); // re
				return;
			}
			else {
				return; // end
			}
		}
		else {
			i = 0;
			while ((pN->getRightChild()->getBookData()->getName()[i]) == (pN->getBookData()->getName()[i]))//compare right child
				i++;
			if ((pN->getRightChild()->getBookData()->getName()[i]) < (pN->getBookData()->getName()[i])) {//swap
				pN->setBookData(pN->getRightChild()->getBookData());//swap parent to child
				pN->getRightChild()->setBookData(swap); // swap child to parent
				pN = pN->getRightChild();// move right child
				heapifyDown(pN); //re
				return;
			}
			else {
				return;//end
			}
		}
	}
	else { // has just one child->left
		i = 0;
		while ((pN->getLeftChild()->getBookData()->getName()[i]) == (pN->getBookData()->getName()[i]))// compare
			i++;
		if ((pN->getLeftChild()->getBookData()->getName()[i]) <(pN->getBookData()->getName()[i])) {
			pN->setBookData(pN->getLeftChild()->getBookData());
			pN->getLeftChild()->setBookData(swap); // last two child remain
			return;
		}
	}
}

bool LoanBookHeap::Insert(LoanBookData* data) {// inser heap
	LoanBookHeapNode* temp;
	if (root == NULL) { // has no data
		setRoot(new LoanBookHeapNode);
		root->setBookData(data); // insert data to root
		count++; // increase count

		return true;
	}
	else {
		count++; // count
	temp = div(count); // find where insert

		
		if (load[0] == 0) {// last is 0 = left
			temp->setLeftChild(new LoanBookHeapNode);
			temp->getLeftChild()->setParent(temp);
			temp = temp->getLeftChild();
		}
		else {// last is 0 = right
			temp->setRightChild(new LoanBookHeapNode);
			temp->getRightChild()->setParent(temp);
			temp = temp->getRightChild();

		}
		temp->setBookData(data); //set book data
		
	}
	heapifyUp(temp);  // sort heap	
	return 0;
}

LoanBookHeapNode* LoanBookHeap::div(int count) { //to find insert where
	// data count
	int i = count;
	int num =-1;
	LoanBookHeapNode* temp = root; // start at root

	memset(load, '\0', sizeof(load)); // reset load

	while (i!= 1) { // div is  end 
		num++;
		load[num] = i%2; // save remain if 1 ->right 0-> left
		i = i / 2;
		
	}

	while (num!= 0) { // search where to insert
		if (load[num] == 0) {
			temp = temp->getLeftChild();
		}
		else {
			temp = temp->getRightChild();
		}
		num-= 1;
	}
	return temp;
}