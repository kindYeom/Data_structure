#include "ListGraph.h"
#include <iostream>
#include <utility>
// Constructor for ListGraph
// Initializes the graph with a specified type (Directed or Undirected) and size

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	if (size < 1)
		m_List = NULL;// If size is less than 1, set m_List to NULL

	m_List = new map<int, int>[size+1]; // Create an array of maps to represent the graph
}
// Destructor for ListGraph
ListGraph::~ListGraph()	
{
	
}

// Method to get adjacent edges for a vertex (Undirected graph)
void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)	 //Definition of getAdjacentEdges(No Direction == Undirected)
{
	auto it = m_List[vertex].begin();
	// Iterate through the edges of the vertex
	while (it != m_List[vertex].end()) {
		m->insert({ it->first, it->second });// Insert the vertices pointing to the given vertex and their weights
		it++;
	}
	for (int i = 0; i < m_Size + 1;i++) {
		if (m_List[i].find(vertex) != m_List[i].end()) {
			it = m_List[i].find(vertex);
			m->insert({ i,it->second });
		}
	}

	return;
}
// Method to get adjacent edges for a vertex (Directed graph)
void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
	auto it = m_List[vertex].begin();
	// Iterate through the edges of the vertex
	while (it != m_List[vertex].end()) {
		m->insert({ it->first, it->second });// Insert adjacent vertices and their weights into the map
		it++;
	}

	return;
}
// Method to insert an edge between vertices with a specified weight
void ListGraph::insertEdge(int from, int to, int weight) //Definition of insertEdge
{
	m_List[from][to] = weight;// Insert an edge with a specified weight between 'from' and 'to' vertices

	return;
}

bool ListGraph::printGraph(ofstream *fout)	//Definition of print Graph
{
	if (m_List == NULL) // Output the vertex number
		return false;

	*fout << "=============print===============" << endl;
	for (int i = 1;i < m_Size + 1;i++) {
		*fout << '[' << i << ']';
		auto it = m_List[i].begin();
		// Iterate through the edges of each vertex and print them
		while (it != m_List[i].end()) {
			*fout <<" -> ";
			*fout << '(' << it->first << ","  << it->second << ')';// Output the adjacent vertices and their weights
			it++;
		}
		*fout << endl;

	}
	*fout << "================================" << endl;// End of graph printing

	return true;
}