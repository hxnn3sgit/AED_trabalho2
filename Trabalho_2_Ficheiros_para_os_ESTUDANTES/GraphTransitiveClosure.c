//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name : Hannes Seidl
// Student Number : 123643
// Student Name :
// Student Number :

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "SortedList.h" // included by myself
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

// Helper function for copying the graph:
void copy_graph(Graph *original, Graph *result) {
	
	for (unsigned int i = 0; i < GraphGetNumVertices(original); ++i) {
		unsigned int *adjacents = GraphGetAdjacentsTo(original, i);
		unsigned int numAdj = adjacents[0];
		for (unsigned int j = 1; j <= numAdj; ++j) {
			GraphAddEdge(result, i, adjacents[j]);
		}
		free(adjacents);
	}
}

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm

  // idea: 
  // - iterating through every vertice
  // - check with wich vertices every vertice is connected
  // - add a new edge from the current vertex to the other vertices
// new version:
Graph* GraphComputeTransitiveClosure(Graph* g) {
    assert(g != NULL);
    assert(GraphIsDigraph(g));
    assert(GraphIsWeighted(g) == 0);
	// COMPLETE THE CODE

    unsigned int numVertices = GraphGetNumVertices(g);

    // Create a new graph to represent the transitive closure
    Graph* tcGraph = GraphCreate(numVertices, 1, 0); // Directed, unweighted graph

    for (unsigned int i = 0; i < numVertices; i++) {
        // Run Bellman-Ford from each vertex
        GraphBellmanFordAlg* bfResult = GraphBellmanFordAlgExecute(g, i);

        // Add edges to the transitive closure graph for all reachable vertices
        for (unsigned int j = 0; j < numVertices; j++) {
            if (GraphBellmanFordAlgReached(bfResult, j) && i != j) {
                GraphAddEdge(tcGraph, i, j);

                InstrCount[1]++; // edge addition counter
            }
        }

        // Clean up Bellman-Ford results
        GraphBellmanFordAlgDestroy(&bfResult);
    }

    return tcGraph;
}

  // COMPLETE THE CODE

  // idea: 
  // - iterating through every vertice
  // - check with wich vertices every vertice is connected
  // - add a new edge from the current vertex to the other vertices
