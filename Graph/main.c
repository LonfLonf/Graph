#include "graphh.h"

int main()
{
	Graph_t* pGraph = create_graph(4);

	// Connections Vertex 0
	add_edge(pGraph->array[0], 1, 10.0);
	add_edge(pGraph->array[0], 2, 10.0);
	add_edge(pGraph->array[0], 3, 10.0);

	// Connections Vertex 1
	add_edge(pGraph->array[1], 0, 10.0);
	add_edge(pGraph->array[1], 2, 10.0);

	// Connections Vertex 2
	add_edge(pGraph->array[2], 0, 10.0);
	add_edge(pGraph->array[2], 1, 10.0);
	add_edge(pGraph->array[2], 3, 10.0);

	// Connections Vertex 3
	add_edge(pGraph->array[3], 0, 10.0);
	add_edge(pGraph->array[3], 2, 10.0);

	print_ordered_pairs(pGraph);

	start_dfs(pGraph, 0);
	printf("\n");
	start_bfs(pGraph, 0);
}