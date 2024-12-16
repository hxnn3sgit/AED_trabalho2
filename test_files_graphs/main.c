// main.c
#include "graph.h"
#include <stdio.h>

int main() {
    // Create a graph with 5 vertices
    Graph *graph = createGraph(5);

    // Add edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Print the graph representation
    printGraph(graph);

    // Free allocated memory
    freeGraph(graph);

    return 0;
}