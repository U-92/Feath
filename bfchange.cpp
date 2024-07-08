#include <stdio.h>
#include <stdlib.h>

#define TAPE_SIZE 30000
#define MAX_CODE_SIZE 65536  // 최대 코드 크기

void brainfuck_interpreter(const char *code) {
    char tape[TAPE_SIZE] = {0}; // 메모리 테이프 초기화
    char *ptr = tape;           // 포인터 초기화
    const char *pc = code;      // 코드 포인터 초기화
    
    while (*pc) {
        switch (*pc) {
            case 76:
                ptr++;
                break;
            case 74:
                ptr--;
                break;
            case 53:
                (*ptr)++;
                break;
            case 55:
                (*ptr)--;
                break;
            case 56:
                putchar(*ptr);
                break;
            case 54:
                *ptr = getchar();
                break;
            case 133:
                if (*ptr == 0) {
                    int open_brackets = 1;
                    while (open_brackets != 0) {
                        pc++;
                        if (*pc == 133) open_brackets++;
                        if (*pc == 135) open_brackets--;
                    }
                }
                break;
            case 135:
                if (*ptr != 0) {
                    int close_brackets = 1;
                    while (close_brackets != 0) {
                        pc--;
                        if (*pc == 133) close_brackets--;
                        if (*pc == 135) close_brackets++;
                    }
                }
        }
    }
}
