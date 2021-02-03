// @author Thad Shinno
// a really good ide https://minond.xyz/brainfuck/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char*file2str(char*);
int isbf(char);
// <>+-[],.
// Brainfuck interpreter
int main(int argc, char*argv[]) {
    // Must have ./bfi {filename}
    if (argc != 2) {
        printf("Usage: ./bfi {filename}\n");
        return 1;
    }
    // get code
    char *code = file2str(argv[1]);
    
    // init tape as basically an array of unsigned chars
    int tapeSize = 1;
    unsigned char *tape = (unsigned char*)malloc(sizeof(unsigned char)); // allocate memory
    memset(tape, 0, sizeof(unsigned char)); // set it to 0

    // init pointer
    unsigned char *ptr = &tape[0]; // pointer starts
    int cur = 0; // current block is index 0

    // input char
    char in;
    // stack to store while [ indexes
    int stackSize = 0;
    int* stack = (int*)malloc(sizeof(int));
    // skipper to find end of [] loop
    int skipper = 0;

    // execute code
    for (int i = 0; code[i] != '\0'; i++) {
        switch (code[i]) {
            case '>':
                ptr++; // move pointer to the right one
                cur++; // increase cur
                // increase size if need to
                if (cur >= tapeSize) {
                    tapeSize++; // increase size
                    tape = realloc(tape, tapeSize*sizeof(char)); // allocate memory to new size
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
                // enter loop if current pointer is not zero
                if (*ptr != 0) {
                    // add the index of the operater AFTER [ to the stack
                    stackSize++;
                    stack = realloc(stack, stackSize*sizeof(int));
                    // memset(stack+stackSize-1, i+1, 1);
                    stack[stackSize-1] = i;
                }
                // otherwise skip the loop
                else {
                    skipper = 1;
                    do {
                        i++;
                        if (code[i] == '[') {
                            skipper++;
                        }
                        else if (code[i] == ']') {
                            skipper--;
                        }
                    } while (skipper != 0);
                }
                break;
            case ']':
                // if the current block is zero, pop the stack and move on
                if (*ptr == 0) {
                    stackSize--; // decrease size
                    stack = realloc(stack, stackSize*(sizeof(int))); // reallocate memory to smaller size
                    break;
                }
                // otherwise, go back to the operater AFTER [
                else {
                    i = stack[stackSize-1]; // set i to the top number in stack
                    break;
                }
                break;
            case '.':
                printf("%c", *ptr); // print current block
                break;
            case ',':
                // get a single char and put it into the current block
                // do NOT get the \n char
                do {
                    in = getchar();
                } while (getchar() != '\n');
                *ptr = in;
                break;
        }
    }
    free(code);
    free(tape);
    free(stack);
}

// filter out non bf operators
char *file2str(char* filename) {
    // open file
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
    // loop through file
    do {
        // if the character is a bf operator, then add it to out
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

// check if a character is a brainfuck character
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
