//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphAllPairsShortestDistances
//

// Student Name : Hannes Seidl
// Student Number : 123643
// Student Name :
// Student Number :

/*** COMPLETE THE GraphAllPairsShortestDistancesExecute FUNCTION ***/

#include "GraphAllPairsShortestDistances.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "SortedList.h"

struct _GraphAllPairsShortestDistances {
  int** distance;  // The 2D matrix storing the all-pairs shortest distances
                   // It is stored as an array of pointers to 1D rows
                   // Idea: an INDEFINITE distance value is stored as -1
  Graph* graph;
};

// Allocate memory and initialize the distance matrix
// Compute the distances between vertices by running the Bellman-Ford algorithm

GraphAllPairsShortestDistances* GraphAllPairsShortestDistancesExecute(Graph* g) {
    assert(g != NULL);

    GraphAllPairsShortestDistances* shortest_distances = malloc(sizeof(GraphAllPairsShortestDistances));
    assert(shortest_distances != NULL);

    unsigned int numVertices = GraphGetNumVertices(g);

    // Allocate memory for the distance matrix
    shortest_distances->distance = malloc(sizeof(int*) * numVertices);
    assert(shortest_distances->distance != NULL);

    for (unsigned int i = 0; i < numVertices; ++i) {
        shortest_distances->distance[i] = malloc(sizeof(int) * numVertices);
        if (shortest_distances->distance[i] == NULL) {
            // Cleanup on failure
            for (unsigned int k = 0; k < i; ++k) free(shortest_distances->distance[k]);
            free(shortest_distances->distance);
            free(shortest_distances);
            perror("Memory allocation failed for distance matrix");
            exit(EXIT_FAILURE);
        }
    }

    // Compute shortest distances using Bellman-Ford
    for (unsigned int i = 0; i < numVertices; ++i) {
        GraphBellmanFordAlg* bellman_ford = GraphBellmanFordAlgExecute(g, i);
        assert(bellman_ford != NULL);

        for (unsigned int j = 0; j < numVertices; ++j) {
            if (i == j) {
                shortest_distances->distance[i][j] = 0; // Distance to self
            } else if (GraphBellmanFordAlgReached(bellman_ford, j)) {
                shortest_distances->distance[i][j] = GraphBellmanFordAlgDistance(bellman_ford, j);
            } else {
                shortest_distances->distance[i][j] = -1; // Indefinite
            }
        }

        GraphBellmanFordAlgDestroy(&bellman_ford); // Pass as double-pointer
    }

    shortest_distances->graph = g;
    return shortest_distances;
}

void GraphAllPairsShortestDistancesDestroy(GraphAllPairsShortestDistances** p) {
  assert(*p != NULL);

  GraphAllPairsShortestDistances* aux = *p;
  unsigned int numVertices = GraphGetNumVertices(aux->graph);

  for (unsigned int i = 0; i < numVertices; i++) {
    free(aux->distance[i]);
  }

  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the result

int GraphGetDistanceVW(const GraphAllPairsShortestDistances* p, unsigned int v,
                       unsigned int w) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(w < GraphGetNumVertices(p->graph));

  return p->distance[v][w];
}

// DISPLAYING on the console

void GraphAllPairsShortestDistancesPrint(
    const GraphAllPairsShortestDistances* p) {
  assert(p != NULL);

  unsigned int numVertices = GraphGetNumVertices(p->graph);
  printf("Graph distance matrix - %u vertices\n", numVertices);

  for (unsigned int i = 0; i < numVertices; i++) {
    for (unsigned int j = 0; j < numVertices; j++) {
      int distanceIJ = p->distance[i][j];
      if (distanceIJ == -1) {
        // INFINITY - j was not reached from i
        printf(" INF");
      } else {
        printf(" %3d", distanceIJ);
      }
    }
    printf("\n");
  }
}
