#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "queue.h"

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
	int num_vertex; // Quantos vertices tem
	int capacity; // Espaços alocados
	Vertex_t** array; 
} Graph_t;

Graph_t* create_graph(int initial_capacity);

int add_vertex(Graph_t* pGraph, Vector2 position, Color color);

bool add_edge(Vertex_t* pArray, int dest, int weight);

void print_ordered_pairs(Graph_t* pGraph);

void start_dfs(Graph_t* pGraph, int vertex);

void dfs(Graph_t* pGraph, int vertex, int* visited);

void start_bfs(Graph_t* pGraph, int start);

void bfs(Graph_t* pGraph, Queue_t* pQueue, int* visited, int start);

int get_degree(Vertex_t* pVertex);

int count_odd_vertices(Graph_t* pGraph);

bool isEulerian(Graph_t* pGraph);

bool isUnicursal(Graph_t* pGraph);

bool isTree(Graph_t* pGraph);

int count_edges(Graph_t* pGraph);

void complete_graph(Graph_t *pGraph);

bool edge_exists(Vertex_t* pVertex, int j);