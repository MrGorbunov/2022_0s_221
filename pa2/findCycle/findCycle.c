#include "../graphutils.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// A program to find a cycle in a directed graph


// QUEUE IMPLEMENTATION

/*
typedef struct Queue Queue;
struct Queue {
	Queue* nextNode;
	BSTNode* bstNode;
};

// Append a new QueueNode to the back of the Queue
void enqueue ( Queue* queue, BSTNode* data ) {
	// First traverse to the bottom of the tree
	Queue* prevQueue = queue;
	while (queue != NULL) {
		prevQueue = queue;
		queue = queue->nextNode;
	}

	Queue* nextQueueNode = calloc(1, sizeof(Queue));
	nextQueueNode->bstNode = data;
	prevQueue->nextNode = nextQueueNode;
}

// Frees the front node of the queue after
// pointing the passsed BSTNode** to the node's data
void dequeue (Queue** queue, BSTNode** data) {
	*data = (*queue)->bstNode;
	Queue* queueToFree = *queue;
	*queue = (*queue)->nextNode;
	free(queueToFree);
}

*/


// STACK IMPLEMENTATION

typedef struct Stack Stack;
struct Stack {
    AdjacencyListNode* node;
    struct Stack* next;
	size_t size;
};

// push an element onto the stack
void push (
    struct Stack** stack,
    AdjacencyListNode* node
) {
	struct Stack* next_elm = calloc(1, sizeof(Stack));
	next_elm->node = node;
	next_elm->next = *stack;
	if (*stack == NULL)
		next_elm->size = 1;
	else
		next_elm->size = (*stack)->size + 1;

	*stack = next_elm;
}

// Remove element from the top of the stack
void pop ( struct Stack** stack, AdjacencyListNode** node ) {
		if (*stack == NULL) {
			return;
		}

		AdjacencyListNode* graphNode = (*stack)->node;
		Stack* nextNode = (*stack)->next;

		free(*stack);
		*stack = nextNode;
		*node = graphNode;
}



// MAIN FUNCTION

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
	assert(argc == 2);
    AdjacencyListNode* adjacencyList;
	graphNode_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);

	// Run a DFS from every single node. If a node can reach itself via
	// a DFS, we have the cycle.
    bool isCyclic = false;
	bool* visited = calloc(graphNodeCount, sizeof(bool));
	Stack* searchStack = NULL;

	for (graphNode_t sourceInd=0; sourceInd < graphNodeCount && !isCyclic; sourceInd++) {
		memset(visited, 0, graphNodeCount * sizeof(bool));

		AdjacencyListNode* sourceNode = &(adjacencyList[sourceInd]);

		// Run DFS
		searchStack = NULL;
		AdjacencyListNode* searchNode = sourceNode;
		push(&searchStack, searchNode);

		while (searchStack != NULL && !isCyclic) {
			searchNode = searchStack->node;
			visited[searchNode->graphNode] = true;

			bool allNeighborsVisited = true;
			AdjacencyListNode* neighbor = searchNode;

			while (neighbor != NULL && !isCyclic) {
				graphNode_t neighborNumber = neighbor->graphNode;

				if (neighborNumber == sourceInd && searchStack->size > 1) {
					// We did a DFS from sourceInd -> sourceInd, i.e. we a loop
					// and it's currently on the stack
					isCyclic = true;
					break;

				} else if (!visited[neighborNumber]) {
					allNeighborsVisited = false;
					break;
				}

				neighbor = neighbor->next;
			}


			if (isCyclic) {
				break;
			}

			if (allNeighborsVisited) {
				// This means we go down one level in the stack
				AdjacencyListNode* dummyPtr = NULL;
				pop(&searchStack, &dummyPtr);
			} else {
				// This means we add the neighbor to the stack
				graphNode_t neighborNumber = neighbor->graphNode;
				push(&searchStack, &(adjacencyList[neighborNumber]));
			}
		}
	}


    if (!isCyclic) { 
		printf("DAG\n"); 
	} else {
		// We need to print in reverse order of the stack
		// so everything is written into an array
		size_t stackSize = searchStack->size;
		graphNode_t* cycleNodes = calloc(stackSize, sizeof(graphNode_t));
		AdjacencyListNode* node = NULL;

		for (size_t i=0; i<stackSize; i++) {
			pop(&searchStack, &node);
			cycleNodes[stackSize-1-i] = node->graphNode;
		}

		for (size_t i=0; i<stackSize; i++) {
			printf("%ld ", cycleNodes[i]);
		}
		printf("\n");

		free(cycleNodes);
	}

    freeAdjList ( graphNodeCount, adjacencyList );
	free(visited);
    return EXIT_SUCCESS;
}
