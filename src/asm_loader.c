#include "asm_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#define SIGNATURE_6502 "__6502__"

bool check_sig(char* str_buf) {
    return strcmp(str_buf, SIGNATURE_6502) == 0;
}

char* get_contents(char* asm6502_path) {
    
    char* contents_buf = NULL;
    size_t buf_size = 0;
    int buf_chars = 0;

    FILE* file = fopen(asm6502_path, "r");
    if(file == NULL) {
        printf("Could not open target file.\n");
        goto _return;
    }
    
    char* line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_chars = 0;
    int lines = -1;
    
    while ((line_chars = getline(&line_buf, &line_buf_size, file)) != -1) {
        lines++;
        if(line_buf[line_chars - 1] == '\n') {
            line_buf[line_chars - 1] = (lines > 0) ? ' ' : '\0';
        } else {
            if(lines == 0) goto check_sig;
            line_chars++;
            line_buf_size = line_chars * sizeof(char);
            line_buf = realloc(line_buf, line_buf_size);
            line_buf[line_chars - 1] = ' ';
        }
        check_sig:
        if(lines == 0 && !check_sig(line_buf)) {
            break;
        }
        buf_chars += line_chars;
        buf_size = buf_chars * sizeof(char);
        contents_buf = realloc(contents_buf, buf_size);
        for(int i = 0; i < line_chars; i++) {
            contents_buf[buf_chars - line_chars + i] = line_buf[i];
        }
    }

    switch(lines) {
        case -1:
            printf("No content in file.\n");
            break;
        case 0:
            printf("Could not identify 6502 assembly.\n");
            break;
        case 1:
            printf("No code to assemble.\n");
            break;
        default:
            buf_chars++;
            buf_size = buf_chars * sizeof(char);
            contents_buf = realloc(contents_buf, buf_size);
            contents_buf[buf_chars - 1] = '\0';
            break;
    }
   
    free(line_buf);
    fclose(file);
    _return:
    return contents_buf;
}
