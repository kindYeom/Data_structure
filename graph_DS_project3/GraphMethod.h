#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph* graph, char option, int vertex, ofstream* fout);
bool DFS(Graph* graph, char option,  int vertex, ofstream* fout);
bool KWANGWOON(Graph* graph, int vertex);  
bool Kruskal(Graph* graph, ofstream* fout);
bool Dijkstra(Graph* graph, char option, int vertex);    //Dijkstra
bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex); //Bellman - Ford
bool FLOYD(Graph* graph, char option);   //FLoyd

#endif
