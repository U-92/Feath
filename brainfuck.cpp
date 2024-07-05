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
            case '>':
                ptr++;
                break;
            case '<':
                ptr--;
                break;
            case '+':
                (*ptr)++;
                break;
            case '-':
                (*ptr)--;
                break;
            case '.':
                putchar(*ptr);
                break;
            case ',':
                *ptr = getchar();
                break;
            case '[':
                if (*ptr == 0) {
                    int open_brackets = 1;
                    while (open_brackets != 0) {
                        pc++;
                        if (*pc == '[') open_brackets++;
                        if (*pc == ']') open_brackets--;
                    }
                }
                break;
            case ']':
                if (*ptr != 0) {
                    int close_brackets = 1;
                    while (close_brackets != 0) {
                        pc--;
                        if (*pc == '[') close_brackets--;
                        if (*pc == ']') close_brackets++;
                    }
                }
                break;
        }
        pc++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename.bf>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        return 1;
    }

    char *code = (char *)malloc(MAX_CODE_SIZE);
    if (!code) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    size_t code_size = fread(code, 1, MAX_CODE_SIZE, file);
    if (code_size == 0 && ferror(file)) {
        perror("Could not read file");
        free(code);
        fclose(file);
        return 1;
    }

    code[code_size] = '\0';  // 문자열 종료 문자 추가

    fclose(file);

    brainfuck_interpreter(code);

    free(code);
    return 0;
}
