#include <stdio.h>
#include <string.h>
#include "gui.h"


bool check_collision(Graph_t* pGraph, Vector2 mousePosition)
{
    float raio_padrao = 20.0f;
    float margem_seguranca = 5.0f;

    for (int i = 0; i < pGraph->num_vertex; i++)
    {
        Vertex_t* pVertex = (Vertex_t*)pGraph->array[i];

        if (CheckCollisionCircles(mousePosition, raio_padrao + margem_seguranca, pVertex->position, pVertex->radius))
        {
            return true;
        }
    }

    return false;
}

int get_vertex_by_position(Graph_t* pGraph, Vector2 mousePosition)
{
    float raio_padrao = 20.0f;
    float margem_seguranca = 5.0f;

    for (int i = 0; i < pGraph->num_vertex; i++)
    {
        Vertex_t* pVertex = (Vertex_t*)pGraph->array[i];

        if (CheckCollisionCircles(mousePosition, raio_padrao + margem_seguranca, pVertex->position, pVertex->radius))
        {
            return i;
        }
    }

    return -1;
}

void DrawGridBackground(int screenWidth, int screenHeight, int spacing)
{
    Color gridColor = Fade(LIGHTGRAY, 0.5f);

    for (int x = 0; x <= screenWidth; x += spacing)
    {
        DrawLine(x, 0, x, screenHeight, gridColor);
    }

    for (int y = 0; y <= screenHeight; y += spacing)
    {
        DrawLine(0, y, screenWidth, y, gridColor);
    }
}

void clean_graph(Graph_t* pGraph)
{
    for (int i = 0; i < pGraph->num_vertex; i++)
    {
        pGraph->array[i]->color = PINK;

        Edge_t* pEdge = pGraph->array[i]->head;
        while (pEdge != NULL) {
            pEdge->in_mst = false;
            pEdge = pEdge->next;
        }
    }
}

char* create_file_name(Graph_t* pGraph)
{
    char* name = (char*)malloc(30 * sizeof(char));
    if (name == NULL) return NULL;

    sprintf_s(name, 30, "%d_%d.graph", pGraph->capacity, pGraph->num_vertex);

    return name;
}

void save_graph(Graph_t* pGraph, int edges)
{
    char* name_file = create_file_name(pGraph);

    FILE* pFile = fopen(name_file, "wb");

    if (pFile == NULL)
    {
        printf("Error to create the file");
        return;
    }

    int num_vertex = pGraph->num_vertex;

    Header_t header = { "GRAPH", num_vertex, edges };

    fwrite(&header, sizeof(header), 1, pFile);
    
    for (int i = 0; i < pGraph->num_vertex; i++)
    {
        Vertex_t* pVertex = pGraph->array[i];

        VertexDisk_t VertexDisk;
        strncpy_s(VertexDisk.label, sizeof(VertexDisk.label), pVertex->label, _TRUNCATE);
        VertexDisk.label[sizeof(VertexDisk.label) - 1] = '\0';
        
        VertexDisk.x = pVertex->position.x;
        VertexDisk.y = pVertex->position.y;
        VertexDisk.radius = pVertex->radius;
        VertexDisk.a = pVertex->color.a;
        VertexDisk.b = pVertex->color.b;
        VertexDisk.g = pVertex->color.g;
        VertexDisk.r = pVertex->color.r;

        fwrite(&VertexDisk, sizeof(VertexDisk), 1, pFile);
    }

    for (int i = 0; i < pGraph->num_vertex; i++)
    {
        Vertex_t* pVertex = pGraph->array[i];
        Edge_t* neighbour = pVertex->head;

        while (neighbour != NULL)
        {
            EdgeDisk_t EdgeDisk;

            EdgeDisk.index_dest = neighbour->index_dest;
            EdgeDisk.vertex = i;
            EdgeDisk.thick = neighbour->thick;
            EdgeDisk.weight = neighbour->weight;

            fwrite(&EdgeDisk, sizeof(EdgeDisk), 1, pFile);
            
            neighbour = neighbour->next;
        }
    }

    free(name_file);
    fclose(pFile);
}

void load_graph_debug(const char* filename, Graph_t **pGraph)
{
    FILE* pFile = fopen(filename, "rb");

    if (pFile == NULL)
    {
        printf("Erro ao abrir o arquivo '%s'!\n", filename);
        return;
    }

    Header_t graph_disk;
    fread(&graph_disk, sizeof(Header_t), 1, pFile);
    
    *pGraph = create_graph(graph_disk.qtd_vertex);

    for (int i = 0; i < graph_disk.qtd_vertex; i++)
    {
        VertexDisk_t v;

        fread(&v, sizeof(VertexDisk_t), 1, pFile);

        Vector2 position = { v.x, v.y };
        Color color = { v.r, v.g, v.b, v.a };

        add_vertex(*pGraph, position, color);
    }

    EdgeDisk_t e;

    while (fread(&e, sizeof(EdgeDisk_t), 1, pFile) == 1)
    {
        add_edge((*pGraph)->array[e.vertex], e.index_dest, e.weight);
    }

    fclose(pFile);
}