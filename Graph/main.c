#include "raylib.h"
#include "graphh.h"
#include "gui.h"
#include "stack.h"

int main(void)
{
    int screenWidth = 1780;
    int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Xablau");

    bool isDragging = false;

    Graph_t* pGraph = create_graph(4);
    int selected_vertex = -1;
    bool status_isTree = false;
    bool status_isUnicursal = false;
    bool status_isEulerian = false;

    bool isDfsRunning = false;
    float dfsTimer = 0.0f;
    float dfsDelay = 0.5f; 
    int* visited_dfs = NULL;
    Stack_t* pStack = create_stack(pGraph->num_vertex);

    bool isBfsRunning = false;
    float bfsTimer = 0.0f;
    float bfsDelay = 0.9f;
    int* visited_bfs = NULL;
    Queue_t* pQueueBfs = NULL;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        Rectangle btnComplete = { 20, 240, 280, 30 };
        Rectangle btnDFS = { 20, 280, 280, 30 };
        Rectangle btnBFS = { 20, 320, 280, 30 };
        Rectangle btnClear = { 20, 360, 280, 30 };

        Vector2 mousePosition = GetMousePosition();

        bool hoverComplete = CheckCollisionPointRec(mousePosition, btnComplete);
        bool hoverDFS = CheckCollisionPointRec(mousePosition, btnDFS);
        bool hoverBFS = CheckCollisionPointRec(mousePosition, btnBFS);
        bool hoverClear = CheckCollisionPointRec(mousePosition, btnClear);

        bool mouseOnButtons = hoverComplete || hoverDFS || hoverBFS || hoverClear;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {

            if (!check_collision(pGraph, mousePosition) && !mouseOnButtons)
            {
                add_vertex(pGraph, mousePosition, PINK);
                status_isTree = isTree(pGraph);
                status_isEulerian = isEulerian(pGraph);
                status_isUnicursal = isUnicursal(pGraph);
            }

            if (hoverComplete) {
                complete_graph(pGraph);
                status_isTree = isTree(pGraph);
                status_isEulerian = isEulerian(pGraph);
                status_isUnicursal = isUnicursal(pGraph);
            }

            if (hoverDFS && pGraph->num_vertex > 0) {
                if (!isDfsRunning) {
                    isDfsRunning = true;
                    dfsTimer = 0.0f;
                    visited_dfs = (int*)calloc(pGraph->num_vertex, sizeof(int));
                    pStack = create_stack(10);
                    push(pStack, 0);
                }
            }

            if (hoverBFS && pGraph->num_vertex > 0) {
                if (!isBfsRunning)
                {
                    isBfsRunning = true;
                    bfsTimer = 0.0f;
                    visited_bfs = (int*)calloc(pGraph->num_vertex, sizeof(int));
                    pQueueBfs = create_queue(pGraph);

                    visited_bfs[0] = 1;
                    enqueue(pQueueBfs, 0);
                }
            }

            if (hoverClear) {
                clean_graph(pGraph);
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mousePosition = GetMousePosition();
            int clickedVertex = get_vertex_by_position(pGraph, mousePosition);

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
                        add_edge(pGraph->array[clickedVertex], selected_vertex, 10);
                        status_isTree = isTree(pGraph);
                        status_isEulerian = isEulerian(pGraph);
                        status_isUnicursal = isUnicursal(pGraph);
                    }

                    selected_vertex = -1;
                }
            }

        }

        if (isDfsRunning) {
            dfsTimer += GetFrameTime();

            if (dfsTimer >= dfsDelay) {
                dfsTimer = 0.0f;

                if (!isStackEmpty(pStack)) {
                    dfs(pGraph, pStack, visited_dfs);
                }
                else {

                    isDfsRunning = false;
                    if (visited_dfs) free(visited_dfs);
                    if (pStack) destroy_stack(pStack);
                    visited_dfs = NULL;
                    pStack = NULL;
                }
            }
        }

        if (isBfsRunning) {
            bfsTimer += GetFrameTime();

            if (bfsTimer >= bfsDelay) {
                bfsTimer = 0.0f;

                if (!isEmpty(pQueueBfs)) {
                    bfs_step(pGraph, pQueueBfs, visited_bfs);
                }
                else {
                    isBfsRunning = false;
                    if (visited_bfs) free(visited_bfs);
                    if (pQueueBfs) destroy_queue(pQueueBfs); 
                    visited_bfs = NULL;
                    pQueueBfs = NULL;
                }
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            DrawGridBackground(screenWidth, screenHeight, 40);

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
 
            DrawRectangle(10, 10, 300, 210, Fade(BLACK, 0.8f));
            DrawRectangleLines(10, 10, 300, 210, GRAY);

            DrawText("ANÁLISE DO GRAFO", 30, 20, 20, WHITE);
            DrawLine(20, 45, 290, 45, DARKGRAY);

            DrawText(TextFormat("Mouse X: %.0f", GetMousePosition().x), 30, 55, 20, SKYBLUE);
            DrawText(TextFormat("Mouse Y: %.0f", GetMousePosition().y), 160, 55, 20, SKYBLUE);

            DrawLine(20, 85, 290, 85, DARKGRAY); 

            DrawText("Euleriano:", 30, 100, 20, LIGHTGRAY);
            DrawText(status_isEulerian ? "SIM" : "NÃO", 180, 100, 20, status_isEulerian ? LIME : RED);

            DrawText("Unicursal:", 30, 125, 20, LIGHTGRAY);
            DrawText(status_isUnicursal ? "SIM" : "NÃO", 180, 125, 20, status_isUnicursal ? LIME : RED);

            DrawText("Árvore:", 30, 150, 20, LIGHTGRAY);
            DrawText(status_isTree ? "SIM" : "NÃO", 180, 150, 20, status_isTree ? LIME : RED);

            DrawText(TextFormat("Pares Ordenados: %d", count_edges(pGraph)), 30, 180, 20, ORANGE);

            int panelWidth = 250;
            int panelX = GetScreenWidth() - panelWidth - 10;
            int panelY = 10;

            DrawRectangle(panelX, panelY, panelWidth, 850, Fade(BLACK, 0.8f));
            DrawRectangleLines(panelX, panelY, panelWidth, 850, GRAY);

            DrawText("LISTA DE ADJACÊNCIA", panelX + 20, panelY + 20, 17, WHITE);
            DrawLine(panelX + 10, panelY + 45, panelX + panelWidth - 10, panelY + 45, DARKGRAY);

            int offsetY = panelY + 60;
            bool list_full = false;

            for (int i = 0; i < pGraph->num_vertex; i++)
            {
                if (list_full) break; 

                Vertex_t* pVertex = (Vertex_t*)pGraph->array[i];
                Edge_t* pEdge_head = pVertex->head;

                while (pEdge_head != NULL)
                {
                    
                    if (offsetY > panelY + 810)
                    {
                        DrawText("...", panelX + 20, offsetY, 20, ORANGE);
                        list_full = true;
                        break;
                    }

                    DrawText(TextFormat("Origem: %d -> Destino: %d", i, pEdge_head->index_dest), panelX + 20, offsetY, 20, LIGHTGRAY);

                    offsetY += 25;

                    pEdge_head = pEdge_head->next;
                }
            }

            DrawRectangle(10, 230, 300, 170, Fade(BLACK, 0.8f));
            DrawRectangleLines(10, 230, 300, 170, GRAY);

            DrawRectangleRec(btnComplete, hoverComplete ? LIGHTGRAY : DARKGRAY);
            DrawRectangleLinesEx(btnComplete, 1, BLACK);
            DrawText("COMPLETAR GRAFO", btnComplete.x + 45, btnComplete.y + 5, 20, hoverComplete ? BLACK : WHITE);

            DrawRectangleRec(btnDFS, hoverDFS ? LIGHTGRAY : DARKGRAY);
            DrawRectangleLinesEx(btnDFS, 1, BLACK);
            DrawText("BUSCA DFS", btnDFS.x + 85, btnDFS.y + 5, 20, hoverDFS ? BLACK : WHITE);

            DrawRectangleRec(btnBFS, hoverBFS ? LIGHTGRAY : DARKGRAY);
            DrawRectangleLinesEx(btnBFS, 1, BLACK);
            DrawText("BUSCA BFS", btnBFS.x + 85, btnBFS.y + 5, 20, hoverBFS ? BLACK : WHITE);

            DrawRectangleRec(btnClear, hoverClear ? LIGHTGRAY : MAROON);
            DrawRectangleLinesEx(btnClear, 1, BLACK);
            DrawText("LIMPAR TELA", btnClear.x + 75, btnClear.y + 5, 20, hoverClear ? BLACK : WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}