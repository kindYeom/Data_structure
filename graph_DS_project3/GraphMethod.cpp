#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>

using namespace std;

bool BFS(Graph* graph, char option, int vertex, ofstream* fout)
{ 
	if (graph == nullptr || fout == nullptr) 
		return false; // Incorrect data input

	std::map<int, bool> visited; // Record visited vertices
	queue<int> q; // Queue for BFS traversal
	q.push(vertex); // Enqueue the starting vertex
	visited[vertex] = true;
	std::map<int, int> adjacentEdges;

	// Output based on graph type (Directed or Undirected)
	if (option == 'Y') {
		*fout << "Directed Graph BFS result" << endl;
	}
	else {
		*fout << "UnDirected Graph BFS result" << endl;
	}
	*fout << "start vertex : " << vertex<<endl;
	while (!q.empty()) {
		
			int currentVertex = q.front();
			*fout << currentVertex;
			q.pop();
			if (option == 'Y') 
				graph->getAdjacentEdgesDirect(currentVertex, &adjacentEdges);
			else
				graph->getAdjacentEdges(currentVertex, &adjacentEdges);
			auto it = adjacentEdges.begin();
			while (it != adjacentEdges.end()) {
				if (!visited[it->first]) {
					q.push(it->first);// Enqueue unvisited adjacent vertices
					visited[it->first] = true;
				}
				it++;
			}
			*fout << "->"; // Separate vertices in the output
		}
	

	return true;
}

bool DFS(Graph* graph, char option, int vertex, ofstream* fout)
{
	if (graph == nullptr || fout == nullptr) 
		return false; // Incorrect command
	int currentVertex;
	int V;

	stack<int> s;
	std::map<int, int> adjacentEdges;
	map<int, bool> visited;

	// Output based on graph type (Directed or Undirected)
	if (option == 'Y') {
		*fout << "Directed Graph BFS result" << endl;
	}
	else {
		*fout << "UnDirected Graph BFS result" << endl;
	}
	*fout << "start vertex : " << vertex << endl;
	visited[vertex] = true;
	s.push(vertex);
	*fout << vertex << "->";
	currentVertex = vertex;


	while (!s.empty()) {
		if(option == 'Y')
			graph->getAdjacentEdgesDirect(currentVertex, &adjacentEdges);
		else
			graph->getAdjacentEdges(currentVertex, &adjacentEdges);

		auto it = adjacentEdges.begin();

		while (it != adjacentEdges.end()) {
			if (!visited[it->first]) {
				s.push(it->first);
				visited[it->first] = true;
				currentVertex = s.top();
				*fout << currentVertex << "->";
				break;
			}
			it++;
		}
		if (it == adjacentEdges.end()) {
			if (s.size() == 1) {
				return true;
			}
			s.pop();
			currentVertex = s.top();
		}
		adjacentEdges.clear();
	}
	return true;
 }

bool Kruskal(Graph* graph, ofstream *fout)
{
	vector<tuple<int, int, int>> result;
	vector<tuple<int, int,int>> adjacentEdges2;
	std::map<int, int> adjacentEdges;
	vector<tuple<int,int,int>> MST;

	
	if (graph == nullptr || fout == nullptr)
		return false; // woreg command
	int i;
	for (i = 1;i <= graph->getSize();i++) {
		graph->getAdjacentEdges(i, &adjacentEdges);

		auto it = adjacentEdges.begin();

		while (it != adjacentEdges.end()) {
			adjacentEdges2.push_back(make_tuple(it->second, i, it->first));
			it++;
		}
		adjacentEdges.clear();
	}
	
	sort(adjacentEdges2.begin(), adjacentEdges2.end());

	int *parent = new int[graph->getSize()+1];
	memset(parent, -1, sizeof(int) * (graph->getSize()+1));


	while (!adjacentEdges2.empty()) {
		int start = get<1>(adjacentEdges2.front());
		int dist = get<2>(adjacentEdges2.front());
		int weight = get<0>(adjacentEdges2.front());
		i = start;
		int j = dist;
		while (1) {
			if (parent[i] == -1)
				break;
			i = parent[i];
		}
		while (1) {
			if (parent[j] == -1)
				break;
			j = parent[j];
		}
		if (j != i) {
			result.push_back(make_tuple(start, dist, weight));
			result.push_back(make_tuple(dist, start, weight));
			parent[j] =i;
		}
		adjacentEdges2.erase(adjacentEdges2.begin());
	}
	if (result.size() != (graph->getSize() - 1) * 2)
		return false;
	sort(result.begin(), result.end());
	*fout << "====== Kruskal =======" << endl;
	 i = 1;
	while (!result.empty()) {
		*fout << '[' << i << ']' << "     ";
		while (i == get<0>(result.front())) {
			*fout << get<1>(result.front()) << '(' << get<2>(result.front()) << ')' << ' ';
			result.erase(result.begin());
			if (result.empty()) {
				*fout <<endl <<"====================" << endl;
				return true;
			}
		}
		*fout << endl;
		i++;

	}

	return true;
}

bool Dijkstra(Graph* graph, char option, int vertex)
{
	return true;
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex) 
{
	return true;
}

bool FLOYD(Graph* graph, char option)
{
	return true;
}

bool KWANGWOON(Graph* graph, int vertex) {
	return true;
}




