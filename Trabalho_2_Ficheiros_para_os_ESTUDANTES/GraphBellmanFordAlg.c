//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphBellmanFord - Bellman-Ford Algorithm
//

// Student Name : Hannes Seidl
// Student Number : 123643
// Student Name :
// Student Number :

/*** COMPLETE THE GraphBellmanFordAlgExecute FUNCTION ***/

#include "GraphBellmanFordAlg.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Graph.h"
#include "IntegersStack.h"
#include "instrumentation.h"

struct _GraphBellmanFordAlg {
  unsigned int* marked;  // To mark vertices when reached for the first time
  int* distance;  // The number of edges on the path from the start vertex
                  // distance[i]=-1, if no path found from the start vertex to i
  int* predecessor;  // The predecessor vertex in the shortest path
                     // predecessor[i]=-1, if no predecessor exists
  Graph* graph;
  unsigned int startVertex;  // The root of the shortest-paths tree
};

/*
GraphBellmanFordAlg* GraphBellmanFordAlgExecute(Graph* g,
                                                unsigned int startVertex) {
  int numVertices = GraphGetNumVertices(g);
  int numEdges = GraphGetNumEdges(g);
  assert(g != NULL);
  assert(startVertex < numVertices);
  assert(GraphIsWeighted(g) == 0);

  GraphBellmanFordAlg* result =
      (GraphBellmanFordAlg*)malloc(sizeof(struct _GraphBellmanFordAlg));
  assert(result != NULL);

  // Given graph and start vertex for the shortest-paths
  result->graph = g;
  result->startVertex = startVertex;

  // TO BE COMPLETED !!
  //
  // CREATE AND INITIALIZE
  
  // marked array and distance array initialization:
  // allocation:
  result->marked = malloc(sizeof(unsigned int) * numVertices);
  result->distance = malloc(sizeof(int) * numEdges);
  result->predecessor = malloc(sizeof(int) * numVertices);

  // initialization:
  memset(result->marked, 0, numVertices, sizeof(int));
  memset(result->distance, -1, numVertices, sizeof(int));
  memset(result->predecessor, -1, numVertices, sizeof(int));
  result->distance[startVertex] = 0; // distance to itself is 0

  int stopflag = 1;

  // stop flag idee
  // while loop
	// GET adjacents, because i am not longer in graph.c, but there are functions
  // Mark all vertices as not yet visited, i.e., ZERO

  // No vertex has (yet) a (valid) predecessor
  
  // No vertex has (yet) a (valid) distance to the start vertex
  
  // THE ALGORTIHM TO BUILD THE SHORTEST-PATHS TREE
  
  int stopflag = 0;
  for (int i = 0; i < numVertices - 1; ++i) {
	stopflag = 0;
	for (int u = 0; u < numVertices; ++u) {
		List *adjacents = GraphGetAdjacents(g, 
	}
  }

  return NULL;
}
*/
// new version:
GraphBellmanFordAlg* GraphBellmanFordAlgExecute(Graph* g, unsigned int startVertex) {
    // 1. Validate input
    int numVertices = GraphGetNumVertices(g);
    assert(g != NULL);
    assert(startVertex < numVertices);

    // 2. Allocate memory for the result structure
    GraphBellmanFordAlg* result = (GraphBellmanFordAlg*)malloc(sizeof(GraphBellmanFordAlg));
    assert(result != NULL);

    result->graph = g;
    result->startVertex = startVertex;

    // 3. Allocate arrays for marked, distance, and predecessor
    result->marked = (unsigned int*)malloc(sizeof(unsigned int) * numVertices);
    result->distance = (int*)malloc(sizeof(int) * numVertices);
    result->predecessor = (int*)malloc(sizeof(int) * numVertices);
    assert(result->marked != NULL && result->distance != NULL && result->predecessor != NULL);

    // 4. Initialize arrays
    for (int i = 0; i < numVertices; i++) {
        result->marked[i] = 0;         // Marked as unvisited
        result->distance[i] = INT_MAX; // Distance initially infinity
        result->predecessor[i] = -1;  // No predecessor
    }
    result->distance[startVertex] = 0; // Distance to itself is 0

    // 5. Bellman-Ford algorithm (Relax edges up to V-1 times)
    for (int i = 0; i < numVertices - 1; i++) {
        for (int u = 0; u < numVertices; u++) {
            // Get all adjacent vertices and edge weights of u
            unsigned int* adjacents = GraphGetAdjacentsTo(g, u);
            double* weights = GraphGetDistancesToAdjacents(g, u);

            if (adjacents == NULL || weights == NULL) continue; // Skip if no adjacents

            // Traverse adjacents array
            for (int v = 0; adjacents[v] != (unsigned int)-1; v++) {
                int neighbor = adjacents[v];
                double weight = weights[v];
                
                // Relax edge u -> neighbor
                if (result->distance[u] != INT_MAX && result->distance[u] + weight < result->distance[neighbor]) {
                    result->distance[neighbor] = result->distance[u] + weight;
                    result->predecessor[neighbor] = u;
                }
            }

            free(adjacents); // Free memory allocated for adjacents
            free(weights);   // Free memory allocated for weights
        }
    }

    // 6. Final Check for Negative-Weight Cycles (Optional for non-negative graphs)
    for (int u = 0; u < numVertices; u++) {
        unsigned int* adjacents = GraphGetAdjacentsTo(g, u);
        double* weights = GraphGetDistancesToAdjacents(g, u);

        if (adjacents == NULL || weights == NULL) continue;

        for (int v = 0; adjacents[v] != (unsigned int)-1; v++) {
            int neighbor = adjacents[v];
            double weight = weights[v];

            if (result->distance[u] != INT_MAX && result->distance[u] + weight < result->distance[neighbor]) {
                printf("Graph contains a negative-weight cycle\n");
                free(adjacents);
                free(weights);

                // Free result structure
                free(result->marked);
                free(result->distance);
                free(result->predecessor);
                free(result);
                return NULL;
            }
        }

        free(adjacents);
        free(weights);
    }

    // 7. Return the result structure
    return result;
}


void GraphBellmanFordAlgDestroy(GraphBellmanFordAlg** p) {
  assert(*p != NULL);

  GraphBellmanFordAlg* aux = *p;

  free(aux->marked);
  free(aux->predecessor);
  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the paths information

int GraphBellmanFordAlgReached(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

int GraphBellmanFordAlgDistance(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->distance[v];
}
Stack* GraphBellmanFordAlgPathTo(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0) {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current]) {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBellmanFordAlgShowPath(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = GraphBellmanFordAlgPathTo(p, v);

  while (StackIsEmpty(s) == 0) {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

// Display the Shortest-Paths Tree in DOT format
void GraphBellmanFordAlgDisplayDOT(const GraphBellmanFordAlg* p) {
  assert(p != NULL);

  Graph* original_graph = p->graph;
  unsigned int num_vertices = GraphGetNumVertices(original_graph);

  // The paths tree is a digraph, with no edge weights
  Graph* paths_tree = GraphCreate(num_vertices, 1, 0);

  // Use the predecessors array to add the tree edges
  for (unsigned int w = 0; w < num_vertices; w++) {
    // Vertex w has a predecessor vertex v?
    int v = p->predecessor[w];
    if (v != -1) {
      GraphAddEdge(paths_tree, (unsigned int)v, w);
    }
  }

  // Display the tree in the DOT format
  GraphDisplayDOT(paths_tree);

  // Housekeeping
  GraphDestroy(&paths_tree);
}
