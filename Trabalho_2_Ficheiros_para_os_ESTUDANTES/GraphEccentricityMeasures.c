// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures

// Student Name : Hannes Seidl
// Student Number : 123643
// Student Name : 
// Student Number : 

#include "GraphEccentricityMeasures.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"
#include <limits.h>

struct _GraphEccentricityMeasures {
  unsigned int* centralVertices;  // centralVertices[0] = number of central vertices
                                  // array size is (number of central vertices + 1)
  int* eccentricity;              // the eccentricity value of each vertex
  Graph* graph;                   // the graph
  int graphRadius;                // the graph radius
  int graphDiameter;              // the graph diameter
};

GraphEccentricityMeasures* GraphEccentricityMeasuresCompute(Graph* g) {
    assert(g != NULL);

    unsigned int numVertices = GraphGetNumVertices(g);
    GraphAllPairsShortestDistances* allPairs = GraphAllPairsShortestDistancesExecute(g);

    GraphEccentricityMeasures* measures = malloc(sizeof(GraphEccentricityMeasures));
    assert(measures != NULL);

    measures->graph = g;
    measures->eccentricity = malloc(sizeof(int) * numVertices);
    assert(measures->eccentricity != NULL);

    measures->graphRadius = INT_MAX;
    measures->graphDiameter = 0;

    // Compute eccentricities, radius, and diameter
    for (unsigned int i = 0; i < numVertices; ++i) {
        int maxDistance = 0;
        for (unsigned int j = 0; j < numVertices; ++j) {
            int distance = GraphGetDistanceVW(allPairs, i, j);
            if (distance > maxDistance) {
                maxDistance = distance;
            }
        }
        measures->eccentricity[i] = maxDistance;
        if (maxDistance < measures->graphRadius) {
            measures->graphRadius = maxDistance;
        }
        if (maxDistance > measures->graphDiameter) {
            measures->graphDiameter = maxDistance;
        }
    }

    // Compute central vertices
    unsigned int centralCount = 0;
    for (unsigned int i = 0; i < numVertices; ++i) {
        if (measures->eccentricity[i] == measures->graphRadius) {
            ++centralCount;
        }
    }

    measures->centralVertices = malloc(sizeof(unsigned int) * (centralCount + 1));
    assert(measures->centralVertices != NULL);

    measures->centralVertices[0] = centralCount;
    unsigned int index = 1;
    for (unsigned int i = 0; i < numVertices; ++i) {
        if (measures->eccentricity[i] == measures->graphRadius) {
            measures->centralVertices[index++] = i;
        }
    }

    GraphAllPairsShortestDistancesDestroy(&allPairs);
    return measures;
}

void GraphEccentricityMeasuresDestroy(GraphEccentricityMeasures** p) {
    assert(p != NULL && *p != NULL);

    GraphEccentricityMeasures* measures = *p;
    free(measures->eccentricity);
    free(measures->centralVertices);
    free(measures);

    *p = NULL;
}

int GraphGetRadius(const GraphEccentricityMeasures* p) {
    assert(p != NULL);
    return p->graphRadius;
}

int GraphGetDiameter(const GraphEccentricityMeasures* p) {
    assert(p != NULL);
    return p->graphDiameter;
}

int GraphGetVertexEccentricity(const GraphEccentricityMeasures* p, unsigned int v) {
    assert(p != NULL);
    assert(v < GraphGetNumVertices(p->graph));
    return p->eccentricity[v];
}

unsigned int* GraphGetCentralVertices(const GraphEccentricityMeasures* p) {
    assert(p != NULL);
    return p->centralVertices;
}

void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures* p) {
    assert(p != NULL);

    printf("Graph Radius: %d\n", p->graphRadius);
    printf("Graph Diameter: %d\n", p->graphDiameter);

    printf("Vertex Eccentricities:\n");
    for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); ++i) {
        printf("Vertex %u: %d\n", i, p->eccentricity[i]);
    }

    printf("Central Vertices: ");
    for (unsigned int i = 1; i <= p->centralVertices[0]; ++i) {
        printf("%u ", p->centralVertices[i]);
    }
    printf("\n");
}
