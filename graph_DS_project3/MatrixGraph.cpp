#include "MatrixGraph.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

// Constructor for MatrixGraph
MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
	// Allocate memory for the adjacency matrix and initialize elements to 0
	m_Mat = new int* [size + 1];
	m_Mat = new int* [size + 1]; 
	for (int i = 0; i <= size; ++i) {
		m_Mat[i] = new int[size + 1];

		for (int j = 0; j <= size; ++j) {
			m_Mat[i][j] = 0;
		}
	}
}
// Destructor for MatrixGraph
MatrixGraph::~MatrixGraph()
{
	delete m_Mat;// Deallocate memory for the adjacency matrix
}
// Method to get adjacent edges for a vertex (Undirected graph)
void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{	
	for (int i = 1;i < m_Size + 1;i++) {
		if (m_Mat[vertex][i] != 0) {
			m->insert({ i,m_Mat[vertex][i] }); // Insert adjacent vertices and their weights into the map
			continue;
		}
		if (m_Mat[i][vertex] != 0 )
			m->insert({ i,m_Mat[i][vertex] }); // Insert vertices pointing to the given vertex and their weights
	}
	return;
}

// Method to get adjacent edges for a vertex (Directed graph)
void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)
{
	for (int i = 1;i < m_Size + 1;i++) {
		if (m_Mat[vertex][i] != 0) {
			m->insert({ i,m_Mat[vertex][i] });// Insert adjacent vertices and their weights into the map
		}
	}
	return;
}
// Method to insert an edge between vertices with a specified weight
void MatrixGraph::insertEdge(int from, int to, int weight)	
{
	m_Mat[from][to] = weight;// Insert an edge with a specified weight between 'from' and 'to' vertices

	return ;
}
// Method to print the graph as an adjacency matrix to an output file
bool MatrixGraph::printGraph(ofstream *fout)	
{
	if (m_Mat == NULL) // Return false if no data
		return false;

	int row = 1,col = 1;
	*fout << "=============print===============" << endl;
	*fout << "       ";
	for (col = 1; col < m_Size + 1;col++) {
		*fout <<"[ "<< col <<" ]" << ' '; // print matrix
	}
	*fout << endl;
	 
	for (row = 1;row < m_Size + 1;row++) {
		*fout << "[ " << row << " ]" << ' ';// Print column indices
		for (col = 1; col < m_Size + 1;col++) {
			*fout << setw(3) << m_Mat[row][col]<<"    ";// Print adjacency matrix
		}
		*fout << endl;
	}

	*fout << "================================" << endl;

	return true;
}
