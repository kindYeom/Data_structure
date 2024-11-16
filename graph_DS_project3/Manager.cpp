
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Manager.h"
Manager::Manager()	
{
	graph = nullptr;	
	fout.open("log.txt", ios::app);
	load = 0;	//Anything is not loaded

}

Manager::~Manager()
{
	if(load)	//if graph is loaded, delete graph
		delete graph;	
	if(fout.is_open())	//if fout is opened, close file
		fout.close();	//close log.txt File
}

void Manager::run(const char* command_txt){
	ifstream fin;	//Command File Input File Stream
	int i = 0;
	string cmd;
	fin.open(command_txt, ios_base::in);//File open with read mode
	
	if(!fin) { //If command File cannot be read, Print error
		fout<<"command file open error"<<endl;
		return;	//Return
	}

	while (getline(fin, data1)) { // read command 
		i = 0;


		while (data1[i]!=' '&& data1[i] != '\0')// read command 
			i++;
			cmd = data1.substr(0, i);

		if (cmd == "LOAD") {
			data1 = data1.substr(i + 1); // remove sord load
			const char* charPtr = data1.c_str();

			if (LOAD(charPtr) == false) 
				printErrorCode(100); // print errorcode
			else {
				fout << "=========LOAD========="<<endl;
				fout << "Success"<<endl;
				fout << "======================="<<endl;
			}

		}
		else if (cmd == "PRINT") { //print data
			if (PRINT() == false)
				printErrorCode(200); // print errorcode
		}
		else if (cmd == "BFS") {
			if (data1.length() < 7) {
				printErrorCode(300); // get strange data
				continue;
			}
			data1 = data1.substr(i + 1);
			char directed = data1[0]; // directed or not
			data1 = data1.substr(2); // get where to start
			if (mBFS(directed,stoi(data1)) == false) // mBFS
				printErrorCode(300);
			fout << endl;
		}
		else if (cmd == "DFS") {
			if (data1.length() < 7) {
				printErrorCode(400); // get strange data
				continue;
			}
			data1 = data1.substr(i + 1); // cut 
			char directed = data1[0];
			data1 = data1.substr(2);
				if (mDFS(directed,stoi(data1)) == false)
				printErrorCode(400);
				fout << endl;
		}
		else if (cmd == "KWANGWOON") {
			//	if (mKWANGWOON() == false)
				printErrorCode(500);


		}
		else if(cmd == "KRUSKAL"){
			if (mKRUSKAL() == false)
				printErrorCode(600);

		}
		else if (cmd == "DIJKSTRA") {
			//	if (mDIJKSTRA() == false)
				printErrorCode(700);

		}
		else if (cmd=="BELLMANFORD") {
		//	if (mBELLMANFORD() == false)
				printErrorCode(800);

		}
		else if (cmd=="FLOYD") {
			//if (mFLOYD() == false)
				printErrorCode(900);

		}
		else if (cmd=="EXIT") {
			exit(-1);
		}
		else {
			printErrorCode(1000);

		}


	}
	fin.close();
	return;
}

bool Manager::LOAD(const char* filename)
{
	//delete graph;
	ifstream fin2;
	int i = 0;
	fin2.open(filename); // open file
	if (!fin2.is_open()) { // no file or already exist data
		return false; // if file doesn't exist print error 
	}
	if (!getline(fin2, data2)) // file has no data
		return false;

	if (data2[0] != 'L' && data2[0] != 'M') // get differernt tpye
		return false;


	type = data2[0]; // get type

	getline(fin2, data2); 

	load = stoi(data2); // get size data

	if (type == 'L') {
		graph = new ListGraph(1,load); //make new listgraph
	}
	else{
		graph = new MatrixGraph(0, load); // load
	}

	if (type == 'L') {
		while (getline(fin2, data2)) {
			
			if (count(data2.begin(), data2.end(), ' ') == 0) { // check empty
				G_data[0] = stoi(data2); // from data
			}
			else {
				i = 0;
				while (data2[i] != ' ')
					i++;
				G_data[1] = stoi(data2.substr(0, i)); // get data
				G_data[2] = stoi(data2.substr(i + 1)); // get data
				graph->insertEdge(G_data[0], G_data[1], G_data[2]);
			}
		}
	}
	else { // when tyep  = m
		i = 0;
		int row = 1, col;
		while (getline(fin2, data2)) {
			col = 1;
			i = 0;
			while (1) {
				while (data2[i] != ' ' && data2[i] != '\0')
					i++;

				G_data[0] = stoi(data2.substr(0, i)); // get data
		
				graph->insertEdge(row, col, G_data[0]);

				if (col == graph->getSize())
					break;
				else
					data2 =data2.substr(i+1);
					i = 0;
					col++; // next col
			}
			row++;
		}
	}

	return true;
}

bool Manager::PRINT()	
{
	if (graph == nullptr)
		return false;
	graph->printGraph(&fout); // print data

	return true;
}

bool Manager::mBFS(char option, int vertex)	
{
	if ( vertex > graph->getSize()) // worng vertex
		return false;
	fout << "======== BFS ========"<<endl;
	BFS(graph, option, vertex,&fout); // serach by BFS
	fout <<endl <<"=====================" << endl;
	return true;
}

bool Manager::mDFS(char option, int vertex)	
{
	if (vertex > graph->getSize())
		return false;
	fout << "======== DFS ========" << endl;
	DFS(graph, option, vertex,&fout);// serach by DFS
	fout << endl << "=====================" << endl;
	return true;
}

bool Manager::mDIJKSTRA(char option, int vertex)	
{
	return true;
}

bool Manager::mKRUSKAL()
{
	Kruskal(graph,&fout);
	return true;
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex) 
{
	return true;
}

bool Manager::mFLOYD(char option)
{
	return true;
}

bool Manager::mKwoonWoon(int vertex) {
	return true;
}

void Manager::printErrorCode(int n) // print error code
{
	fout<<"========ERROR======="<<endl;
	fout<<n<<endl;
	fout<<"===================="<<endl << endl;
	return;
}


