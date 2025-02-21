#include <stdio.h>
#include <ctype.h>

int main() {
    char expr[100];
    char symbol[10];
    int symbolCount = 0;
    int symbolIndex = 0;
    char ch;
    char symbolTable[20][10];
    char symbolType[20];

    printf("Enter an expression: ");
    fgets(expr, sizeof(expr), stdin);

    for (int i = 0; expr[i] != '\0'; i++) {
        ch = expr[i];

        if (isalnum(ch)) {
            symbol[symbolIndex++] = ch;
        }
        else if (symbolIndex > 0) {
            symbol[symbolIndex] = '\0';
            for (int j = 0; j < symbolIndex; j++) {
                symbolTable[symbolCount][j] = symbol[j];
            }
            symbolType[symbolCount] = 'I';
            symbolCount++;
            symbolIndex = 0;
        }

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (symbolIndex > 0) {
                symbol[symbolIndex] = '\0';
                for (int j = 0; j < symbolIndex; j++) {
                    symbolTable[symbolCount][j] = symbol[j];
                }
                symbolType[symbolCount] = 'I';
                symbolCount++;
                symbolIndex = 0;
            }
            symbol[0] = ch;
            symbol[1] = '\0';
            for (int j = 0; j < 2; j++) {
                symbolTable[symbolCount][j] = symbol[j];
            }
            symbolType[symbolCount] = 'O';
            symbolCount++;
        }
    }

    if (symbolIndex > 0) {
        symbol[symbolIndex] = '\0';
        for (int j = 0; j < symbolIndex; j++) {
            symbolTable[symbolCount][j] = symbol[j];
        }
        symbolType[symbolCount] = 'I';
        symbolCount++;
    }

    printf("\nSymbol Table with Memory Addresses:\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("Symbol: %s\tType: %c\tAddress: %p\n", symbolTable[i], symbolType[i], (void*)&symbolTable[i]);
    }

    return 0;
}


