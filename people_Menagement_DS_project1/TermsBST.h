#pragma once
#include "TermsBSTNode.h"
#include "MemberQueueNode.h"
#include <string>
#include <fstream>
#include "NameBST.h"

class TermsBST
{
private:
    TermsBSTNode* root; // Address of the starting node for each BST.

public:
    TermsBST();
    ~TermsBST();

    TermsBSTNode* getRoot(); // Get the root node of the BST.
    void setRoot(); // Set the root node of the BST.
    
    // Insert a new node into the BST based on the provided MemberQueueNode.
    void insert(MemberQueueNode* Q);

    // Print the BST and write the output to the specified file stream.
    void print(TermsBSTNode* branch, ofstream* output);

    // Delete nodes in the BST based on the provided date and the associated NameBST.
    int delete_Term(string date, NameBST* N_BST);

    // Traverse the BST in level order and delete nodes with the specified name and end date.
    void level_travel_distory(TermsBSTNode* node, int* count, NameBST* N_BST);

    // Delete nodes with the specified name and end date.
    void delete_term_name(string name, string enddate);
};
