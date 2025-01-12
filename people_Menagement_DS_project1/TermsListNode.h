#pragma once
#include <iostream>
#include "TermsBST.h"
#include "NameBST.h"
// 여기에는 가입약관 종류만 들어가거 name bst에 이름 들어가서 이름을  위치를 포인터 변수로 저장. 즉 네임 비티에수 헤더 춛가하고 주소 해야한다.

class TermsListNode
{
private:

	TermsListNode* next;
	char type; // 가입 약관 종류
	int member; // 가입 약관 회원 수
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