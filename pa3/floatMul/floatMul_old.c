#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23


float readFloat (FILE* fp) {
    // The following is taking from binToFloat

    // first, read the binary number representation of float point number
    char buff;
    unsigned int binary = 0;
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB (Most Significant Bit) first as that is what comes first in the file
        fscanf(fp, "%c", &buff);
        binary *= 2;
        binary += buff == '1' ? 1 : 0;
    }

    // S
    bool sign = 1 & (binary >> (FRAC_SZ + EXP_SZ));

    // E
    signed short exponent = ~(1 << EXP_SZ) & (binary >> FRAC_SZ);
    if (exponent == 0)
        return 0.0f;
    exponent -= 127;

    // M
    unsigned int mantissa = (binary << (1 + EXP_SZ)) >> (1 + EXP_SZ);

    // Add the leading 1 i.e. normalize the mantissa
    mantissa ^= 1 << FRAC_SZ;
    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp ( mantissa, exponent - FRAC_SZ);
    number = sign ? -number : number;

    return (float) number;
}


int main(int argc, char *argv[]) {

    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // READING INPUT
    float num1 = readFloat(fp);
    fscanf(fp, "\n");
    float num2 = readFloat(fp);

    float result = num1 * num2;

    // float product = *(float *) &multiplier * *(float *) &multiplicand; // you are not allowed to print from this.
    // unsigned int ref_bits = *(unsigned int *) &product; // you are not allowed to print from this. But you can use it to validate your solution.

    unsigned int sign = result <= -0.0f ? 1 : 0;


    // SIGN
    printf("%d_",sign);
    assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ)));

    // PRINTING
    // print exp
    for ( int bit_index=EXP_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&exp>>bit_index;
        printf("%d",trial_bit);
        assert (trial_bit == (1&ref_bits>>(bit_index+FRAC_SZ)));
    }
    printf("_");

    // print frac
    for ( int bit_index=FRAC_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&frac>>bit_index;
        printf("%d",trial_bit);
        assert (trial_bit == (1&ref_bits>>(bit_index)));
    }

    return(EXIT_SUCCESS);

}
