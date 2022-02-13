#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// A program to perform a LEVEL ORDER (BREADTH-FIRST) TRAVERSAL of a binary search tree

// BINARY SEARCH TREE

typedef struct BSTNode BSTNode;
struct BSTNode {
    int key;
    struct BSTNode* l_child; // nodes with smaller key will be in left subtree
    struct BSTNode* r_child; // nodes with larger key will be in right subtree
};

// Add new data to the BST using recursion
void add_to_bst (struct BSTNode* root, int value) {
	assert(root != NULL);
	struct BSTNode** child_to_travel_to;

	if (value == root->key) {
		return;
	} else if (value < root->key) {
		child_to_travel_to = &(root->l_child);
	} else {
		child_to_travel_to = &(root->r_child);
	}

	if (!*child_to_travel_to) {
		*child_to_travel_to = calloc(1, sizeof(BSTNode));
		(*child_to_travel_to)->key = value;
	} else {
		add_to_bst(*child_to_travel_to, value);
	}
}

// Delete the BST using recursion
void free_bst (struct BSTNode* root) {
	if (root == NULL)
		return;

	free_bst(root->l_child);
	free_bst(root->r_child);
	free(root);
}


// LINKED LIST IMPLEMENTATION OF QUEUE

// queue needed for level order traversal
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

void testQueue();
void testBST();


int main ( int argc, char* argv[] ) {

	//
	// Step 1 : Construct tree
	//

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

	// calloc is used to clear the data
	// malloc will break this
	BSTNode* root = calloc(1, sizeof(BSTNode)); 
	fscanf(fp, "%d", &(root->key));
    int key;
    while ( fscanf(fp, "%d", &key)!=EOF ) {
		add_to_bst(root, key);
    }
    fclose(fp);


	//
	// Step 2 : Populate Queue
	//

	Queue* levelOrderQueue = calloc(1, sizeof(Queue));
	levelOrderQueue->bstNode = root;

	while (levelOrderQueue != NULL) {
		BSTNode* nextVal = levelOrderQueue->bstNode;
		if (nextVal != NULL) {
			enqueue(levelOrderQueue, nextVal->l_child);
			enqueue(levelOrderQueue, nextVal->r_child);
			printf("%d ", nextVal->key);
		}

		Queue* prevQueueNode = levelOrderQueue;
		levelOrderQueue = levelOrderQueue->nextNode;
		free(prevQueueNode);
	}

	printf("\n");

    free_bst(root);
    return EXIT_SUCCESS;
}






void testQueue () {
	printf(" == Testing Queue ==\n\n");

	BSTNode* root = calloc(1, sizeof(BSTNode));
	root->key = 10;
	add_to_bst(root, 9);
	add_to_bst(root, 8);
	add_to_bst(root, 7);
	add_to_bst(root, 6);

	Queue* myQ = calloc(1, sizeof(Queue));
	myQ->bstNode = root;

	enqueue(myQ, root->l_child);
	enqueue(myQ, root->l_child->l_child);
	enqueue(myQ, root->l_child);
	enqueue(myQ, root->l_child->l_child);
	enqueue(myQ, root->l_child);
	enqueue(myQ, root->l_child->l_child);

	while (myQ != NULL) {
		BSTNode* data;
		dequeue(&myQ, &data);
		printf("Pulled data: %d\n", data->key);
	}

	free_bst(root);
}


void testBST () {
	BSTNode* root = NULL;
	root = calloc(1, sizeof(BSTNode));
	root->key = 10;

	printf("\n\nAdding 9\n");
	add_to_bst(root, 9);

	printf("\n\nAdding 8\n");
	add_to_bst(root, 8);

	printf("\n\nAdding 8 again\n");
	add_to_bst(root, 8);

	printf("Root Val: %d\n", root->key);
	printf("root.l  : %d\n", root->l_child->key);
	printf("root.l.l: %d\n", root->l_child->l_child->key);

	free_bst(root);
}



