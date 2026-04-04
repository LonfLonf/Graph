# 🚀 Graph Editor (Editor de Grafos Interativo em C)

Este é um editor e visualizador interativo de grafos desenvolvido em C puro, utilizando a biblioteca gráfica **Raylib**. O projeto permite a criação visual de vértices e arestas, análise de propriedades matemáticas do grafo em tempo real e visualização animada de algoritmos de busca clássicos.

## ✨ Funcionalidades e Controles

O editor possui uma interface gráfica customizada dividida em painéis e botões de interação.

* **Botão Esquerdo do Mouse (LMB):** * Clica em áreas vazias da grade para criar um novo vértice.
  * Interage com os botões do menu (Completar Grafo, Busca DFS, Busca BFS, Limpar Tela, Salvar Grafo).
* **Botão Direito do Mouse (RMB):**
  * Usado para criar arestas. Clique em um vértice (ele será selecionado) e, em seguida, clique em outro vértice para traçar a aresta conectando-os.
* **Painel de Análise (Esquerda):** Exibe as coordenadas do mouse, se o grafo é Euleriano, Unicursal ou uma Árvore, além de mostrar o número de pares ordenados (arestas).
* **Painel de Adjacência (Direita):** Mostra em tempo real a Lista de Adjacência do grafo atual, detalhando as conexões de origem e destino.

---

## 🏗️ Estruturas de Dados (Structs)

O projeto utiliza o modelo de **Lista de Adjacência** para representar o grafo na memória.

### Estruturas do Grafo na Memória (RAM)
Definidas em `graphh.h`:

```c
// Representa uma conexão (aresta) na lista ligada de um vértice.
typedef struct Edge {
	int index_dest;   // Índice do vértice de destino no array principal.
	int weight;       // Peso da aresta.
	float thick;      // Espessura da linha (para renderização visual).
	struct Edge *next;// Ponteiro para a próxima aresta da lista (encadeamento).
} Edge_t;

// Representa um nó (vértice) do grafo.
typedef struct Vertex {
	char label[50];   // Rótulo textual do vértice (ex: "Vertice 0").
	float radius;     // Raio do círculo desenhado na tela.
	Edge_t* head;     // Ponteiro para o início da lista ligada de arestas.
	Vector2 position; // Posição (X, Y) na tela.
	Color color;      // Cor atual do vértice (muda durante as animações de busca).
} Vertex_t;

// A estrutura principal que encapsula o grafo inteiro.
typedef struct Graph {
	int num_vertex;   // Quantidade atual de vértices criados.
	int capacity;     // Capacidade máxima alocada atualmente (cresce via realloc).
	Vertex_t** array; // Array dinâmico de ponteiros para os vértices.
} Graph_t;

```

### Estruturas de Persistência (Disco)
Projetadas com tamanhos fixos para serialização (salvar/carregar arquivos .graph binários).
Definidas em `graphh.h`:

```c
// Cabeçalho do arquivo salvo.
typedef struct Header {
	char header_name[5]; // Assinatura do arquivo (ex: "GRAPH").
	int qtd_vertex;      // Total de vértices salvos.
	int qtd_edges;       // Total de arestas salvas.
} Header_t;

// Representação de uma aresta para o arquivo em disco.
typedef struct EdgeDisk {
	int vertex;       // Índice do vértice de origem.
	int index_dest;   // Índice do vértice de destino.
	int weight;       // Peso da aresta.
	float thick;      // Espessura visual.
} EdgeDisk_t;

// Representação de um vértice sem ponteiros, para salvar em disco.
typedef struct VertexDisk {
	char label[50];      // Rótulo.
	unsigned int color;  // Cor aglutinada.
	unsigned char r, g, b, a; // Componentes RGBA da cor separadas.
	float radius;        // Raio do círculo.
	float x, y;          // Posições no eixo cartesiano da tela.
} VertexDisk_t;

```

### Estruturas de Persistência (Disco)
Projetadas com tamanhos fixos para serialização (salvar/carregar arquivos .graph binários).
Definidas em `queue.h` e `stack.h`:

```c
// Fila Circular (para a Busca em Largura - BFS).
typedef struct Queue {
	int start;        // Índice do início da fila.
	int end;          // Índice do fim da fila.
	int capacity;     // Tamanho máximo (baseado no total de vértices).
	int* pArr;        // Array de inteiros para guardar os índices dos vértices.
} Queue_t;

// Pilha Dinâmica (para a Busca em Profundidade - DFS).
typedef struct Stack {
    int top;          // Índice do topo da pilha (-1 se vazia).
    int capacity;     // Capacidade atual da pilha.
    int* pArr;        // Array de inteiros para guardar os índices empilhados.
} Stack_t;

```

### 1. Núcleo do Grafo (`graph.c` e `graphh.h`)
Responsável por toda a matemática e manipulação de memória da estrutura de dados.

* **`create_graph(int initial_capacity)`:** Aloca o array de ponteiros principal.
* **`add_vertex(...)`:** Cria um novo vértice. Utiliza `realloc` automaticamente se o limite do array for atingido, garantindo crescimento dinâmico.
* **`add_edge(...)`:** Adiciona uma aresta direcionada conectando um vértice de origem a um de destino.
* **`print_ordered_pairs(...)`:** Imprime a lista de adjacência no console (usado para debug).
* **`dfs(...)`:** Executa um passo da Busca em Profundidade desempilhando o nó atual e empilhando os vizinhos não visitados, alterando suas cores.
* **`bfs(...)`:** Executa a Busca em Largura de forma instantânea (sem delay visual).
* **`bfs_step(...)`:** Executa um único passo da Busca em Largura usando a fila. Fundamental para a animação "frame a frame" na interface.
* **`start_bfs(...)`:** Função auxiliar (wrapper) para inicializar a fila e iniciar o processo de BFS completo no console.
* **`get_degree(...)`:** Retorna o grau de um vértice (quantas arestas ele possui).
* **`count_odd_vertices(...)`:** Retorna a quantidade de vértices com grau ímpar.
* **`isEulerian(...)`:** Verifica se existe um ciclo Euleriano (0 vértices de grau ímpar).
* **`isUnicursal(...)`:** Verifica se existe um caminho Euleriano (exatamente 2 vértices de grau ímpar).
* **`isTree(...)`:** Verifica simultaneamente se o grafo é conexo (usando BFS) e se o número de arestas obedece a regra $E = V - 1$.
* **`count_edges(...)`:** Retorna o total de arestas do grafo inteiro dividindo por 2 (assumindo grafo não-direcionado nas renderizações).
* **`edge_exists(...)`:** Checa se já existe conexão entre dois vértices específicos.
* **`complete_graph(...)`:** Percorre todos os vértices e adiciona as arestas faltantes para torná-lo um grafo totalmente conexo (todos ligados a todos).

### 2. Interface e Persistência (`gui.c` e `gui.h`)
* **`check_collision(...)`:** Checa se o mouse está pairando sobre algum vértice (com margem de segurança de 5 pixels).
* **`get_vertex_by_position(...)`:** Retorna o índice exato do vértice que foi clicado.
* **`DrawGridBackground(...)`:** Função puramente visual que renderiza as linhas de grade cinza claro.
* **`clean_graph(...)`:** Reseta a cor de todos os vértices para `PINK`, limpando as marcações azuis deixadas pelas buscas DFS/BFS.
* **`save_graph(...)`:** Grava o estado atual do grafo em disco (`test.graph`) abrindo um fluxo binário (`wb`) e salvando primeiro o header, depois os vértices de disco e, por fim, as arestas de disco.
* **`load_graph_debug(...)`:** Lê o arquivo binário (`rb`) e reconstrói o grafo completamente na memória usando `add_vertex` e `add_edge`.

### 3. Loop Principal (`main.c`)
* É a alma da aplicação. Inicializa a janela `1780x1000` a `60 FPS`.
* Controla as "máquinas de estado" das buscas (variáveis como `isDfsRunning`, `dfsTimer`, `dfsDelay`) para criar o efeito de delay visual agradável.
* Renderiza as linhas das arestas e textos (`DrawLineEx`, `DrawText`) conectando os centros dos círculos.
* Mantém o gerenciamento dinâmico de cliques nas bounding boxes (retângulos virtuais) dos botões do menu lateral esquerdo.

### 4. Estruturas Auxiliares (`queue.c` e `stack.c`)
* Métodos clássicos implementados em C puro: `enqueue`, `dequeue`, `push`, `pop`, `isFull`, `isEmpty`. Ambas possuem a função de destroy para limpar corretamente as alocações da heap (evitando vazamento de memória) após a finalização da busca visual no mapa.