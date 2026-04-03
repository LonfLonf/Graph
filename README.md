# Xablau - Graph Editor & Analyzer

O **Xablau** é um editor de grafos interativo desenvolvido em **C** utilizando a biblioteca **Raylib**. O projeto permite a criação visual de vértices e arestas, além de fornecer uma análise em tempo real das propriedades matemáticas do grafo.

## 🚀 Funcionalidades

* **Interação Visual:** Adicione vértices com cliques e conecte-os dinamicamente.
* **Algoritmos de Busca:** Implementação de **BFS** (Busca em Largura) e **DFS** (Busca em Profundidade).
* **Análise Estrutural:** Identificação automática de Grafos Eulerianos, Unicursais e Árvores.
* **Manipulação de Matriz/Lista:** Visualização da lista de adjacência em tempo real na interface.
* **Geração Automática:** Função para transformar o conjunto de vértices em um **Grafo Completo**.

## 🛠️ Tecnologias Utilizadas

* **Linguagem C:** Lógica de estruturas de dados e ponteiros.
* **Raylib:** Renderização gráfica e gerenciamento de inputs.
* **Estruturas de Dados:** Listas encadeadas para arestas e arrays dinâmicos para vértices.

## 📂 Estrutura do Projeto

* `main.c`: Ponto de entrada e loop principal da interface.
* `graph.c / graphh.h`: Core da lógica de grafos e algoritmos.
* `gui.c / gui.h`: Funções de auxílio para a interface e colisões.
* `queue.c / queue.h`: Implementação de fila para suporte ao BFS.

## 🧠 Structs
### Graphh.h
#### Edge_t
```
typedef struct Edge {
	int index_dest;
	int weight;
	float thick;
	struct Edge *next;
} Edge_t;
```
#### Vertex_t
```
typedef struct Vertex {
	char label[50];
	float radius;
	Edge_t* head;
	Vector2 position;
	Color color;
} Vertex_t;
```

#### Graph_t
```
typedef struct Graph {
	int num_vertex;
	int capacity; 
	Vertex_t** array; 
} Graph_t;
```

### queue.h
#### Queue_t
```
typedef struct Queue {
	int start;
	int end;
	int capacity;
	int* pArr;
} Queue_t;
```

## 🧠 Explicação das Funções

> *Espaço reservado para a sua explicação detalhada das funções do sistema.*

### Graphh.h
#### `Graph_t* create_graph(int initial_capacity)`:
A função create_graph é responsável pela criação da struct Graph_t. Essa função é obrigatoria a ser declarada antes do uso de qualquer funcionalidade disponivel.

#### `int add_vertex(Graph_t* pGraph, Vector2 position, Color color);`:
Função responsável por criar um adicionar após o clique do usuario um vertex. Para utilizar essa função antes é necessario ter criado o Grafo, pegar o Vector2 com a função GetMousePosition() e por ultimo colocar alguma color que no nosso código será PINK.
Dentro do código da função é possivel ver no primeiro bloco um check para consultar se a capacidade do Grafo está cheia, caso esteja dobramos a capacidade e damos um realloc e retornamos o novo ponteiro para a nova struct do Grafo.
Caso não esteja cheio o Grafo temos um processo de inicialização padrão da struct Vertex_t.

## ⚙️ Como Compilar e Rodar

1. Certifique-se de ter o compilador `gcc` e a biblioteca `raylib` instalados.
2. No terminal, execute o comando:
   ```bash
   gcc main.c graph.c gui.c queue.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o xablau
