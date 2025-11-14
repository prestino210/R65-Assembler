#include "parse_6502.h"
#include "tokenize_asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint16_t offset;
    char* label;
} Label;

Label* labels = NULL;
int labelsc = 0;
uint16_t prgm_offset = 0x0600;

uint8_t* parse_6502(Token* tokens) {
    uint8_t prgm_bytes = NULL;


    return prgm_bytes;
}

// @todo: write method to convert addresses and int literals into ints