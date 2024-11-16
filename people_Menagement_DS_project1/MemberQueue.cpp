
#include "MemberQueue.h"

MemberQueue::MemberQueue() // constructor data set
{
	MemberQueueNode* m_rear = nullptr; // rear
	MemberQueueNode* m_front = nullptr;//  head
	count = 0; // member
}
MemberQueue::~MemberQueue()// 
{
	
}	

bool MemberQueue::empty()
{
	if (m_rear == nullptr && m_front == nullptr) // Q is empty
		return 1; // empty
	else
		return 0; // no

} 
bool MemberQueue::full() // Q is full
{
	if (count = 100)
		return 1; // full
	else
		return 0; // no
}
bool MemberQueue::push(string line) { // input Q

	if (count >= 100) 
		exit(-1); // date is full
	if (count == 0) { // first data
		m_front = new MemberQueueNode; //  front 
		m_rear = m_front; // rear = front
		m_front->SetData(line);// set data

		count++; // data plus
	}
	else {// more than one data
		MemberQueueNode* temp = new MemberQueueNode;//Address value temporary storage variable.
		m_rear->SetNext(temp);// Connecting nodes
		m_rear = temp; // change the rear position
		m_rear->SetData(line); //Data entry
	}

	return 1;
}
 bool MemberQueue::pop(TermsLIST *t_Head, NameBST *n_Head )// Data output
{
	 if (empty()) // End of pop that will be empty
		 return 0;

	 MemberQueueNode* temp;
	 while (m_front != nullptr) { // Until the next address is not available

		 t_Head->insert(m_front->gettype(),m_front); // Export values sequentially from m_front
		 // term list
		 n_Head->insert(m_front); // Send name to BST TREE
		 //name bst
		 temp = m_front;
		m_front = temp->GetNext();// Turn the memory you were pointing to into front
		
		free(temp); //Release Memory
		temp = nullptr;
	 }

	 return 1;
	 
};
MemberQueueNode MemberQueue::rear()
{
	return *m_rear;
};