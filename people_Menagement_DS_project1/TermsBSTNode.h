#pragma once
#include <string>
using namespace std;

// Declaration of the class TermsBSTNode
class TermsBSTNode
{
private:
	TermsBSTNode* left;      // Pointer to the left child node
	TermsBSTNode* right;     // Pointer to the right child node
	string name;            // Variable to store the name
	int age;                // Variable to store the age
	string start_date;      // Variable to store the start date
	string end_date;        // Variable to store the end date  

public:
	// Constructor: Initializes left and right pointers to nullptr
	TermsBSTNode() {
		left = nullptr;
		right = nullptr;
	}

	// Destructor: No explicit cleanup is performed in the destructor

	// Getter methods for left and right child nodes
	TermsBSTNode* getLeft() { return left; }
	TermsBSTNode* getRight() { return right; }

	// Setter methods for left and right child nodes
	void setLeft(TermsBSTNode* left) { this->left = left; }
	void setRight(TermsBSTNode* right) { this->right = right; }

	/////////////////////////////////////

	// Method to set data for the node based on input values and type
	void setdata(string name, int age, string start_date, char type) {
		this->name = name;
		this->age = age;
		this->start_date = start_date;
		this->end_date = start_date;

		// Logic to update the end date based on the given type
		switch (type) {
		case 'A':

			end_date[6] = end_date[6] + 6;
			if (end_date[6] >= 58) {
				end_date[6] -= 10;
				end_date[5]++;
				if (end_date[5] > 49) {
					end_date[5] -= 2;
					end_date[3]++;
					if (end_date[3] >= 58) {
						end_date[3] -= 10;
						end_date[2]++;
						if (end_date[2] >= 58) {
							end_date[2] -= 10;
							end_date[1]++;
							if (end_date[2] >= 58) {
								end_date[2] -= 10;
								end_date[1]++;
							}
						}
					}
				}
			}
			break;
		case 'B':
			end_date[3] += 1;
			if (end_date[3] >= 58) {
				end_date[3] -= 10;
				end_date[2]++;
				if (end_date[2] >= 58) {
					end_date[2] -= 10;
					end_date[1]++;
					if (end_date[2] >= 58) {
						end_date[2] -= 10;
						end_date[1]++;
					}
				}
			}
			break;
		case 'C':
			end_date[3] += 2;
			if (end_date[3] >= 58) {
				end_date[3] -= 10;
				end_date[2]++;
				if (end_date[2] >= 58) {
					end_date[2] -= 10;
					end_date[1]++;
					if (end_date[2] >= 58) {
						end_date[2] -= 10;
						end_date[1]++;
					}
				}
			}
			break;
		case 'D':
			end_date[3] += 3;
			if (end_date[3] >= 58) {
				end_date[3] -= 10;
				end_date[2]++;
				if (end_date[2] >= 58) {
					end_date[2] -= 10;
					end_date[1]++;
					if (end_date[2] >= 58) {
						end_date[2] -= 10;
						end_date[1]++;
					}
				}
			}
			break;
		}

	}

	string getname() { return name; }
	int getage() { return age; }
	string getstartdate() { return start_date; }
	string getenddate() { return end_date; }

	void dataCopy(string name, int age, string start_date, string end_date) {
		this->name = name;
		this->age = age;
		this->start_date = start_date;
		this->end_date = end_date;

	}

};

