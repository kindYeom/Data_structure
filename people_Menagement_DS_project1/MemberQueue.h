#pragma once
#include "MemberQueueNode.h"
#include "iostream"
#include"TermsList.h"
#include"NameBST.h"


class MemberQueue
{
private:
	MemberQueueNode* m_rear; // last node
	MemberQueueNode* m_front;// frirst dnode
	int count; // number of node


public:
	MemberQueue();
	~MemberQueue();

	bool empty(); // is empty?
		

	bool full(); //is full?


	bool push(string line);
	bool pop(TermsLIST *t_Head,NameBST *n_Head);
	MemberQueueNode rear();

};

