#include "raylib.h"
#include "graphh.h"
#include "gui.h"
#include "stack.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    Graph_t* pGraph = NULL;

    if (argc > 1)
    {
        load_graph_debug(argv[1], &pGraph);
    }
    else
    {
        pGraph = create_graph(4);
    }

    int screenWidth = 1600;
    int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Editor de Grafos");

    Image logo = LoadImage("logo.png");
    SetWindowIcon(logo);

    bool isDragging = false;
    int draggingVertex = -1;

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

    bool isKruskalRunning = false;
    float kruskalTimer = 0.0f;
    float kruskalDelay = 0.9f;
    KruskalState_t* pKruskalState = NULL;
    bool kruskalFinished = false;

    bool isDijkstraRunning = false;
    float dijkstraTimer = 0.0f;
    float dijkstraDelay = 0.5f;
    DijkstraState_t* pDijkstraState = NULL;
    bool dijkstraFinished = false;

    bool isChromaticRunning = false;
    float chromaticTimer = 0.0f;
    float chromaticDelay = 0.5f;
    ChromaticState_t* pChromaticState = NULL;
    bool chromaticFinished = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        Rectangle btnComplete = { 20, 240, 280, 30 };
        Rectangle btnDFS = { 20, 280, 280, 30 };
        Rectangle btnBFS = { 20, 320, 280, 30 };
        Rectangle btnAGM = { 20, 360, 280, 30 };
        Rectangle btnDijkstra = { 20, 400, 280, 30 };
        Rectangle btnCrom = { 20, 440, 280, 30 }; 

        Rectangle btnClear = { 20, 480, 280, 30 };
        Rectangle btnSave = { 20, 520, 280, 30 };

        Vector2 mousePosition = GetMousePosition();

        bool hoverComplete = CheckCollisionPointRec(mousePosition, btnComplete);
        bool hoverDFS = CheckCollisionPointRec(mousePosition, btnDFS);
        bool hoverBFS = CheckCollisionPointRec(mousePosition, btnBFS);
        bool hoverClear = CheckCollisionPointRec(mousePosition, btnClear);
        bool hoverSave = CheckCollisionPointRec(mousePosition, btnSave);

        bool hoverAGM = CheckCollisionPointRec(mousePosition, btnAGM);
        bool hoverDijkstra = CheckCollisionPointRec(mousePosition, btnDijkstra);
        bool hoverCrom = CheckCollisionPointRec(mousePosition, btnCrom);

        bool mouseOnButtons = hoverComplete || hoverDFS || hoverBFS || hoverClear || hoverSave || hoverAGM 
            || hoverDijkstra || hoverCrom;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            draggingVertex = get_vertex_by_position(pGraph, mousePosition);

            if (draggingVertex != -1) {
                isDragging = true;
            } else if (!check_collision(pGraph, mousePosition) && !mouseOnButtons)
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

            if (hoverAGM && pGraph->num_vertex > 0) {
                if (!isKruskalRunning) {
                    isKruskalRunning = true;
                    kruskalTimer = 0.0f;
                    pKruskalState = Kruskal_init(pGraph);
                }
            }

            if (hoverDijkstra && pGraph->num_vertex > 0) {
                if (!isDijkstraRunning) {
                    isDijkstraRunning = true;
                    dijkstraTimer = 0.0f;
                    pDijkstraState = Dijkstra_init(pGraph, 0);
                }
            }

            if (hoverCrom && pGraph->num_vertex > 0) {
                if (!isChromaticRunning) {
                    isChromaticRunning = true;
                    chromaticTimer = 0.0f;
                    pChromaticState = Chromatic_init(pGraph);
                }
            }

            if (hoverClear) {
                clean_graph(pGraph);
                isKruskalRunning = false;
                kruskalFinished = false;
                isDijkstraRunning = false;
                dijkstraFinished = false;
                isChromaticRunning = false;
                chromaticFinished = false;
                if (pKruskalState) {
                    Kruskal_free(pKruskalState);
                    pKruskalState = NULL;
                }
                if (pDijkstraState) {
                    Dijkstra_free(pDijkstraState);
                    pDijkstraState = NULL;
                }
                if (pChromaticState) {
                    Chromatic_free(pChromaticState);
                    pChromaticState = NULL;
                }
                status_isTree = isTree(pGraph);
                status_isEulerian = isEulerian(pGraph);
                status_isUnicursal = isUnicursal(pGraph);
            }

            if (hoverSave) {
                int edges = count_edges(pGraph);
                save_graph(pGraph, edges);
            }
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (isDragging && draggingVertex != -1) {
                Vector2 newMousePosition = GetMousePosition();
                Vertex_t* pVertex = (Vertex_t*)pGraph->array[draggingVertex];
                pVertex->position = newMousePosition;
            }
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isDragging = false;
            draggingVertex = -1;
        }

        float mouseWheel = GetMouseWheelMove();
        if (mouseWheel != 0) {
            Vector2 mousePosition = GetMousePosition();
            for (int i = 0; i < pGraph->num_vertex; i++) {
                Vertex_t* pVertex = (Vertex_t*)pGraph->array[i];
                Edge_t* pEdge_head = pVertex->head;

                while (pEdge_head != NULL) {
                    Vertex_t* pDestino = (Vertex_t*)pGraph->array[pEdge_head->index_dest];

                    Vector2 midPoint;
                    midPoint.x = (pVertex->position.x + pDestino->position.x) / 2.0f;
                    midPoint.y = (pVertex->position.y + pDestino->position.y) / 2.0f;

                    if (CheckCollisionPointCircle(mousePosition, midPoint, 20.0f)) {
                        pEdge_head->weight += (int)mouseWheel;
                        if (pEdge_head->weight < 0) pEdge_head->weight = 0;
                        if (pEdge_head->weight > 99) pEdge_head->weight = 99;

                        Edge_t* pEdge_back = pDestino->head;
                        while (pEdge_back != NULL) {
                            if (pEdge_back->index_dest == i) {
                                pEdge_back->weight = pEdge_head->weight;
                                break;
                            }
                            pEdge_back = pEdge_back->next;
                        }
                    }

                    pEdge_head = pEdge_head->next;
                }
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mousePosition = GetMousePosition();
            bool edgeClicked = false;

            for (int i = 0; i < pGraph->num_vertex; i++) {
                Vertex_t* pVertex = (Vertex_t*)pGraph->array[i];
                Edge_t* pEdge_head = pVertex->head;

                while (pEdge_head != NULL) {
                    Vertex_t* pDestino = (Vertex_t*)pGraph->array[pEdge_head->index_dest];
                    int dest_index = pEdge_head->index_dest;

                    Vector2 midPoint;
                    midPoint.x = (pVertex->position.x + pDestino->position.x) / 2.0f;
                    midPoint.y = (pVertex->position.y + pDestino->position.y) / 2.0f;

                    if (CheckCollisionPointCircle(mousePosition, midPoint, 20.0f)) {
                        remove_edge(pVertex, dest_index);
                        remove_edge(pDestino, i);
                        edgeClicked = true;

                        status_isTree = isTree(pGraph);
                        status_isEulerian = isEulerian(pGraph);
                        status_isUnicursal = isUnicursal(pGraph);
                        break;
                    }

                    pEdge_head = pEdge_head->next;
                }
                if (edgeClicked) break;
            }

            if (!edgeClicked) {
                int clickedVertex = get_vertex_by_position(pGraph, mousePosition);


                if (clickedVertex != -1 && IsKeyDown(KEY_LEFT_SHIFT)) {
                    remove_vertex(pGraph, clickedVertex);
                    if (selected_vertex == clickedVertex) selected_vertex = -1;
                    if (draggingVertex == clickedVertex) {
                        draggingVertex = -1;
                        isDragging = false;
                    }

                    status_isTree = isTree(pGraph);
                    status_isEulerian = isEulerian(pGraph);
                    status_isUnicursal = isUnicursal(pGraph);
                } 
                else if (clickedVertex != -1)
                {
                    if (selected_vertex == -1)
                    {
                        selected_vertex = clickedVertex;
                    }
                    else
                    {
                        if (selected_vertex != clickedVertex)
                        {
                            int weight = create_random_weights();
                            add_edge(pGraph->array[selected_vertex], clickedVertex, weight);
                            add_edge(pGraph->array[clickedVertex], selected_vertex, weight);
                            status_isTree = isTree(pGraph);
                            status_isEulerian = isEulerian(pGraph);
                            status_isUnicursal = isUnicursal(pGraph);
                        }

                        selected_vertex = -1;
                    }
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

        if (isKruskalRunning) {
            kruskalTimer += GetFrameTime();

            if (kruskalTimer >= kruskalDelay) {
                kruskalTimer = 0.0f;

                if (pKruskalState && !pKruskalState->finished) {
                    Kruskal_step(pGraph, pKruskalState);
                }
                else if (pKruskalState && pKruskalState->finished) {
                    isKruskalRunning = false;
                    kruskalFinished = true;
                }
            }
        }

        if (isDijkstraRunning) {
            dijkstraTimer += GetFrameTime();

            if (dijkstraTimer >= dijkstraDelay) {
                dijkstraTimer = 0.0f;

                if (pDijkstraState && !pDijkstraState->finished) {
                    Dijkstra_step(pGraph, pDijkstraState);
                }
                else if (pDijkstraState && pDijkstraState->finished) {
                    isDijkstraRunning = false;
                    dijkstraFinished = true;
                }
            }
        }

        if (isChromaticRunning) {
            chromaticTimer += GetFrameTime();

            if (chromaticTimer >= chromaticDelay) {
                chromaticTimer = 0.0f;

                if (pChromaticState && !pChromaticState->finished) {
                    Chromatic_step(pGraph, pChromaticState);
                }
                else if (pChromaticState && pChromaticState->finished) {
                    isChromaticRunning = false;
                    chromaticFinished = true;
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

                    if (kruskalFinished) {
                        if (pEdge_head->in_mst) {
                            DrawLineEx(pVertex->position, pDestino->position, 3.0f, RED);

                            int midX = (pVertex->position.x + pDestino->position.x) / 2;
                            int midY = (pVertex->position.y + pDestino->position.y) / 2;
                            DrawText(TextFormat("%d", pEdge_head->weight), midX - 10, midY - 10, 20, WHITE);
                        }
                    } else if (dijkstraFinished) {
                        if (pEdge_head->in_mst) {
                            DrawLineEx(pVertex->position, pDestino->position, 3.0f, GREEN);

                            int midX = (pVertex->position.x + pDestino->position.x) / 2;
                            int midY = (pVertex->position.y + pDestino->position.y) / 2;
                            DrawText(TextFormat("%d", pEdge_head->weight), midX - 10, midY - 10, 20, WHITE);
                        }
                    } else {
                        Color edgeColor = pEdge_head->in_mst ? RED : DARKGRAY;
                        DrawLineEx(pVertex->position, pDestino->position, 3.0f, edgeColor);

                        int midX = (pVertex->position.x + pDestino->position.x) / 2;
                        int midY = (pVertex->position.y + pDestino->position.y) / 2;
                        DrawText(TextFormat("%d", pEdge_head->weight), midX - 10, midY - 10, 20, RED);
                    }

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

            DrawRectangle(10, 230, 300, 350, Fade(BLACK, 0.8f));
            DrawRectangleLines(10, 230, 300, 350, GRAY);

            DrawRectangleRec(btnComplete, hoverComplete ? LIGHTGRAY : DARKGRAY);
            DrawRectangleLinesEx(btnComplete, 1, BLACK);
            int textCompleteWidth = MeasureText("COMPLETAR GRAFO", 20);
            DrawText("COMPLETAR GRAFO", btnComplete.x + (btnComplete.width - textCompleteWidth) / 2, btnComplete.y + 5, 20, hoverComplete ? BLACK : WHITE);

            DrawRectangleRec(btnDFS, hoverDFS ? LIGHTGRAY : DARKGRAY);
            DrawRectangleLinesEx(btnDFS, 1, BLACK);
            int textDFSWidth = MeasureText("BUSCA DFS", 20);
            DrawText("BUSCA DFS", btnDFS.x + (btnDFS.width - textDFSWidth) / 2, btnDFS.y + 5, 20, hoverDFS ? BLACK : WHITE);

            DrawRectangleRec(btnBFS, hoverBFS ? LIGHTGRAY : DARKGRAY);
            DrawRectangleLinesEx(btnBFS, 1, BLACK);
            int textBFSWidth = MeasureText("BUSCA BFS", 20);
            DrawText("BUSCA BFS", btnBFS.x + (btnBFS.width - textBFSWidth) / 2, btnBFS.y + 5, 20, hoverBFS ? BLACK : WHITE);

            DrawRectangleRec(btnAGM, hoverAGM ? LIGHTGRAY : DARKGRAY);
            DrawRectangleLinesEx(btnAGM, 1, BLACK);
            int textAGMWidth = MeasureText("AGM", 20);
            DrawText("AGM", btnAGM.x + (btnAGM.width - textAGMWidth) / 2, btnAGM.y + 5, 20, hoverAGM ? BLACK : WHITE);

            DrawRectangleRec(btnDijkstra, hoverDijkstra ? LIGHTGRAY : DARKGRAY);
            DrawRectangleLinesEx(btnDijkstra, 1, BLACK);
            int textDijkstraWidth = MeasureText("DIJKSTRA", 20);
            DrawText("DIJKSTRA", btnDijkstra.x + (btnDijkstra.width - textDijkstraWidth) / 2, btnDijkstra.y + 5, 20, hoverDijkstra ? BLACK : WHITE);

            DrawRectangleRec(btnCrom, hoverCrom ? LIGHTGRAY : DARKGRAY);
            DrawRectangleLinesEx(btnCrom, 1, BLACK);
            int textCromWidth = MeasureText("NÚMERO CROMATICO", 20);
            DrawText("NÚMERO CROMATICO", btnCrom.x + (btnCrom.width - textCromWidth) / 2, btnCrom.y + 5, 20, hoverCrom ? BLACK : WHITE);

            DrawRectangleRec(btnClear, hoverClear ? LIGHTGRAY : MAROON);
            DrawRectangleLinesEx(btnClear, 1, BLACK);
            int textClearWidth = MeasureText("LIMPAR TELA", 20);
            DrawText("LIMPAR TELA", btnClear.x + (btnClear.width - textClearWidth) / 2, btnClear.y + 5, 20, hoverClear ? BLACK : WHITE);

            DrawRectangleRec(btnSave, hoverSave ? LIGHTGRAY : DARKGREEN);
            DrawRectangleLinesEx(btnSave, 1, BLACK);
            int textSaveWidth = MeasureText("SALVAR GRAFO", 20);
            DrawText("SALVAR GRAFO", btnSave.x + (btnSave.width - textSaveWidth) / 2, btnSave.y + 5, 20, hoverSave ? BLACK : WHITE);

        EndDrawing();
    }

    UnloadImage(logo);
    CloseWindow();
    return 0;
}