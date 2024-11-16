#pragma once
#include <iostream>
#include "TermsBST.h"
#include "NameBST.h"
// ���⿡�� ���Ծ�� ������ ���� name bst�� �̸� ���� �̸���  ��ġ�� ������ ������ ����. �� ���� ��Ƽ���� ��� �w���ϰ� �ּ� �ؾ��Ѵ�.

class TermsListNode
{
private:

	TermsListNode* next;
	char type; // ���� ��� ����
	int member; // ���� ��� ȸ�� ��
	TermsBST *t_bst;

public:
	TermsListNode() {
		type = NULL;
		member = 0; // member s
		next = nullptr; // reset 
		t_bst = nullptr;

	}
	~TermsListNode() {}

	TermsListNode* getNext() { return next; } // call next node

	void setNext(TermsListNode* next) { this->next = next; } // link next node

	void settype(char X) { // input new type
		type = X; // input type
		increase_member(); // member +1
	};

	char gettype() { return type; } //type call
	int getmember() { return member; } //type member call
	void setmember(int cin) { member -= cin; }
	void increase_member() { member++; } // member increase
	 
	void setTermBST(TermsBST * node) {
		t_bst = node;
	}
	TermsBST* gettermbst() {
		return t_bst;
	}
};