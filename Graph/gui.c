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