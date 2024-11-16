#include "Graph.h"

Graph::Graph(bool type, int size)
{
	m_Type = type; // type data
	m_Size = size; // size data
}

Graph::~Graph()	
{

}


bool Graph::getType(){return m_Type;}	
int Graph::getSize(){return m_Size;}
