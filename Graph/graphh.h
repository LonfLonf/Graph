#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "queue.h"
#include "stack.h"

#pragma once

typedef struct Edge {
	int index_dest;
	int weight;
	float thick;
	bool in_mst;
	struct Edge *next;
} Edge_t;

typedef struct Vertex {
	char label[50];
	float radius;
	Edge_t* head;
	Vector2 position;
	Color color;
} Vertex_t;

typedef struct Graph {
	int num_vertex;
	int capacity; 
	Vertex_t** array; 
} Graph_t;

/// <summary>
/// 
/// </summary>

typedef struct EdgeDisk {
	int vertex;
	int index_dest;
	int weight;
	float thick;
} EdgeDisk_t;

typedef struct VertexDisk {
	char label[50];
	unsigned int color;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	float radius;
	float x;
	float y;  
} VertexDisk_t;

typedef struct GraphDisk {
	int num_vertex;
	int capacity;
} GraphDisk_t;

typedef struct KruskalEdge {
	int src;
	int dest;
	int weight;
} KruskalEdge_t;

typedef struct KruskalState {
	KruskalEdge_t* edges;
	int* parent;
	int* rank;
	int edge_count;
	int current_edge;
	int mst_weight;
	bool finished;
} KruskalState_t;

typedef struct DijkstraState {
	int* distance;
	bool* visited;
	int* parent;
	int source;
	int destination;
	int current_vertex;
	int vertices_processed;
	int num_vertex;
	bool finished;
} DijkstraState_t;

typedef struct ChromaticState {
	int* color;
	int num_colors;
	int num_vertex;
	int current_vertex;
	bool finished;
} ChromaticState_t;

Graph_t* create_graph(int initial_capacity);

int add_vertex(Graph_t* pGraph, Vector2 position, Color color);

bool add_edge(Vertex_t* pArray, int dest, int weight);

void print_ordered_pairs(Graph_t* pGraph);

void dfs(Graph_t* pGraph, Stack_t* pStack, int* visited_dfs);

void bfs(Graph_t* pGraph, Queue_t* pQueueBfs, int* visited_bfs, int start);

void bfs_step(Graph_t* pGraph, Queue_t* pQueueBfs, int* visited_bfs);

void start_bfs(Graph_t* pGraph, int start);

int get_degree(Vertex_t* pVertex);

int count_odd_vertices(Graph_t* pGraph);

bool isEulerian(Graph_t* pGraph);

bool isUnicursal(Graph_t* pGraph);

bool isTree(Graph_t* pGraph);

int count_edges(Graph_t* pGraph);

void complete_graph(Graph_t *pGraph);

bool remove_edge(Vertex_t* pVertex, int dest);
void remove_vertex(Graph_t* pGraph, int index);

bool edge_exists(Vertex_t* pVertex, int j);

int create_random_weights();

KruskalState_t* Kruskal_init(Graph_t* pGraph);

void Kruskal_step(Graph_t* pGraph, KruskalState_t* pState);

void Kruskal_free(KruskalState_t* pState);

DijkstraState_t* Dijkstra_init(Graph_t* pGraph, int source);

void Dijkstra_step(Graph_t* pGraph, DijkstraState_t* pState);

void Dijkstra_free(DijkstraState_t* pState);

void Dijkstra(Graph_t* pGraph);

ChromaticState_t* Chromatic_init(Graph_t* pGraph);

void Chromatic_step(Graph_t* pGraph, ChromaticState_t* pState);

void Chromatic_free(ChromaticState_t* pState);

void CromaticNumber(Graph_t* pGraph);
