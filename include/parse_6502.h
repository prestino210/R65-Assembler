#ifndef PARSE_ASM_H
#define PARSE_ASM_H
#include <stdint.h>
#include "tokenize_asm.h"

uint8_t* parse_6502(Statement* statements);

#endif
