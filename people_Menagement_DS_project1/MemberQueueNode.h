#pragma once
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

class MemberQueueNode // Node used for implementing the queue
{
private:
    MemberQueueNode* m_pNext; // Variable pointing to the next node
    string name; // Member's name
    int age; // Member's age
    string date; // Date of collecting personal information
    char type; // Type of agreement for membership

public:
    MemberQueueNode() {// Constructor, initializes values.
        m_pNext = nullptr;
        // Automatically initialize name
        age = NULL;
        // Automatically initialize data.
        type = NULL;
    }
    ~MemberQueueNode() {}

    //*************************************************
    //************************************************

    bool SetData(string a) {

        int s = 0;
        while (a[s] != ' ') {
            s++;
        }
        name = a.substr(0, s);    // Get the name.
        s++; // Move the address to the current space position +1
        age = stoi(a.substr(s, 2)); // Get the age; it handles single-digit ages as well.
        while (a[s] != ' ') {// Move to the next space position.
            s++;
        }
        s++;// Move to the next space position +1
        date = a.substr(s, 10);
        while (a[s] != ' ') {// Move to the next space position.
            s++;
        }
        s++;
        type = a[s];
        return 1;
    };

    void SetNext(MemberQueueNode* Node) {
        m_pNext = Node;
    };

    MemberQueueNode* GetNext() {
        return m_pNext;
    }

    char gettype() { return type; }
    string getname() { return name; }
    string getdate() { return date; }
    int getage() { return age; }
};
