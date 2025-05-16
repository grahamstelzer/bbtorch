#include <stdio.h>
#include <stdint.h>
#include <limits.h> // for CHAR_BIT

// create bitfields for smaller precision floating points:

// bfloat16, bias=127, represent values up to 3.4x10^38
struct BF16 {
    uint16_t mantissa : 7;
    uint16_t exponent : 8;
    uint16_t sign : 1;
};

void matrix_multiply();
void show_ieee754_32bit(float);
void fp32_to_bf16(float);

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
    // printf("Size of float_32 union is %lu bytes\n", sizeof(float_union)); 
    
    int i = sizeof input_f * CHAR_BIT;

    printf ("  ");
    while (i--)
        // starting at 32nd bit (31 since 0 indexed) via shifting
        //  band that bit with 0001 (0x1) which only displays 1 if 
        //  if input is 1
        
        printf("%d ", (float_union.u >> i) & 0x1); // remove space next to %d for nonformatted bits

        // note: since calling float_union.u, this reads
        //  the value there as the uint32_t value NOT
        //  the float value

    printf("\n");
    // formatting to easily see s,e,m
    printf (" |s|      exp      |                  mantissa"
        "                   |\n\n");
}

void fp32_to_bf16(float input_f) {
    show_ieee754_32bit(input_f);
}


int main(int argc, char* argv[]) {

    long i;

    struct BF16 bf16_instance;
    struct BF16* bf16_ptr = &bf16_instance;
    
    printf("size of bf16: %lu (bytes)\n", sizeof(bf16_instance));
    printf("address of bf16: %p\n", (void*)bf16_ptr);

    printf("\n");


    float temp = 0.1875;
    float* temp_ptr = &temp;

    printf("size of tempfloat: %lu (bytes)\n", sizeof(temp));
    printf("address of temp: %p\n", (void*)temp_ptr);

    printf("\n");


    // set memory address of float temp to memory address of a long
    //  and take the value
    i = *(long*) &temp; 
    printf("bits of i: ");
    for (int bit = sizeof(i) * CHAR_BIT - 1; bit >= 0; bit--) {
        printf("%ld", (i >> bit) & 1);
    }
    printf("\n");






    return 0;
}