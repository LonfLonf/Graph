#include "graphh.h"
#include "queue.h"

Graph_t* create_graph(int initial_capacity)
{
	if (initial_capacity <= 0) initial_capacity = 10;

	Graph_t* pGraph = (Graph_t*)malloc(sizeof(Graph_t));
	Vertex_t** pArray = (Vertex_t**)malloc(initial_capacity * sizeof(Vertex_t*));

	if (pArray == NULL || pGraph == NULL)
	{
		perror("Memory Allocation for Dynamic Array for the Graph Struct FAILED!!!");
		return NULL;
	}

	pGraph->num_vertex = 0;
	pGraph->capacity = initial_capacity;
	pGraph->array = pArray;

	return pGraph;
}

int add_vertex(Graph_t* pGraph, Vector2 pos, Color col)
{
	
	if (pGraph->num_vertex == pGraph->capacity)
	{
		pGraph->capacity *= 2; 

		Vertex_t** temp = (Vertex_t**)realloc(pGraph->array, pGraph->capacity * sizeof(Vertex_t*));

		if (temp == NULL) {
			perror("Realloc FAILED!!!");
			return -1;
		}
		pGraph->array = temp;
	}

	int index = pGraph->num_vertex;
	Vertex_t* new_vertex = (Vertex_t*)malloc(sizeof(Vertex_t));

	if (new_vertex == NULL) {
		perror("Memory Allocation for Vertex FAILED!!!");
		return -1;
	}

	snprintf(new_vertex->label, sizeof(new_vertex->label), "Vertice %d", index);
	new_vertex->head = NULL;
	new_vertex->position = pos;
	new_vertex->color = col;
	new_vertex->radius = 20.0f;

	
	pGraph->array[index] = new_vertex;
	pGraph->num_vertex++;

	return index;
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

// BFS -> Breadth-First Search
void bfs(Graph_t* pGraph, Queue_t *pQueue, int* visited, int start)
{
	enqueue(pQueue, start);
	visited[start] = 1;

	while (!isEmpty(pQueue))
	{
		int index = dequeue(pQueue);

		printf("Visitando Vertice: %d\n", index);

		Vertex_t* pVertex = (Vertex_t*)pGraph->array[index];
		Edge_t* neighbor = pVertex->head;

		while (neighbor != NULL)
		{
			if (visited[neighbor->index_dest] == 0)
			{
				visited[neighbor->index_dest] = 1;
				enqueue(pQueue, neighbor->index_dest);
			}

			neighbor = neighbor->next;
		}
	}
}

void start_bfs(Graph_t* pGraph, int start)
{
	int* visited_arr_ptr = (int*)calloc(pGraph->num_vertex, sizeof(int));
	Queue_t* pQueue = create_queue(pGraph);

	bfs(pGraph, pQueue, visited_arr_ptr, start);

	free(visited_arr_ptr);
	destroy_queue(pQueue);
}

int get_degree(Vertex_t* pVertex)
{
	Edge_t* neighbor = pVertex->head;
	int degree = 0;

	while (neighbor != NULL)
	{
		degree++;
		neighbor = neighbor->next;
	}

	return degree;
}

int count_odd_vertices(Graph_t* pGraph)
{
	int odds = 0;

	for (int i = 0; i < pGraph->num_vertex; i++)
	{
		int counter = 0;

		Vertex_t* pVertex = (Vertex_t*)pGraph->array[i];
		Edge_t* neigbour = pVertex->head;

		while (neigbour != NULL)
		{
			counter++;
			neigbour = neigbour->next;
		}

		if (!(counter % 2 == 0))
		{
			odds++;
		}
	}

	return odds;
}

bool isEulerian(Graph_t *pGraph)
{
	int odd = count_odd_vertices(pGraph);
	return odd == 0;
}

bool isUnicursal(Graph_t* pGraph)
{
	int odd = count_odd_vertices(pGraph);
	return odd == 2;
}

int count_edges(Graph_t* pGraph)
{
	int edges = 0;

	for (int i = 0; i < pGraph->num_vertex; i++)
	{

		Vertex_t* pVertex = (Vertex_t*)pGraph->array[i];
		Edge_t* neigbour = pVertex->head;

		while (neigbour != NULL)
		{
			edges++;
			neigbour = neigbour->next;
		}
	}

	return edges / 2;
}

bool isTree(Graph_t* pGraph)
{
	int* visited_arr_ptr = (int*)calloc(pGraph->num_vertex, sizeof(int));
	Queue_t* pQueue = create_queue(pGraph);

	if (visited_arr_ptr == NULL)
	{
		perror("Failed to allocate array visited");
		return false;
	}

	bfs(pGraph, pQueue, visited_arr_ptr, 0);

	for (int i = 0; i < pGraph->num_vertex; i++)
	{
		if (visited_arr_ptr[i] == 0)
		{
			free(visited_arr_ptr);
			destroy_queue(pQueue);
			return false; 
		}
	}

	if (!((pGraph->num_vertex - 1) == count_edges(pGraph)))
	{
		free(visited_arr_ptr);
		destroy_queue(pQueue);
		return false;
	}

	free(visited_arr_ptr);
	destroy_queue(pQueue);

	return true;
}

bool edge_exists(Vertex_t* pVertex, int j)
{
	Edge_t* neigbour = pVertex->head;

	while (neigbour != NULL)
	{
		
		if (neigbour->index_dest == j)
		{
			return true;
		}

		neigbour = neigbour->next;
	}
	

	return false;;
}

void complete_graph(Graph_t *pGraph)
{

	for (int i = 0; i < pGraph->num_vertex; i++)
	{
		Vertex_t* pVertex = (Vertex_t*)pGraph->array[i];
		Edge_t* head = pVertex->head;
		int count_neighbours = get_degree(pVertex);

		if (count_neighbours == (pGraph->num_vertex - 1))
		{
			continue;
		}
		else
		{
			Edge_t* neigbour = pVertex->head;

			for (int j = 0; j < pGraph->num_vertex; j++)
			{
				if (i != j && !(edge_exists(pVertex, j)))
				{
					add_edge(pGraph->array[i], j, 10);
				}
			}
		}
	}
}
