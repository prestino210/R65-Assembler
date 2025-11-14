#include "asm_loader.h" 
#include "parse_6502.h" 
#include "write_program.h" 
#include "tokenize_asm.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Please specify target .s file.\n");
        goto catch;
    }
    
    char* contents = get_contents(argv[1]);
    if(contents == NULL) {
        printf("Loader error.\n");
        goto catch;
    }
    Token* tokens = tokenize(contents);
    if(tokens == NULL) {
        printf("Analysis error.\n"); // un comment
        goto catch;
    }
    uint8_t* rom_bytes = parse_6502(tokens);
    if(rom_bytes == NULL) {
        printf("Assembler error.\n");
        goto catch;
    } 
    if(write_rom(rom_bytes) == FAILED_WRITE) {
        printf("ROM write error.\n");
        goto catch;
    }
    printf("Assembled target 6502 assembly to ROM.\n");
    
    return EXIT_SUCCESS;
    catch: return EXIT_FAILURE;
}