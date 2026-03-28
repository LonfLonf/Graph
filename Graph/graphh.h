#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge {
	int index_dest;
	int weight;
	struct Edge *next;
} Edge_t;

typedef struct Vertex {
	char label[50];
	Edge_t* head;
} Vertex_t;

typedef struct Graph {
	int num_vertex;
	Vertex_t** array;
} Graph_t;

Graph_t* create_graph(int num_vertex);

bool add_edge(Vertex_t* pArray, int dest, int weight);

void print_ordered_pairs(Graph_t* pGraph);