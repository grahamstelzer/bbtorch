#include <stdio.h>
#include <stdint.h>
#include <limits.h> // for CHAR_BIT

void matrix_multiply();
void show_ieee754_32bit(float);

void matrix_multiply() {

}



// take in float value, print out bits using type-punning
//  via: https://stackoverflow.com/questions/44609743/obtaining-bit-representation-of-a-float-in-c
void show_ieee754_32bit(float input_f) {

    // declare/instantiate union
    union {
        float f;
        uint32_t u;
    } float_union = { .f = input_f }; // sets fu.f to input_f

    // check size
    //  %lu for checking long unsigned
    printf("Size of float_32 union is %lu bytes\n", sizeof(float_union)); 
    
    int i = sizeof input_f * CHAR_BIT;

    printf ("  ");
    while (i--)
        // starting at 32nd bit (31 since 0 indexed) via shifting
        //  band that bit with 0001 (0x1) which only displays 1 if 
        //  if input is 1
        
        printf ("%d ", (float_union.u >> i) & 0x1); // remove next to %d for nonformatted bits

        // note: since calling float_union.u, this reads
        //  the value there as the uint32_t value NOT
        //  the float value
    printf("\n");
    printf (" |s|      exp      |                  mantissa"
        "                   |\n\n");
 
}

int main(int argc, char* argv[]) {
    float temp = 3.2;
    show_ieee754_32bit(3.2);

    return 0;
}