#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// <>+-[],.
int main(void) {
    char *code = ">+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+++++++..+++.[-]>++++++++[<++++>-] <.>+++++++++++[<++++++++>-]<-.--------.+++.------.--------.[-]>++++++++[<++++>- ]<+.[-]++++++++++.";
    // init tape
    int size = 0; // size of tape is 0
    char *tape = (char*)malloc(sizeof(char)); // allocate memory
    memset(tape, 0, 1); // set it to 0

    // init pointer
    char *ptr = &tape[0];
    int cur = 0; // current block is index 0

    for (char c = 0; code[c] != '\0'; c++) {
        switch (code[c]) {
            case '>':
                ptr++; // move pointer to the right one
                cur++; // increase cur
                // increase size if need to
                if (cur >= size) {
                    size++;
                    tape = realloc(tape, size*sizeof(char));
                    memset(tape+cur, 0, 1); // set the new one to 0
                }
                break;
            case '<':
                ptr--;
                cur--;
                break;
            case '+':
                (*ptr)++;
                break;
            case '-':
                (*ptr)--;
                break;
        }
    }
    free(tape);
}