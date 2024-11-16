#pragma once
#include <string>
class NameBSTNode
{
private:

    NameBSTNode* left; // Pointer to the left child node.
    NameBSTNode* right; // Pointer to the right child node.
    string name; // Member's name.
    int age; // Member's age.
    string start_date; // Start date of membership.
    string end_date; // End date of membership.
    char type; // Type of membership agreement.

public:
    NameBSTNode() {
        left = nullptr;
        right = nullptr;
        age = NULL;
        type = NULL;
    }
    ~NameBSTNode() {}

    // Getters and setters for left and right child nodes.
    NameBSTNode* getLeft() { return left; }
    NameBSTNode* getRight() { return right; }
    void setLeft(NameBSTNode* left) { this->left = left; }
    void setRight(NameBSTNode* right) { this->right = right; }

    // Set data for the node.
    void setdata(string name, int age, string start_date, char type) {
        this->name = name;
        this->age = age;
        this->start_date = start_date;
        this->end_date = start_date;
        this->type = type;
		switch (type) {
		case 'A':

			end_date[6] = end_date[6] + 6;
			if (end_date[5] == '1' && end_date[6] > 50) {
				end_date[6] = end_date[6] - 2;
				end_date[5]++;
			}
			if (end_date[6] >= 58) {
				end_date[6] -= 10;
				end_date[5]++;
			}
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
        // ... (logic for updating end_date based on type)
    }

    // Getters for member data.
    string getname() { return name; }
    int getage() { return age; }
    string getstartdate() { return start_date; }
    string getenddate() { return end_date; }
    char gettype() { return type; }

    // Copy data from another node.
    void dataCopy(string name, int age, string start_date, string end_date) {
        this->name = name;
        this->age = age;
        this->start_date = start_date;
        this->end_date = end_date;
    }
};
