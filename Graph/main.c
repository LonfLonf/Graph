#include <stdio.h>
#include "graphh.h"

int main()
{
	// Criando um grafo com capacidade inicial de 2, para forçar o realloc e testar!
	Graph_t* pGraph = create_graph(2);

	// Posições e cores fictícias só pro terminal rodar (no Raylib virá do mouse)
	Vector2 dummy_pos = { 0, 0 };
	Color dummy_col = BLACK;

	// Adicionando os vértices um por um (como se fossem 4 cliques)
	add_vertex(pGraph, dummy_pos, dummy_col); // Cria o Vértice 0
	add_vertex(pGraph, dummy_pos, dummy_col); // Cria o Vértice 1
	add_vertex(pGraph, dummy_pos, dummy_col); // Cria o Vértice 2 (AQUI O REALLOC ACONTECE!)
	add_vertex(pGraph, dummy_pos, dummy_col); // Cria o Vértice 3

	// Agora sim podemos ligar eles!
	add_edge(pGraph->array[0], 1, 10);
	add_edge(pGraph->array[1], 0, 10);

	add_edge(pGraph->array[1], 2, 10);
	add_edge(pGraph->array[2], 1, 10);

	add_edge(pGraph->array[2], 3, 10);
	add_edge(pGraph->array[3], 2, 10);

	printf("=== ESTRUTURA DINÂMICA FUNCIONANDO ===\n");
	printf("Total de Vértices: %d\n", pGraph->num_vertex);
	printf("Capacidade Atual da Memória: %d\n\n", pGraph->capacity);

	print_ordered_pairs(pGraph);

	printf("=== TESTE DA ÁRVORE ===\n");
	if (isTree(pGraph)) {
		printf("Resultado: É UMA ÁRVORE! 🌲\n");
	}
	else {
		printf("Resultado: NÃO é uma árvore.\n");
	}

	printf("\n=== TESTE EULERIANO E UNICURSAL ===\n");
	printf("É Euleriano (Ciclo fechado)? %s\n", isEulerian(pGraph) ? "Sim" : "Nao");
	printf("É Unicursal (Caminho que não fecha)? %s\n", isUnicursal(pGraph) ? "Sim" : "Nao");

	printf("\n=== COMPLETANDO O GRAFO ===\n");
	printf("Transformando em Grafo Completo (K4)...\n");
	complete_graph(pGraph);

	printf("\nNovas Conexoes (Todos conhecem todos):\n");
	print_ordered_pairs(pGraph);

	// Testando a árvore novamente após completar (agora cheio de ciclos, não deve ser árvore)
	printf("=== TESTE DA ÁRVORE (APÓS COMPLETAR) ===\n");
	if (isTree(pGraph)) {
		printf("Resultado: É UMA ÁRVORE! 🌲\n");
	}
	else {
		printf("Resultado: NÃO é mais uma árvore (encontramos ciclos!).\n");
	}

	return 0;
}