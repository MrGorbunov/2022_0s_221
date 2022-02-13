#include "../graphutils.h" // header for functions to load and free adjacencyList
#include "assert.h"

// A program to print the edge list of a graph given the adjacency matrix
int main ( int argc, char* argv[] ) {

    // FIRST, READ THE ADJACENCY MATRIX FILE
    AdjacencyListNode* adjacencyList = NULL;
	size_t graphNodeCount;

	/* One cmd argument for the file location */
	assert(argc == 2);
	graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);

    // NEXT, TRAVERSE THE ADJACENCY LIST AND PRINT EACH EDGE, REPRESENTED AS A PAIR OF NODES
    // Example of traversing the adjacency list is in the freeAdjList() function in graphutils.h
	for (size_t i=0; i<graphNodeCount; i++) {
		AdjacencyListNode startNode = adjacencyList[i];
		size_t startNum = startNode.graphNode;

		while (startNode.next != NULL) {
			startNode = *(startNode.next);
			printf("%ld %ld\n", startNum, startNode.graphNode);
		}
	}

    // NOW, BE SURE TO FREE THE ADJACENCY LIST
	freeAdjList(graphNodeCount, adjacencyList);

    return EXIT_SUCCESS;
}

