#pragma once
#include <iostream>
#include "TermsBST.h"
#include "NameBST.h"
// ¿©±â¿¡´Â °¡ÀÔ¾à°ü Á¾·ù¸¸ µé¾î°¡°Å name bst¿¡ ÀÌ¸§ µé¾î°¡¼­ ÀÌ¸§À»  À§Ä¡¸¦ Æ÷ÀÎÅÍ º¯¼ö·Î ÀúÀå. Áï ³×ÀÓ ºñÆ¼¿¡¼ö Çì´õ ­w°¡ÇÏ°í ÁÖ¼Ò ÇØ¾ßÇÑ´Ù.

class TermsListNode
{
private:

	TermsListNode* next;
	char type; // °¡ÀÔ ¾à°ü Á¾·ù
	int member; // °¡ÀÔ ¾à°ü È¸¿ø ¼ö
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