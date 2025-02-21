#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

int is_keyword(char *str) {
    const char *keywords[] = {
        "int", "float", "char", "double", "if", "else", "while", "for",
        "return", "switch", "case", "break", "continue", "void", "printf"
    };
    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void classify(char *str) {
    if (is_keyword(str)) {
        printf("%s is a keyword\n", str);
    } else if (isdigit(str[0])) {
        printf("%s is a constant\n", str);
    } else {
        printf("%s is an identifier\n", str);
    }
}

void analyze(FILE *source) {
    char c, str[MAX_LEN];
    int i = 0;

    while ((c = fgetc(source)) != EOF) {
        if (isspace(c)) {
            continue;
        }

        if (isalpha(c) || c == '_') {
            str[i++] = c;
            c = fgetc(source);
            while (isalnum(c) || c == '_') {
                str[i++] = c;
                c = fgetc(source);
            }
            str[i] = '\0';
            ungetc(c, source);
            classify(str);
            i = 0;
        } else if (isdigit(c)) {
            str[i++] = c;
            c = fgetc(source);
            while (isdigit(c)) {
                str[i++] = c;
                c = fgetc(source);
            }
            str[i] = '\0';
            ungetc(c, source);
            printf("%s is a constant\n", str);
            i = 0;
        } else if (c == '/') {
            c = fgetc(source);
            if (c == '/') {
                while (c != '\n' && c != EOF) {
                    c = fgetc(source);
                }
                printf("Single-line comment detected\n");
            } else if (c == '*') {
                c = fgetc(source);
                while (c != '*' && c != EOF) {
                    c = fgetc(source);
                }
                if (c == '*') {
                    c = fgetc(source);
                    if (c == '/') {
                        printf("Multi-line comment detected\n");
                    }
                }
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' || c == '%' || c == ';' || c == ',' || c == '(' || c == ')') {
            printf("Operator/Special character: %c\n", c);
        } else {
            printf("Unknown character: %c\n", c);
        }
    }
}

int main() {
    FILE *source = fopen("inputlexicalanalyzer.c" ,"r");
    if (source == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    printf("Lexical Analysis:\n");
    analyze(source);
    fclose(source);
    return 0;
}
