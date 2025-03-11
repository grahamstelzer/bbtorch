# include <stdio.h>
# include <stdint.h> // for uint8_t

// memcpy written from computerphile video
//   via dr steve bagley
void memcpy(void *dest, void *src, size_t n) {

    uint8_t *p = (uint8_t *)dest; // cast
    uint8_t *q = (uint8_t *)src;
    size_t i = 0;

    while(i < n) {
        *p++ = *q++; // post incrementation: read val at q pointer, assign to val at p, increment
        i++;
    }
}

#include <stdint.h>

void asm_memcpy(uint8_t *dest, const uint8_t *src, uint32_t num) {
    __asm__ volatile ( // NOTE: volatile keyword in order to NOT auto-optimize instrux
        "MOV R2, #0       \n"   // counter = 0
        "B condition      \n"   // branch to cond
        "loop:            \n"
        "    LDRB R4, [R1]  \n" // load byte from src
        "    ADD R1, R1, #1 \n" // increment src pointer
        "    STRB R4, [R0]  \n" // store byte to dest
        "    ADD R0, R0, #1 \n" // inc dest pointer
        "    ADD R2, R2, #1 \n" // inc counter
        "condition:        \n"
        "    CMP R2, R3    \n" // compare counter with num
        "    BLT loop      \n" // branch less than if counter < num
        :
        : "r"(dest), "r"(src), "r"(num) // assignments (inputs)
        : "r0", "r1", "r2", "r3", "r4", "cc", "memory" // "clobber"
            //  "r0", "r1", "r2", "r3", "r4" → Tells the compiler that these registers will be modified.
            // "cc" → Informs the compiler that the condition codes (flags) will be altered.
            // "memory" → Informs the compiler that memory will be read and written, preventing optimizations that assume memory is unchanged.
    );
}



int main() {
    char src[] = "Hello, World!";
    char dest[20];

    memcpy(dest, src, sizeof(src));

    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);

    return 0;
}





// seperate generated asm from online assembler
    //__asm__(
    //     "section .text\n"
    //     "global memcpy\n"
    //     "\n"
    //     "memcpy:\n"
    //     "    ; Function parameters:\n"
    //     "    ; dest in rdi\n"
    //     "    ; src in rsi\n"
    //     "    ; n in rdx\n"
    //     "\n"
    //     "    ; Cast dest and src to uint8_t*\n"
    //     "    mov r8, rdi          ; p = (uint8_t *)dest\n"
    //     "    mov r9, rsi          ; q = (uint8_t *)src\n"
    //     "    xor rcx, rcx         ; i = 0\n"
    //     "\n"
    //     ".loop:\n"
    //     "    cmp rcx, rdx         ; compare i with n\n"
    //     "    jge .done            ; if i >= n, exit loop\n"
    //     "\n"
    //     "    mov al, [r9]         ; load byte from src (q) into al\n"
    //     "    mov [r8], al         ; store byte in dest (p)\n"
    //     "\n"
    //     "    inc r8               ; p++\n"
    //     "    inc r9               ; q++\n"
    //     "    inc rcx              ; i++\n"
    //     "    jmp .loop            ; repeat the loop\n"
    //     "\n"
    //     ".done:\n"
    //     "    ret\n"
    // );
