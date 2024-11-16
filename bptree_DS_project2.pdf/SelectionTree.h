
#pragma once
#include "SelectionTreeNode.h"
#include <map>
#include <fstream>
#include <iostream>

class SelectionTree
{
private:
    SelectionTreeNode* root;
    ofstream* fout;
    std::map<int, SelectionTreeNode*>Selectionmap;

public:
    SelectionTree(ofstream* fout) {
        this->root = new SelectionTreeNode;
        this->fout = fout;
     
        Selectionmap[0] = new SelectionTreeNode;
        Selectionmap[100] = new SelectionTreeNode;
        Selectionmap[200] = new SelectionTreeNode;
        Selectionmap[300] = new SelectionTreeNode;
        Selectionmap[400] = new SelectionTreeNode;
        Selectionmap[500] = new SelectionTreeNode;
        Selectionmap[600] = new SelectionTreeNode;
        Selectionmap[700] = new SelectionTreeNode;
        //root  - leftchild
        root->setLeftChild(new SelectionTreeNode);
        root->getLeftChild()->setParent(root);
        //root rightchild
        root->setRightChild(new SelectionTreeNode);
        root->getRightChild()->setParent(root);
        // root-left-left
        root->getLeftChild()->setLeftChild(new SelectionTreeNode);
        root->getLeftChild()->getLeftChild()->setParent(root->getLeftChild());
        // root-left-right
        root->getLeftChild()->setRightChild(new SelectionTreeNode);
        root->getLeftChild()->getRightChild()->setParent(root->getLeftChild());
        // root-right-left
        root->getRightChild()->setLeftChild(new SelectionTreeNode);
        root->getRightChild()->getLeftChild()->setParent(root->getRightChild());
        //root-right-left
        root->getRightChild()->setRightChild(new SelectionTreeNode);
        root->getRightChild()->getRightChild()->setParent(root->getRightChild());
        //set root data
        auto it = Selectionmap.begin();
        root->getLeftChild()->getLeftChild()->setLeftChild(it->second);//000
        it->second->setParent(root->getLeftChild()->getLeftChild());
        advance(it, 1);
        root->getLeftChild()->getLeftChild()->setRightChild(it->second);//100
        it->second->setParent(root->getLeftChild()->getLeftChild());
        advance(it, 1);
        root->getLeftChild()->getRightChild()->setLeftChild(it->second);//200
        it->second->setParent(root->getLeftChild()->getRightChild());
        advance(it, 1);
        root->getLeftChild()->getRightChild()->setRightChild(it->second);//300
        it->second->setParent(root->getLeftChild()->getRightChild());
        advance(it, 1);
        root->getRightChild()->getLeftChild()->setLeftChild(it->second);//400
        it->second->setParent(root->getRightChild()->getLeftChild());
        advance(it, 1);
        root->getRightChild()->getLeftChild()->setRightChild(it->second);//500
        it->second->setParent(root->getRightChild()->getLeftChild());
        advance(it, 1);
        root->getRightChild()->getRightChild()->setLeftChild(it->second);//600
        it->second->setParent(root->getRightChild()->getRightChild());
        advance(it, 1);
        root->getRightChild()->getRightChild()->setRightChild(it->second);//700
        it->second->setParent(root->getRightChild()->getRightChild());
       // root-2-4
        // make selection tree; 
    }
    ~SelectionTree() {
        deletetree(root);
 
    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    bool Insert(LoanBookData* newData);
    bool Delete();
    bool printBookData(int bookCode);
    void deletetree(SelectionTreeNode * root) { // free all memory
        if (root != NULL) {
            return;
        }
        deletetree(root->getLeftChild());
        deletetree(root->getRightChild());
        free(root); 
    };
};