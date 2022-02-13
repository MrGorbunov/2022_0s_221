#include <stdlib.h>
#include <stdio.h>

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

	if (*child_to_travel_to == NULL) {
		*child_to_travel_to = malloc(sizeof(struct BSTNODE));	
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
/* ... */

// Append a new QueueNode to the back of the Queue
void enqueue ( Queue* queue, BSTNode* data ) {
  /* ... */
}


int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE BINARY SEARCH TREE
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    BSTNode* root = NULL;
    int key;
    while ( fscanf(fp, "%d", &key)!=EOF ) {
        root = insert (root, key);
    }
    fclose(fp);

    // USE A QUEUE TO PERFORM LEVEL ORDER TRAVERSAL
    Queue queue = { .front=NULL, .back=NULL };
    BSTNode* currBSTNode = root;
    do {
        /* ... */
    } while ( currBSTNode!=NULL );

    delete_bst(root);
    return EXIT_SUCCESS;
}
