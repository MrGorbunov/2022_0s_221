#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    signed int input;
    fscanf(fp, "%d", &input);

    if (input == 0) {
        printf("0000");

    } else if (input >= 0) {
        // If it's non-negative, there are no leading FFFFs so we're good to just print
        printf("%X", input);

    } else {
        // Otherwise, we do the string format and skip 4 characters (the leading FFFFs)
        char* formatBuff = calloc(100, sizeof(char));
        sprintf(formatBuff, "%X", input);
        printf("%s", (formatBuff + 4));

        free(formatBuff);
    }

    return EXIT_SUCCESS;

}
