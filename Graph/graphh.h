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