# Brainfuck interpreter
---
Brainfuck is an esoteric programming language with 8 operators: ```<>+-[],.```

This interpreter even supports nested while loops.

- "<" moves the memory pointer one block to the left
- ">" moves the memory pointer one block the the right
- "+" Increments the value of what the pointer points to.
- "-" Decrements the value of what the pointer points to.
- "[" Opens a while loop.
- "]" If the value currently pointed to is zero, jump back to "[", otherwise exit the while loop.
- "," Accept 1 character of user input.
- "." Print the Ascii character of the value currently pointed to.