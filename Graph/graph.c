#include "graphh.h"

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
	pEdge->in_mst = false;
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

void dfs(Graph_t* pGraph, Stack_t* pStack, int* visited_dfs)
{
	int current = pop(pStack);

	if (visited_dfs[current] == 0) {
		visited_dfs[current] = 1;
		pGraph->array[current]->color = DARKBLUE;
		printf("Visitando: %d\n", current);

		Edge_t* neighbor = pGraph->array[current]->head;
		while (neighbor != NULL) {
			if (visited_dfs[neighbor->index_dest] == 0) {
				push(pStack, neighbor->index_dest);
				pGraph->array[neighbor->index_dest]->color = SKYBLUE;
			}
			neighbor = neighbor->next;
		}
	}
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

void bfs_step(Graph_t* pGraph, Queue_t* pQueueBfs, int* visited_bfs)
{
	int current = dequeue(pQueueBfs);

	if (current == -1) return;

	pGraph->array[current]->color = DARKBLUE;
	printf("BFS Visitando: %d\n", current);

	Edge_t* neighbor = pGraph->array[current]->head;
	while (neighbor != NULL) {
		int dest = neighbor->index_dest;
		if (visited_bfs[dest] == 0) {
			visited_bfs[dest] = 1;
			enqueue(pQueueBfs, dest);
			pGraph->array[dest]->color = SKYBLUE;
		}
		neighbor = neighbor->next;
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
					add_edge(pGraph->array[i], j, create_random_weights());
				}
			}
		}
	}
}

int create_random_weights()
{
	return (rand() % 15) + 1;
}

bool remove_edge(Vertex_t* pVertex, int dest)
{
	if (pVertex == NULL || pVertex->head == NULL) return false;

	Edge_t* current = pVertex->head;
	Edge_t* previous = NULL;

	while (current != NULL)
	{
		if (current->index_dest == dest)
		{
			if (previous == NULL) {
				pVertex->head = current->next;
			}
			else {
				previous->next = current->next;
			}
			free(current);
			return true;
		}
		previous = current;
		current = current->next;
	}
	return false;
}

void remove_vertex(Graph_t* pGraph, int index)
{
	if (pGraph == NULL || index < 0 || index >= pGraph->num_vertex) return;

	Vertex_t* pVertexToRemove = pGraph->array[index];

	for (int i = 0; i < pGraph->num_vertex; i++)
	{
		Vertex_t* pVertex = pGraph->array[i];

		remove_edge(pVertex, index);

		Edge_t* current = pVertex->head;
		while (current != NULL)
		{
			if (current->index_dest > index) {
				current->index_dest--;
			}
			current = current->next;
		}
	}

	Edge_t* current = pVertexToRemove->head;
	while (current != NULL)
	{
		Edge_t* next = current->next;
		free(current);
		current = next;
	}
	free(pVertexToRemove);

	for (int i = index; i < pGraph->num_vertex - 1; i++)
	{
		pGraph->array[i] = pGraph->array[i + 1];
	}

	pGraph->num_vertex--;
}

int sort_kruskal(const void *a, const void *b)
{
	KruskalEdge_t* edgeA = (KruskalEdge_t*)a;
	KruskalEdge_t* edgeB = (KruskalEdge_t*)b;

	return (edgeA->weight - edgeB->weight);
}

int find_parent(int parent[], int i) {
	if (parent[i] == i)
		return i;
	return parent[i] = find_parent(parent, parent[i]);
}

void union_sets(int parent[], int rank[], int x, int y) {
	int xroot = find_parent(parent, x);
	int yroot = find_parent(parent, y);

	if (rank[xroot] < rank[yroot])
		parent[xroot] = yroot;
	else if (rank[xroot] > rank[yroot])
		parent[yroot] = xroot;
	else {
		parent[yroot] = xroot;
		rank[xroot]++;
	}
}

KruskalState_t* Kruskal_init(Graph_t* pGraph)
{
	if (pGraph->num_vertex <= 0) return NULL;

	int max_edges = count_edges(pGraph) * 2; 
	if (max_edges == 0) return NULL;

	KruskalState_t* pState = malloc(sizeof(KruskalState_t));
	if (pState == NULL) return NULL;

	KruskalEdge_t* pArr = malloc(sizeof(KruskalEdge_t) * max_edges);
	if (pArr == NULL) {
		free(pState);
		return NULL;
	}

	int edge_index = 0;

	for (int i = 0; i < pGraph->num_vertex; i++)
	{
		Vertex_t *pVertex = (Vertex_t*)pGraph->array[i];
		Edge_t* neigbour = pVertex->head;

		while (neigbour != NULL)
		{
			if (i < neigbour->index_dest) {
				pArr[edge_index].src = i;
				pArr[edge_index].dest = neigbour->index_dest;
				pArr[edge_index].weight = neigbour->weight;
				edge_index++;
			}
			neigbour = neigbour->next;
		}
	}

	qsort(pArr, edge_index, sizeof(KruskalEdge_t), sort_kruskal);

	int* parent = malloc(sizeof(int) * pGraph->num_vertex);
	int* rank = calloc(pGraph->num_vertex, sizeof(int));

	if (parent == NULL || rank == NULL) {
		free(parent);
		free(rank);
		free(pArr);
		free(pState);
		return NULL;
	}

	for (int i = 0; i < pGraph->num_vertex; i++) {
		parent[i] = i;
	}

	pState->edges = pArr;
	pState->parent = parent;
	pState->rank = rank;
	pState->edge_count = edge_index;
	pState->current_edge = 0;
	pState->mst_weight = 0;
	pState->finished = false;

	return pState;
}

void Kruskal_step(Graph_t* pGraph, KruskalState_t* pState)
{
	if (pState == NULL || pState->finished || pState->current_edge >= pState->edge_count) {
		if (pState && !pState->finished) {
			pState->finished = true;
		}
		return;
	}

	KruskalEdge_t* edge = &pState->edges[pState->current_edge];
	int src = edge->src;
	int dest = edge->dest;
	int weight = edge->weight;

	int x = find_parent(pState->parent, src);
	int y = find_parent(pState->parent, dest);

	if (x != y) {
		pState->mst_weight += weight;
		union_sets(pState->parent, pState->rank, x, y);

		Vertex_t* pSrcVertex = (Vertex_t*)pGraph->array[src];
		Edge_t* pEdge = pSrcVertex->head;
		while (pEdge != NULL) {
			if (pEdge->index_dest == dest) {
				pEdge->in_mst = true;
				break;
			}
			pEdge = pEdge->next;
		}

		Vertex_t* pDestVertex = (Vertex_t*)pGraph->array[dest];
		pEdge = pDestVertex->head;
		while (pEdge != NULL) {
			if (pEdge->index_dest == src) {
				pEdge->in_mst = true;
				break;
			}
			pEdge = pEdge->next;
		}
	}

	pState->current_edge++;
}

void Kruskal_free(KruskalState_t* pState)
{
	if (pState == NULL) return;
	free(pState->edges);
	free(pState->parent);
	free(pState->rank);
	free(pState);
}

DijkstraState_t* Dijkstra_init(Graph_t* pGraph, int source)
{
	if (pGraph->num_vertex <= 0 || source < 0 || source >= pGraph->num_vertex) {
		return NULL;
	}

	DijkstraState_t* pState = malloc(sizeof(DijkstraState_t));
	if (pState == NULL) return NULL;

	pState->distance = malloc(sizeof(int) * pGraph->num_vertex);
	pState->visited = malloc(sizeof(bool) * pGraph->num_vertex);
	pState->parent = malloc(sizeof(int) * pGraph->num_vertex);

	if (pState->distance == NULL || pState->visited == NULL || pState->parent == NULL) {
		free(pState->distance);
		free(pState->visited);
		free(pState->parent);
		free(pState);
		return NULL;
	}

	for (int i = 0; i < pGraph->num_vertex; i++) {
		pState->distance[i] = (i == source) ? 0 : INT_MAX;
		pState->visited[i] = false;
		pState->parent[i] = -1;
	}

	pState->source = source;
	pState->destination = pGraph->num_vertex - 1; 
	pState->current_vertex = source;
	pState->vertices_processed = 0;
	pState->num_vertex = pGraph->num_vertex;
	pState->finished = false;

	return pState;
}

void Dijkstra_step(Graph_t* pGraph, DijkstraState_t* pState)
{
	if (pState == NULL || pState->finished || pState->vertices_processed >= pState->num_vertex) {
		if (pState && !pState->finished) {
			pState->finished = true;

			int current = pState->destination;

			while (current != pState->source && pState->parent[current] != -1) {
				int parent = pState->parent[current];

				Vertex_t* pParentVertex = (Vertex_t*)pGraph->array[parent];
				Edge_t* pEdge = pParentVertex->head;
				while (pEdge != NULL) {
					if (pEdge->index_dest == current) {
						pEdge->in_mst = true;
						break;
					}
					pEdge = pEdge->next;
				}

				current = parent;
			}
		}
		return;
	}

	if (pState->visited[pState->destination]) {
		pState->finished = true;

		int current = pState->destination;

		while (current != pState->source && pState->parent[current] != -1) {
			int parent = pState->parent[current];

			Vertex_t* pParentVertex = (Vertex_t*)pGraph->array[parent];
			Edge_t* pEdge = pParentVertex->head;
			while (pEdge != NULL) {
				if (pEdge->index_dest == current) {
					pEdge->in_mst = true;
					break;
				}
				pEdge = pEdge->next;
			}

			current = parent;
		}

		return;
	}

	int minDist = INT_MAX;
	int minVertex = -1;

	for (int i = 0; i < pState->num_vertex; i++) {
		if (!pState->visited[i] && pState->distance[i] < minDist) {
			minDist = pState->distance[i];
			minVertex = i;
		}
	}

	if (minVertex == -1) {
		pState->finished = true;
		return;
	}

	pState->visited[minVertex] = true;
	pState->vertices_processed++;

	Vertex_t* pVertex = (Vertex_t*)pGraph->array[minVertex];
	Edge_t* pEdge = pVertex->head;

	while (pEdge != NULL) {
		int neighbor = pEdge->index_dest;
		int weight = pEdge->weight;

		if (!pState->visited[neighbor]) {
			int newDist = (pState->distance[minVertex] == INT_MAX) ? INT_MAX : pState->distance[minVertex] + weight;

			if (newDist < pState->distance[neighbor]) {
				pState->distance[neighbor] = newDist;
				pState->parent[neighbor] = minVertex;

			}
		}

		pEdge = pEdge->next;
	}
}

void Dijkstra_free(DijkstraState_t* pState)
{
	if (pState == NULL) return;
	free(pState->distance);
	free(pState->visited);
	free(pState->parent);
	free(pState);
}

void Dijkstra(Graph_t* pGraph)
{
	if (pGraph->num_vertex <= 0) return;

	DijkstraState_t* pState = Dijkstra_init(pGraph, 0);
	if (pState == NULL) return;

	while (!pState->finished) {
		Dijkstra_step(pGraph, pState);
	}

	Dijkstra_free(pState);
}

Color get_chromatic_color(int color_index)
{
	switch(color_index) {
		case 0: return RED;
		case 1: return BLUE;
		case 2: return GREEN;
		case 3: return YELLOW;
		case 4: return MAGENTA;
		case 5: return (Color){0, 255, 255, 255}; 
		case 6: return ORANGE;
		case 7: return PURPLE;
		case 8: return LIME;
		case 9: return MAROON;
		default: return WHITE;
	}
}

ChromaticState_t* Chromatic_init(Graph_t* pGraph)
{
	if (pGraph->num_vertex <= 0) return NULL;

	ChromaticState_t* pState = malloc(sizeof(ChromaticState_t));
	if (pState == NULL) return NULL;

	pState->color = malloc(sizeof(int) * pGraph->num_vertex);
	if (pState->color == NULL) {
		free(pState);
		return NULL;
	}

	for (int i = 0; i < pGraph->num_vertex; i++) {
		pState->color[i] = -1;
	}

	pState->num_vertex = pGraph->num_vertex;
	pState->current_vertex = 0;
	pState->num_colors = 0;
	pState->finished = false;

	return pState;
}

void Chromatic_step(Graph_t* pGraph, ChromaticState_t* pState)
{
	if (pState == NULL || pState->finished || pState->current_vertex >= pState->num_vertex) {
		if (pState && !pState->finished) {
			pState->finished = true;
		}
		return;
	}

	int vertex = pState->current_vertex;
	
	bool* available = malloc(sizeof(bool) * (pState->num_colors + 1));
	for (int i = 0; i <= pState->num_colors; i++) {
		available[i] = true;
	}

	Vertex_t* pVertex = (Vertex_t*)pGraph->array[vertex];
	Edge_t* pEdge = pVertex->head;

	while (pEdge != NULL) {
		int neighbor = pEdge->index_dest;
		if (pState->color[neighbor] != -1) {
			available[pState->color[neighbor]] = false;
		}
		pEdge = pEdge->next;
	}

	int color = 0;
	while (color <= pState->num_colors && !available[color]) {
		color++;
	}

	pState->color[vertex] = color;

	if (color >= pState->num_colors) {
		pState->num_colors = color + 1;
	}

	printf("Vertice %d colorido com cor %d\n", vertex, color);

	if (color < 10) {
		pGraph->array[vertex]->color = get_chromatic_color(color);
	}

	pState->current_vertex++;
	free(available);
}

void Chromatic_free(ChromaticState_t* pState)
{
	if (pState == NULL) return;
	free(pState->color);
	free(pState);
}

void CromaticNumber(Graph_t* pGraph)
{

	if (pGraph->num_vertex <= 0) return;

	ChromaticState_t* pState = Chromatic_init(pGraph);
	if (pState == NULL) return;

	while (!pState->finished) {
		Chromatic_step(pGraph, pState);
	}

	Chromatic_free(pState);
}
