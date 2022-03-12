#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of float point number
    char buff;
    unsigned int binary = 0;
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB (Most Significant Bit) first as that is what comes first in the file
        fscanf(fp, "%c", &buff);
        binary *= 2;
        binary += buff == '1' ? 1 : 0;
    }

    // float number = *(float *)&binary; // you are not allowed to do this.
    // printf("Binary: %X\n", binary);

    // S
    bool positive = 1 & (binary >> (FRAC_SZ + EXP_SZ));
    // printf("Sign: %d\n", positive);

    // E
    signed short exponent = ~(1 << EXP_SZ) & (binary >> FRAC_SZ);
    if (exponent == 0) {
        printf("%e\n", 0.0);
        return EXIT_SUCCESS;
    }

    exponent -= 127;
    // printf("Exp: %X | %d\n", exponent, exponent);

    // M
    unsigned int mantissa = (binary << (1 + EXP_SZ)) >> (1 + EXP_SZ);
    // Add the leading 1 i.e. normalize the mantissa
    mantissa ^= 1 << FRAC_SZ;
    // printf("Mant: %d \n", mantissa);

    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp ( mantissa, exponent - FRAC_SZ);
    number = positive ? -number : number;
    printf("%e\n", number);

    return EXIT_SUCCESS;

}
