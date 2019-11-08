#include <cstdio>

char ok(char code)
{
    if (code == SUCCESS)
        return 1;

    decrypt(code);
    return 0;
}

void decrypt(char code)
{
    switch (code) {
        case ST_FULL: {
            fprintf(stderr, "Error 201: unable to push stack is full.\n");
            break;
        }
        case ST_EMPTY: {
            fprintf(stderr, "Error 203: nothing to pop: stack is empty.\n");
            break;
        }
        case ST_NULLPTR: {
            fprintf(stderr, "Error 204: invalid memory address.\n");
            break;
        }
        case ST_CORRUPTION: {
            fprintf(stderr, "Error 205: stack data has been corrupted.\n");
            break;
        }
        default: {
            fprintf(stderr, "Unknown error\n");
        }
    }
}