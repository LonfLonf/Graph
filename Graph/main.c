#include <stdio.h>
#include "graphh.h"

int main()
{
	// Criando um grafo de teste (Caminho de 4 vértices: 0-1-2-3)
	// Esse formato inicialmente é uma árvore e também é unicursal!
	Graph_t* pGraph = create_graph(4);

	add_edge(pGraph->array[0], 1, 10);
	add_edge(pGraph->array[1], 0, 10);

	add_edge(pGraph->array[1], 2, 10);
	add_edge(pGraph->array[2], 1, 10);

	add_edge(pGraph->array[2], 3, 10);
	add_edge(pGraph->array[3], 2, 10);

	printf("=== ESTRUTURA INICIAL ===\n");
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