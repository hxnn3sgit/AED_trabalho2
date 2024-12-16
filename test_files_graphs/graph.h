// graph.h
#ifndef GRAPH_H
#define GRAPH_H

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph {
    int numVertices;
    Node **adjLists;
} Graph;

Graph *createGraph(int vertices);
void addEdge(Graph *graph, int src, int dest);
void printGraph(Graph *graph);
void freeGraph(Graph *graph);

#endif