#pragma once

#include "raylib.h"
#include "graphh.h"

bool check_collision(Graph_t* pGraph, Vector2 mousePosition);
int get_vertex_by_position(Graph_t *pGraph, Vector2 mousePosition);
void DrawGridBackground(int screenWidth, int screenHeight, int spacing);
void clean_graph(Graph_t* pGraph);