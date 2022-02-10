#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

struct element {
    char close;
    struct element* next;
};

struct element* push (
    struct element* stack,
    char close
) {
	struct element* next_elm = calloc(1, sizeof(struct element));
	next_elm->close = close;
	next_elm->next = stack;

	return next_elm;
}

// Remove element from the top of the stack
char pop ( struct element** stack ) {
    if (*stack != NULL) {
			char topChar = (*stack)->close;
			*stack = (*stack)->next;
			return topChar;
    } else {
        return '\0';
    }
}

int main(int argc, char* argv[]) {

		assert(argc == 2);

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    struct element* root = NULL;
    bool balanced = true;

    char buff;
		char expected_char;

    while ( balanced && fscanf(fp, "%c", &buff)==1 ) {

        switch(buff) {
						// Openers
            case '<' :
            case '(' :
            case '[' :
            case '{' :
                root = push(root, buff);
								break;

            case '>' :
            case ')' :
            case ']' :
            case '}' :
								expected_char = pop(&root);
								if (expected_char != buff)
									balanced = false;
								break;

            default :
                printf("Invalid character\n" );
        }
    }

		// Free all nodes
		while ( root != NULL ) {
			struct element* next_node = root->next;
			free(root);
			root = next_node;
		}

		printf("Hello");
    printf ( balanced ? "yes" : "no" );
		printf ("\n");
    fclose(fp);
    return 0;
}
