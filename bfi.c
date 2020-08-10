// @author Thad Shinno
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char*file2str(char*);
int isbf(char);
// <>+-[],.

int main(int argc, char*argv[]) {
    // Must have ./bfi {filename}
    if (arc != 2) {
        printf("Usage: ./bfi {filename}\n");
        return 1;
    }
    // get code
    char *code = file2str(argv[1]);
    // printf("%s", code);
    
    // init tape
    int tapeSize = 1;
    char *tape = (char*)malloc(sizeof(char)); // allocate memory
    memset(tape, 0, 1); // set it to 0

    // init pointer
    char *ptr = &tape[0];
    int cur = 0; // current block is index 0

    // input char
    char in;
    // stack to store while [ indexes
    int stackSize = 0;
    int* stack = (int*)malloc(sizeof(int));

    // execute code
    for (int i = 0; code[i] != '\0'; i++) {
        switch (code[i]) {
            case '>':
                ptr++; // move pointer to the right one
                cur++; // increase cur
                // increase size if need to
                if (cur >= tapeSize) {
                    tapeSize++;
                    tape = realloc(tape, tapeSize*sizeof(char));
                    memset(tape+cur, 0, 1); // set the new block to 0
                }
                break;
            case '<':
                ptr--; // move pointer to the left one
                cur--; // decrease cur
                break;
            case '+':
                (*ptr)++; // increase current block by one
                break;
            case '-':
                (*ptr)--; // decrease current block by one
                break;
            case '[':
                // add the index of the operater AFTER [ to the stack
                stackSize++;
                stack = realloc(stack, stackSize*sizeof(int));
                // memset(stack+stackSize-1, i+1, 1);
                stack[stackSize-1] = i;
                break;
            case ']':
                // if the current block is zero, pop the stack and move on
                if (*ptr == 0) {
                    stackSize--;
                    stack = realloc(stack, stackSize*(sizeof(int)));
                    break;
                }
                // otherwise, go back to the operater AFTER [
                else {
                    i = stack[stackSize-1];
                    break;
                }
                break;
            case '.':
                printf("%c", *ptr); // print current block
                break;
            case ',':
                // get a single char and put it into the current block
                printf("Enter a character: ");
                in = getchar();
                *ptr = in;
                break;
        }
    }
    free(tape);
}

char *file2str(char* filename) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        printf("File not found\n");
        exit(1);
    }
    // init out
    char c;
    int size = 0;
    char *out = (char*)malloc(sizeof(char));
    do {
        c = fgetc(fp);
        if (isbf(c)) {
            size++;
            out = realloc(out, size*(sizeof(char)));
            memset(out+size-1, c, 1);
        }
    } while (c != EOF);
    fclose(fp);
    return out;
}

int isbf(char c) {
    // + , - .
    if ('+' <= c && c <= '.') {
        return 1;
    }
    // < > [ ]
    else {
        return (c == '<' || c == '>' || c == '[' || c==']');
    }
}