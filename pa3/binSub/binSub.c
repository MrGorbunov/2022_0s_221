#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    // FILE* fp = fopen("/home/velcro/Documents/Undergrad/CS/CompArch-211/2022_0s_221/pa3/binSub/tests/test2.txt", "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the minuend (number to be subtracted from)
    char buff;
    bool minuend[8]; // suggested that you store bits as array of bools; minuend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
        fscanf(fp, "%c", &buff);
        minuend[i] = buff == '1' ? true : false;
    }

    // Go to next line in reading
    fscanf(fp, "\n");

    // notice that you are reading two different lines; caution with reading
    // second, read the subtrahend (number to subtract)
    bool subtrahend[8]; // suggested that you store bits as array of bools; subtrahend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
        fscanf(fp, "%c", &buff);
        subtrahend[i] = buff == '1' ? true : false;
    }

    // WE WILL DO SUBTRACTION BY NEGATING THE SUBTRAHEND AND ADD THAT TO THE MINUEND

    // Negate the subtrahend
    for (int i=0; i<=7; i++) {
        subtrahend[i] = !subtrahend[i];
    }

    // add one
    bool carry = true; // to implement the 'add one' logic, we do binary addition logic with carry set to true at the beginning
    for (int i=0; i<8 && carry; i++) { // iterate from LSB to MSB
        bool nextCarry = subtrahend[i] && carry;
        subtrahend[i] = (subtrahend[i] && !carry) || (!subtrahend[i] && carry);
        carry = nextCarry;
    }

    // Add the minuend and the negated subtrahend
    bool difference[8];
    carry = false;
    for (int i=0; i<8; i++) {
        bool b1 = carry;
        bool b2 = subtrahend[i];
        bool b3 = minuend[i];

        // At least two must be true
        carry = (b1 && b2) || (b1 && b3) || (b2 && b3);
        // One or three need to be true
        difference[i] = (b1 && b2 && b3) || (b1 && !b2 && !b3) || (!b1 && b2 && !b3) || (!b1 && !b2 && b3);
    }

    // print the difference bit string
    for (int i=7; 0<=i; i--)
        printf("%d",difference[i]);


    return EXIT_SUCCESS;

}
