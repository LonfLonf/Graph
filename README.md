# 🚀 Graph Editor (Editor de Grafos Interativo em C)

Este é um editor e visualizador interativo de grafos desenvolvido em C puro, utilizando a biblioteca gráfica **Raylib**. O projeto permite a criação visual de vértices e arestas, análise de propriedades matemáticas do grafo em tempo real, manipulação interativa de dados, e visualização animada de algoritmos clássicos (DFS, BFS, Kruskal, Dijkstra e Número Cromático).

## ✨ Funcionalidades e Controles

### 🖱️ Interações do Mouse

#### Botão Esquerdo (LMB)
* **Clique em área vazia:** Cria um novo vértice na posição do cursor
* **Clique + Arrasto em um vértice:** Move o vértice para a nova posição
* **Clique em botões:** Ativa as funções do menu (ver seção de Botões)

#### Botão Direito (RMB)
* **Clique em uma aresta:** Remove a aresta (desenho da linha é deletado)
* **Shift + Clique em um vértice:** Remove o vértice e reindexação automática dos vizinhos

#### Mouse Wheel (Roda do Mouse)
* **Scroll para cima/baixo perto de uma aresta:** Aumenta/diminui o peso da aresta (limites: 0-99)

### 📊 Painéis de Informação

#### Painel de Análise (Canto Superior Esquerdo)
Exibe em tempo real:
* Coordenadas do mouse (X, Y)
* Se o grafo é **Árvore** ✓
* Se o grafo é **Euleriano** ✓
* Se o grafo é **Unicursal** ✓
* Total de arestas e vértices

#### Painel de Adjacência (Lado Direito)
Mostra a **Lista de Adjacência completa**:
* Vértice de origem
* Destino(s) conectado(s)
* Peso de cada aresta

### 🎛️ Botões de Controle

| Botão | Descrição | Atalho Visual |
|-------|-----------|---------------|
| **COMPLETAR GRAFO** | Torna o grafo completo (K_n) conectando todos os vértices | - |
| **BUSCA DFS** | Executa Busca em Profundidade animada começando do vértice 0 | Vertices ficam azuis |
| **BUSCA BFS** | Executa Busca em Largura animada começando do vértice 0 | Vertices ficam azuis |
| **AGM** | Calcula a Árvore Geradora Mínima usando algoritmo de Kruskal | Arestas ficam **VERMELHAS** 🔴 |
| **DIJKSTRA** | Encontra o caminho mais curto do vértice 0 até o último vértice | Arestas ficam **VERDES** 🟢 |
| **NÚMERO CROMÁTICO** | Colore o grafo com o mínimo de cores necessárias | Vertices em cores variadas 🎨 |
| **LIMPAR TELA** | Reseta tudo (cores, arestas AGM/Dijkstra, algoritmos) | - |
| **SALVAR GRAFO** | Salva o grafo em arquivo binário `test.graph` | - |

---

## 🔧 Detalhes dos Algoritmos

### 1️⃣ **AGM - Árvore Geradora Mínima (Kruskal)**

**O que faz:**
* Encontra o conjunto de arestas que conecta todos os vértices com o menor peso total
* Usa algoritmo de Kruskal com Union-Find para detectar ciclos
* Executa passo a passo com animação

**Visualização:**
* Durante a execução: Apenas as arestas selecionadas são mostradas em **VERMELHO**
* Outras arestas desaparecem da tela
* Console mostra: Cada aresta incluída e o peso total da AGM

**Configuração:**
* Delay: 0.5 segundos entre cada passo
* Útil para problemas de conectividade mínima (redes, estradas, etc)

**Exemplo prático:**
- Crie 4 vértices em forma de quadrado
- Conecte todos (8 arestas)
- Clique em AGM
- Apenas 3 arestas serão mostradas em vermelho (conectando os 4 vértices)

### 2️⃣ **DIJKSTRA - Caminho Mais Curto**

**O que faz:**
* Encontra o caminho de distância mínima começando do **vértice 0**
* Destino final é o **último vértice criado**
* Para a execução assim que atinge o destino (otimizado)

**Visualização:**
* Durante a execução: Arestas em processamento ficam **VERMELHAS**
* Quando termina: Apenas o **caminho ótimo** é mostrado em **VERDE** 🟢
* Outras arestas desaparecem
* Console mostra: Caminho completo e distância total

**Configuração:**
* Delay: 0.5 segundos entre cada passo
* Útil para GPS, roteamento de rede, planejamento de rotas

**Exemplo prático:**
- Crie 3 vértices em linha (0, 1, 2)
- Ajuste pesos: 0→1 = 5, 1→2 = 3
- Clique em DIJKSTRA
- Verá o caminho 0 → 1 → 2 em verde com distância total de 8

### 3️⃣ **NÚMERO CROMÁTICO - Coloração de Grafo**

**O que faz:**
* Colore os vértices com o **mínimo de cores possíveis**
* Garante que nenhum vértice vizinho tenha a mesma cor
* Algoritmo guloso (não necessariamente ótimo, mas eficiente)

**Visualização:**
* Cada vértice é colorido progressivamente com uma cor diferente
* Paleta de 10 cores:
  - 🔴 Vermelho
  - 🔵 Azul
  - 🟢 Verde
  - 🟡 Amarelo
  - 🟣 Magenta
  - 🟦 Cyan
  - 🟠 Orange
  - 🟪 Purple
  - 🟩 Lime
  - 🟥 Maroon
* Console mostra: Número de cores necessárias ao final

**Configuração:**
* Delay: 0.5 segundos entre cada vértice
* Útil para problemas de alocação de recursos (horários, frequências, etc)

**Exemplo prático:**
- Crie um triângulo (3 vértices conectados)
- Clique em NÚMERO CROMÁTICO
- Verá 3 cores diferentes (uma para cada vértice)
- Para um quadrado: apenas 2 cores serão necessárias

---

## 🏗️ Estruturas de Dados (Structs)

O projeto utiliza o modelo de **Lista de Adjacência** para representar o grafo na memória.

### Estruturas Principais
Definidas em `graphh.h`:

```c
// Representa uma conexão (aresta) na lista ligada de um vértice
typedef struct Edge {
    int index_dest;      // Índice do vértice de destino
    int weight;          // Peso da aresta (0-99)
    float thick;         // Espessura visual da linha
    bool in_mst;         // Flag: está na AGM ou caminho mais curto?
    struct Edge *next;   // Próxima aresta da lista encadeada
} Edge_t;

// Representa um vértice (nó) do grafo
typedef struct Vertex {
    char label[50];      // Rótulo (ex: "Vértice 0")
    float radius;        // Raio do círculo visual
    Edge_t* head;        // Primeira aresta conectada
    Vector2 position;    // Coordenadas X, Y na tela
    Color color;         // Cor atual (muda conforme algoritmos)
} Vertex_t;

// Estrutura principal do grafo
typedef struct Graph {
    int num_vertex;      // Total de vértices
    int capacity;        // Capacidade máxima alocada
    Vertex_t** array;    // Array de ponteiros para vértices
} Graph_t;
```

### Estruturas dos Algoritmos

```c
// Estado do Kruskal para execução passo a passo
typedef struct KruskalState {
    KruskalEdge_t* edges;    // Array de arestas ordenadas por peso
    int* parent;             // Array Union-Find
    int* rank;               // Ranks para otimização Union-Find
    int edge_count;          // Total de arestas
    int current_edge;        // Aresta sendo processada
    int mst_weight;          // Peso total acumulado
    bool finished;           // Algoritmo terminou?
} KruskalState_t;

// Estado do Dijkstra para execução passo a passo
typedef struct DijkstraState {
    int* distance;           // Menor distância até cada vértice
    bool* visited;           // Vértices já processados
    int* parent;             // Pais no caminho mais curto
    int source;              // Vértice de origem (sempre 0)
    int destination;         // Vértice de destino (último vértice)
    int current_vertex;      // Vértice processado agora
    int vertices_processed;  // Contador
    int num_vertex;          // Total de vértices
    bool finished;           // Algoritmo terminou?
} DijkstraState_t;

// Estado do Número Cromático para execução passo a passo
typedef struct ChromaticState {
    int* color;              // Cor de cada vértice (-1 = sem cor)
    int num_colors;          // Total de cores usadas
    int num_vertex;          // Total de vértices
    int current_vertex;      // Vértice sendo colorido
    bool finished;           // Algoritmo terminou?
} ChromaticState_t;
```

---

## 📁 Estrutura do Projeto

### Arquivos Principais

| Arquivo | Responsabilidade |
|---------|-----------------|
| `main.c` | Loop principal, interface, máquinas de estado dos algoritmos |
| `graph.c` | Lógica dos algoritmos (Kruskal, Dijkstra, Cromático) |
| `graphh.h` | Definições de structs e declarações globais |
| `gui.c` | Renderização visual, salvamento e carregamento |
| `gui.h` | Declarações de funções da GUI |
| `queue.c` / `queue.h` | Implementação de fila (BFS) |
| `stack.c` / `stack.h` | Implementação de pilha (DFS) |
| `logo.png` | Ícone da aplicação |

### Executável

O programa já está compilado e pronto para usar:
```
Graph/x64/Release/Graph.exe
```

Para executar, clique duas vezes ou use:
```bash
./Graph.exe
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Árvore Geradora Mínima
```
1. Crie um grafo com 4 vértices em forma de quadrado
2. Conecte todos os vértices:
   - 0 ↔ 1 (peso 5)
   - 1 ↔ 2 (peso 3)
   - 2 ↔ 3 (peso 4)
   - 3 ↔ 0 (peso 2)
   - 0 ↔ 2 (peso 7)
   - 1 ↔ 3 (peso 6)
3. Clique no botão AGM
4. Observarão 3 arestas em VERMELHO com peso total de 9
5. Console mostra: Aresta 3-0 (2), Aresta 1-2 (3), Aresta 1-0 (5)
```

### Exemplo 2: Caminho Mais Curto
```
1. Crie 4 vértices em linha: 0, 1, 2, 3
2. Configure pesos:
   - 0 → 1 = 2
   - 1 → 2 = 3
   - 2 → 3 = 1
   - 0 → 3 = 10 (caminho direto mais caro)
3. Clique em DIJKSTRA
4. O caminho 0 → 1 → 2 → 3 aparecerá em VERDE
5. Distância total: 6 (melhor que o caminho direto de 10)
```

### Exemplo 3: Colorir Grafo
```
1. Crie um triângulo (3 vértices todos conectados)
2. Clique em NÚMERO CROMÁTICO
3. Cada vértice recebe uma cor diferente (precisam 3 cores)
4. Crie um quadrado (4 vértices conectados em ciclo)
5. Clique em NÚMERO CROMÁTICO
6. Apenas 2 cores são suficientes (alternando)
```

---

## 🎯 Casos de Uso Práticos

| Algoritmo | Aplicação Real | Exemplo |
|-----------|---------------|---------|
| **AGM (Kruskal)** | Redes de infraestrutura | Conectar cidades com estradas/fibra com custo mínimo |
| **Dijkstra** | Navegação GPS | Encontrar rota mais rápida de A para B |
| **Número Cromático** | Agendamento | Agendar aulas sem conflitos (cada aula = cor) |
| **DFS/BFS** | Busca em estruturas | Explorar labirintos ou árvores de diretórios |

---

## 🎨 Cores e Legenda Visual

### Durante os Algoritmos
- 🔴 **VERMELHO**: Arestas sendo processadas ou na AGM
- 🟢 **VERDE**: Caminho final encontrado (Dijkstra)
- 🔵 **AZUL**: Vértices visitados (DFS/BFS)
- 🔴🔵🟢🟡🟣: Colores variadas (Número Cromático)

### Estados das Arestas
- **Cinza**: Aresta normal
- **VERMELHO** (AGM): Aresta selecionada para a árvore mínima
- **VERDE** (Dijkstra): Aresta no caminho mais curto
- **Desaparece**: Quando AGM/Dijkstra termina e oculta as outras arestas

---

## ⚙️ Configurações e Limites

| Parâmetro | Valor | Descrição |
|-----------|-------|-----------|
| **Peso mínimo** | 0 | Limite inferior para peso de arestas |
| **Peso máximo** | 99 | Limite superior para peso de arestas |
| **Delay DFS/BFS** | 0.5 s | Tempo entre passos da busca |
| **Delay AGM** | 0.5 s | Tempo entre passos do Kruskal |
| **Delay Dijkstra** | 0.5 s | Tempo entre passos do Dijkstra |
| **Delay Cromático** | 0.5 s | Tempo entre colorações |
| **Cores máximas** | 10 | Paleta visual disponível |
| **Vértices recomendados** | até 50 | Para fluidez ótima |

---

## 🔒 Gerenciamento de Memória

O projeto usa **C puro** sem vazamentos:
- ✅ Alocação dinâmica com `malloc()` e `realloc()`
- ✅ Liberação com `free()` ao finalizar
- ✅ Funções específicas: `Kruskal_free()`, `Dijkstra_free()`, `Chromatic_free()`
- ✅ Limpeza de estruturas auxiliares: `destroy_queue()`, `destroy_stack()`

---

## 📝 Notas Importantes

⚠️ **AGM e Dijkstra:**
- Ambos usam o flag `in_mst` das arestas para marcar seleção
- Quando você clica em "LIMPAR TELA", este flag é resetado

⚠️ **Número Cromático:**
- Algoritmo guloso (não garante solução ótima)
- Funciona para grafos conexos ou desconexos
- Máximo de 10 cores visualmente

⚠️ **Dijkstra:**
- Sempre começa do vértice **0**
- Sempre termina no **último vértice criado**
- Pausa assim que atinge o destino (otimização)

⚠️ **Remoção de Vértices:**
- Ao remover um vértice, os índices dos vizinhos são automaticamente atualizados
- Todas as arestas conectadas são removidas

⚠️ **Performance:**
- Recomendado até 50 vértices para máxima fluidez
- Com 100+ vértices, a renderização pode ficar mais lenta

---

## 📚 Referências Matemáticas

- **Algoritmo de Kruskal:** https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
- **Algoritmo de Dijkstra:** https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
- **Coloração de Grafos:** https://en.wikipedia.org/wiki/Graph_coloring
- **Busca em Profundidade (DFS):** https://en.wikipedia.org/wiki/Depth-first_search
- **Busca em Largura (BFS):** https://en.wikipedia.org/wiki/Breadth-first_search

---

## 🛠️ Funções Principais em `graph.c`

### Algoritmos com Visualização
- `Kruskal_init()` - Inicializa o estado do Kruskal
- `Kruskal_step()` - Processa um passo do Kruskal
- `Dijkstra_init()` - Inicializa o Dijkstra
- `Dijkstra_step()` - Processa um passo do Dijkstra
- `Chromatic_init()` - Inicializa o Número Cromático
- `Chromatic_step()` - Colore um vértice

### Operações Básicas
- `create_graph()` - Cria um novo grafo
- `add_vertex()` - Adiciona um vértice
- `add_edge()` - Adiciona uma aresta
- `remove_vertex()` - Remove um vértice
- `remove_edge()` - Remove uma aresta
- `complete_graph()` - Torna o grafo completo

### Análise de Propriedades
- `isTree()` - Verifica se é árvore
- `isEulerian()` - Verifica se é Euleriano
- `isUnicursal()` - Verifica se é Unicursal
- `count_edges()` - Conta arestas

---
