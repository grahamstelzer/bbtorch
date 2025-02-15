#include <stdio.h>

// gcc test.c -o test && ./test

void print_binary(long num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) { // sizeof gets number of bytes, then mult by 8 to get number of bits
        // since iterating down (i--), take current MSB in num, shift all the way to
        //  LSB, binand with 1 to see if its 1 or 0
        printf("%ld", (num >> i) & 1); 
    }
    printf("\n");
}

void print_ieee754(float num) {
    // union to store different datatypes in the same memory location
    //  NOTE: literally the same starting address 
    //  - allows interpretation of items as different types
    //  - size is its largest member type, so below wll be allocate 8 bytes
    //    - char c;      // 1 byte
    //    - int i;       // 4 bytes (and floats)
    //    - double d;    // 8 bytes (and longs)
    union {
        float f;
        unsigned int u; // 4 bytes to match the float
        // long u; // 8 bytes, unexpected results, 
    } ieee;

    ieee.f = num; // set num to a float (ieee)...

    for (int i = sizeof(ieee.u) * 8 - 1; i >= 0; i--) {
        printf("%u", (ieee.u >> i) & 1); //...but interpret as unsigned int (binary string)
    }
    printf("\n");
}


void pretty_print(long lnum, float fnum) {
    printf("long: %ld, float: %f\n", lnum, fnum);
    printf("Binary of long: ");
    print_binary(lnum);
    printf("ieee of float: ");
    print_ieee754(fnum);
}


int main() {

    long l = 1234;
    float f = -8.125;

    pretty_print(l, f);


    l = l >> 1; // should act as division
    // f = f >> 1; // doesnst work since float stored as ieee 754

    printf("\nright shift long (division) ");
    pretty_print(l, f);

    float *f_ptr = &f; // pointer to the address of f
    printf("\nThe address of f is:            %p\n", (void *)&f); // cast ensures no type errors or information loss
    printf("The address stored in f_ptr is: %p\n", (void *)f_ptr);
    // above two printf should be the same

    long long_f = * (long *) &f; // interpret the bits of float f as a long integer
    // &f takes address of the variable f (float) which gives a pointer (float *) to f
    // (long *) casts the pointer to f (float *) to a long pointer (long *)
    // * dereference the pointer (long *) to access the value at that address, 
    //   BUT not it is interpreted as a long integer instead of flaot
    printf("\nvalue at f interpreted as a long:  %p\n", (void *)long_f);
    print_binary(long_f);
    print_ieee754(f);



    return 0;
}