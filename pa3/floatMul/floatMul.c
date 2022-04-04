#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23


void readFloat (FILE* fp, bool* s, unsigned int* m, signed short* e, float* num) {
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
    if (exponent == 0) {
        *s = 0;
        *m = 0;
        *e = 0;
        *num = 0.0f;
        return;
    }
    exponent -= 127;

    // M
    unsigned int mantissa = (binary << (1 + EXP_SZ)) >> (1 + EXP_SZ);

    // Add the leading 1 i.e. normalize the mantissa
    mantissa ^= 1 << FRAC_SZ;
    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp ( mantissa, exponent - FRAC_SZ);
    number = sign ? -number : number;

    // Returns
    *s = sign;
    *m = mantissa;
    *e = exponent;
    *num = (float) number;
}



int main(int argc, char *argv[]) {

    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE* fp = fopen(argv[1], "r");
    // FILE* fp = fopen("/home/velcro/Documents/Undergrad/CS/CompArch-211/2022_0s_221/pa3/floatMul/tests/test0.txt", "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP
    bool s1, s2;
    unsigned int m1, m2;
    signed short e1, e2;
    float num1, num2;

    // first, read the binary number representation of multiplier
    readFloat(fp, &s1, &m1, &e1, &num1);

    // notice that you are reading two different lines; caution with reading
    fscanf(fp, "\n");

    // first, read the binary number representation of multiplcand
    readFloat(fp, &s2, &m2, &e2, &num2);

    float product = num1 * num2; // you are not allowed to print from this.
    unsigned int ref_bits = *(unsigned int *) &product; // you are not allowed to print from this. But you can use it to validate your solution.

    if (product == 0) {
        printf("0_00000000_00000000000000000000000");
        return EXIT_SUCCESS;
    }

    // SIGN
    bool sign = s1 ^ s2;
    printf("%d_",sign);
    assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ)));

    // EXP
    // add the two exp together
    signed int exp = (int) e1 + e2;
    exp += 127;

    // FRAC
    // multiply the mantissas
    unsigned long frac = ((long) m1 * m2) >> FRAC_SZ;

    // if (frac & (frac - 1) == 0) {
    //     // it's a power of 2
    // }

    // overflow
    unsigned int exp_correct = 0;

    while (frac >> FRAC_SZ > 0) {
        frac = frac >> 1;
        exp_correct++;
    }
    exp += exp_correct;

    // unsigned int exp_correct = 0;
    // while (!(1 & (frac >> FRAC_SZ))) {
    //     frac = frac << 1;
    //     exp_correct++;
    // }

    // exp -= exp_correct;

    // PRINTING
    // print exp
    for ( int bit_index=EXP_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&exp>>bit_index;
        printf("%d",trial_bit);
        // assert (trial_bit == (1&ref_bits>>(bit_index+FRAC_SZ)));
    }
    printf("_");

    // print frac
    for ( int bit_index=FRAC_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&frac>>bit_index;
        printf("%d",trial_bit);
        // assert (trial_bit == (1&ref_bits>>(bit_index)));
    }

    return(EXIT_SUCCESS);

}
