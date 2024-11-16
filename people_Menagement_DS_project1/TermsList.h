#pragma once
#include "TermsListNode.h"
#include "MemberQueueNode.h"
#include "NameBST.h"

class TermsLIST
{
private:
    TermsListNode* head; // Address of the starting node.

public:
    TermsLIST();
    ~TermsLIST();

    TermsListNode* getHead(); // Get the starting address.

    // Insert a new node into the list based on the provided type and MemberQueueNode.
    void insert(char type, MemberQueueNode* Q);

    // Search for a node with the given type in the list.
    TermsListNode* search(string type);

    // Delete nodes in the list based on the provided date and the associated NameBST.
    void delete_list(string date, NameBST* N_BST);

    // Delete nodes in the list based on the provided data, type, and end date.
    void delete_list_name(string data, char type, string enddate);
};
