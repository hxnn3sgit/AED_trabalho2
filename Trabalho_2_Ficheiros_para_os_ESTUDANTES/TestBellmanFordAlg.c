//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira, Joao Manuel Rodrigues - Dec 2024
//
// Testing the Bellman-Ford algorithm
//

#include <assert.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

int main(void) {
    // What kind of graph is dig01?
    Graph* dig01 = GraphCreate(6, 1, 0);
    GraphAddEdge(dig01, 1, 2);
    GraphAddEdge(dig01, 1, 4);
    GraphAddEdge(dig01, 3, 4);

    printf("The graph:\n");
    // Displaying in DOT format
    GraphDisplayDOT(dig01);
    printf("\n");

    GraphCheckInvariants(dig01);

    // Bellman-Ford Algorithm
    // Consider each vertex as a start vertex
    for (unsigned int i = 0; i < 6; i++) {
        InitializeInstrumentation();
        InstrCalibrate();

        double startTime = cpu_time();
        GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(dig01, i);
        double endTime = cpu_time();

        printf("The shortest path tree rooted at %u\n", i);
        GraphBellmanFordAlgDisplayDOT(BF_result);
        printf("\n");

        // Get memory usage for BF_result
        size_t numVertices = GraphGetNumVertices(dig01); // Number of vertices remains the same
        size_t numEdges = 0;

        for (unsigned int j = 0; j < numVertices; ++j) {
            if (GraphBellmanFordAlgReached(BF_result, j) && GraphBellmanFordAlgGetPredecessor(BF_result, j) != -1) {
                numEdges++;
            }
        }

        size_t vertexSize = sizeof(unsigned int) + sizeof(int) * 2; // marked, distance, predecessor
        size_t edgeSize = sizeof(int);
        size_t memoryUsage = EstimateMemoryUsage(numVertices, numEdges, vertexSize, edgeSize);

        printf("Execution Time: %.6f seconds\n", endTime - startTime);
        PrintInstrumentationMetrics("BellmanFord Algorithm", memoryUsage);

        InstrReset();
        GraphBellmanFordAlgDestroy(&BF_result);
    }

    // What kind of graph is g01?
    Graph* g01 = GraphCreate(6, 0, 0);
    GraphAddEdge(g01, 0, 5);
    GraphAddEdge(g01, 2, 4);
    GraphAddEdge(g01, 2, 3);
    GraphAddEdge(g01, 1, 2);
    GraphAddEdge(g01, 0, 1);
    GraphAddEdge(g01, 3, 4);
    GraphAddEdge(g01, 3, 5);
    GraphAddEdge(g01, 0, 2);

    printf("The graph:\n");
    // Displaying in DOT format
    GraphDisplayDOT(g01);
    printf("\n");

    GraphCheckInvariants(g01);

    // Bellman-Ford Algorithm
    InitializeInstrumentation();

    // Consider each vertex as a start vertex
    for (unsigned int i = 0; i < 6; i++) {
        double startTime = cpu_time();
        GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(g01, i);
        double endTime = cpu_time();

        printf("The shortest path tree rooted at %u\n", i);
        GraphBellmanFordAlgDisplayDOT(BF_result);
        printf("\n");

        printf("Execution Time: %.6f seconds\n", endTime - startTime);
        GraphBellmanFordAlgDestroy(&BF_result);
    }

    InstrPrint();

    // Reading a directed graph from file
    FILE* file = fopen("DG_2.txt", "r");
    Graph* dig03 = GraphFromFile(file);
    fclose(file);

    // Displaying in DOT format
    GraphDisplayDOT(dig03);
    printf("\n");

    GraphCheckInvariants(dig03);

    // Bellman-Ford Algorithm
    InstrReset();
    InitializeInstrumentation();

    // Consider each vertex as a start vertex
    for (unsigned int i = 0; i < GraphGetNumVertices(dig03); i++) {
        double startTime = cpu_time();
        GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(dig03, i);
        double endTime = cpu_time();

        printf("The shortest path tree rooted at %u\n", i);
        GraphBellmanFordAlgDisplayDOT(BF_result);
        printf("\n");

        printf("Execution Time: %.6f seconds\n", endTime - startTime);
        GraphBellmanFordAlgDestroy(&BF_result);
    }

    InstrPrint();

    GraphDestroy(&g01);
    GraphDestroy(&dig01);
    GraphDestroy(&dig03);

    return 0;
}