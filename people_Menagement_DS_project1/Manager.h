#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
#include<iostream>
#include "string"
using namespace std;

class Manager
{
private:

	ifstream fcmd; // Input file stream for command file reading.
	ifstream fdata; // Input file stream for reading the data file.
	ofstream flog; // Output file stream to be used when creating log.
	string line; // Variable used for reading one line of commands.
	string line_data; // Variable used for reading one line of data.
	MemberQueue m_Queue; // Variable used for the queue data structure.
	TermsLIST t_list; // Variable used for the TermsLIST data structure.
	NameBST N_bst; // Variable used for the NameBST data structure.
public:
	Manager();
	
	
	~Manager();

	void run(const char* command); // Reads the commands.

	void PrintSuccess(const char* cmd); // Displays success messages on the screen.
	void PrintErrorCode(int num); // Displays error messages on the screen.

	void LOAD(const char* data_files); // Function to read files.
	void ADD(string line); // Function used to add data to the queue.
	bool QPOP(); // Function for Qpop.
	void SEARCH(string name); // Search function.
	void PRINT(string input); // Function to print all.
	void DELETE(string name); // Delete data function.
	void EXIT(); // Exit the program.
};
