#pragma once

#include "raylib.h"
#include "graphh.h"

typedef struct Header
{
	char header_name[5];
	int qtd_vertex;
	int qtd_edges;
} Header_t;

bool check_collision(Graph_t* pGraph, Vector2 mousePosition);
int get_vertex_by_position(Graph_t *pGraph, Vector2 mousePosition);
void DrawGridBackground(int screenWidth, int screenHeight, int spacing);
void clean_graph(Graph_t* pGraph);
void save_graph(Graph_t* pGraph, int edges);
void load_graph_debug(const char* filename, Graph_t** pGraph);
char* create_file_name(Graph_t* pGraph);