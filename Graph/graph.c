#include "graphh.h"

Graph_t* create_graph(int num_vertex)
{
	// Creating the Dynamic Array for the Graph Struct
	Graph_t* pGraph = (Graph_t*)malloc(sizeof(Graph_t));
	Vertex_t** pArray = (Vertex_t**)malloc(num_vertex * sizeof(Vertex_t*));

	if (pArray == NULL || pGraph == NULL)
	{
		perror("Memory Allocation for Dynamic Array for the Graph Struct FAILED!!!");
		return NULL;
	}

	pGraph->num_vertex = num_vertex;
	pGraph->array = pArray;

	// Starting the Array of Vertices
	for (int i = 0; i < num_vertex; i++)
	{
		pArray[i] = (Vertex_t*)malloc(sizeof(Vertex_t));

		if (pArray[i] == NULL)
		{
			perror("Memory Allocation for Vertex FAILED!!!");
			return NULL;
		}

		char str[80];
		snprintf(pArray[i]->label, sizeof(pArray[i]->label), "Vertice %d", i);
		pArray[i]->head = NULL;
	}

	return pGraph;
}

bool add_edge(Vertex_t* pArray, int dest, int weight)
{
	Edge_t* pEdge = (Edge_t*)malloc(sizeof(Edge_t));

	if (pEdge == NULL)
	{
		perror("Allocating Memory for the Vertex FAILED!!!");
		return false;
	}

	pEdge->index_dest = dest;
	pEdge->weight = weight;
	pEdge->next = pArray->head;

	pArray->head = pEdge;

	return true;
}

void print_ordered_pairs(Graph_t* pGraph)
{
	int i = 0;
	for (i; i < pGraph->num_vertex; i++)
	{
		printf("Edges Vertex %d\n", i);

		Vertex_t* pVertex = (Vertex_t *)pGraph->array[i];
		Edge_t* pEdge_head = pVertex->head;

		while (pEdge_head != NULL)
		{
			printf("Origem: %d - Destino: %d\n", i, pEdge_head->index_dest);
			pEdge_head = pEdge_head->next;
		}  

		printf("\n");
	}
}

void dfs(Graph_t* pGraph, int vertex, int* visited)
{
	visited[vertex] = 1;

	Vertex_t* pVertex = (Vertex_t*)pGraph->array[vertex];
	Edge_t* neighbor = pVertex->head;

	printf("Visitado: %s\n", pVertex->label);

	while (neighbor != NULL)
	{
		if (visited[neighbor->index_dest] == 0)
		{
			dfs(pGraph, neighbor->index_dest, visited);
		}

		neighbor = neighbor->next;
	}
}

void start_dfs(Graph_t* pGraph, int vertex)
{
	int* pArr = (int*)calloc(pGraph->num_vertex, sizeof(int));

	dfs(pGraph, vertex, pArr);

	free(pArr);
}