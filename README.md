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

## 🧠 Explicação das Funções

> *Espaço reservado para a sua explicação detalhada das funções do sistema.*

---

## ⚙️ Como Compilar e Rodar

1. Certifique-se de ter o compilador `gcc` e a biblioteca `raylib` instalados.
2. No terminal, execute o comando:
   ```bash
   gcc main.c graph.c gui.c queue.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o xablau
