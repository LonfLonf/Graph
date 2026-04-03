#include "raylib.h"
#include "graphh.h"
#include "gui.h"

int main(void)
{
    InitWindow(800, 450, "Xablau");

    Vector2 nodePosition = { 400.0f, 225.0f };
    float nodeRadius = 15.0f;
    bool isDragging = false;

    Graph_t* pGraph = create_graph(4);
    int selected_vertex = -1;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Vector2 mousePos = GetMousePosition();

        // Talvez criar uma função do tipo: Checar se existe algum vertice naquela posição
        // Ou posso fazer com um loop tb
        //bool isHovering = CheckCollisionPointCircle(mousePos, nodePosition, nodeRadius);

        //if (isHovering && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        //    isDragging = true;
        //}

        //if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        //    isDragging = false;
        //}

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            if (!check_collision(pGraph, mousePosition))
            {
                add_vertex(pGraph, mousePosition, PINK);
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mousePosition = GetMousePosition();
            Vertex_t* clickedVertex = get_vertex_by_position(pGraph, mousePosition);

            if (clickedVertex != -1)
            {
                if (selected_vertex == -1)
                {
                    selected_vertex = clickedVertex;
                }
                else
                {
                    if (selected_vertex != clickedVertex)
                    {
                        add_edge(pGraph->array[selected_vertex], clickedVertex, 10);
                    }

                    selected_vertex = -1;
                }
            }
        }


        if (isDragging) {
            Vector2 delta = GetMouseDelta();
            nodePosition.x += delta.x;
            nodePosition.y += delta.y;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < pGraph->num_vertex; i++)
            {
                Vertex_t* pVertex = (Vertex_t*)pGraph->array[i];
                Edge_t* pEdge_head = pVertex->head;

                while (pEdge_head != NULL)
                {
                    int index_destino = pEdge_head->index_dest;

                    Vertex_t* pDestino = (Vertex_t*)pGraph->array[index_destino];

                    DrawLineEx(pVertex->position, pDestino->position, 3.0f, DARKGRAY);

                    int midX = (pVertex->position.x + pDestino->position.x) / 2;
                    int midY = (pVertex->position.y + pDestino->position.y) / 2;

                    DrawText(TextFormat("%d", pEdge_head->weight), midX - 10, midY - 10, 20, RED);

                    pEdge_head = pEdge_head->next;
                }
            }

            for (int i = 0; i < pGraph->num_vertex; i++)
            {
                Vertex_t* pVertex = (Vertex_t*)pGraph->array[i];
                DrawCircleV(pVertex->position, pVertex->radius, pVertex->color);

                DrawText(TextFormat("%d", i), pVertex->position.x - 5, pVertex->position.y - 10, 20, WHITE);
            }
 
            DrawText(TextFormat("Mouse X: %.2f", GetMousePosition().x), 10, 10, 20, BLUE);
            DrawText(TextFormat("Mouse Y: %.2f", GetMousePosition().y), 10, 30, 20, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}