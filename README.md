# Brainfuck interpreter
---
Brainfuck is an esoteric programming language with 8 operators: ```<>+-[],.```

- "<" moves the memory pointer one block to the left
- ">" moves the memory pointer one block the the right
- "+" Increments the value of what the pointer points to.
- "-" Decrements the value of what the pointer points to.
- "[" Opens a while loop.
- "]" If the value currently pointed to is zero, jump back to "[", otherwise exit the while loop.
- "," Accept 1 character of user input.
- "." Print the Ascii character of the value currently pointed to.

---
## Programs
- bfi.c is a brainfuck interpreter written in C. It even supports nested while loops.
- hello<span></span>.bf is a program written in brainfuck that prints Hello, World! to the terminal. I copied this program from [roachhd](https://gist.github.com/roachhd/dce54bec8ba55fb17d3a), which has a nice brainfuck tutorial.
- add<span></span>.bf is an original program I wrote. It simply takes an input of two single digit integers, adds them together, and displays the output to terminal. The most difficult part of this program was converting the added result to a two-character output.