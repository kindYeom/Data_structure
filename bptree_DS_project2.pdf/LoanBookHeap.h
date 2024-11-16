
#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"

class LoanBookHeap
{
private:
    LoanBookHeapNode* root;
    int count;
    int load[100];
public:
    LoanBookHeap() {
        this->root = NULL;
        this->count = 0;
        load[100] = NULL; // to insert log of heap  
    };
    ~LoanBookHeap() {
        deletetree(root);
    };


    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    LoanBookHeapNode* getRoot() { return root; }

    void heapifyUp(LoanBookHeapNode* pN);
    void heapifyDown(LoanBookHeapNode* pN);

    bool Insert(LoanBookData* data);
    LoanBookHeapNode* div(int count);
    void setCount(int x) { count = x; };
    void countdown() { count--; };
    int getCount() { return count; };
    int getLast() { return load[0]; };

    void deletetree(LoanBookHeapNode* root) { // free all memory
        if (root != NULL) {
            return;
        }
        deletetree(root->getLeftChild());
        deletetree(root->getRightChild());
        free(root);
    };
};
