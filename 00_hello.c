/**
 * @file: 00_helo.c
 * @brief: Introductory C program for teaching basic output.
 *
 * @description:
 *  This program prints "Hello, World!" to the console.
 *
 * Steps:
 *  1) Compile:
 *    gcc 00_hello.c -o hello
 *
 *  2) Run:
 *    ./hello   -> Linux & macOS
 *    hello.exe -> Windows
 *
 * @notes:
 *  - To change the output binary name:
 *    gcc 00_hello.c -o hello.exe
 *
 *  - #include <stdio.h>
 *    Gives us access to standard input & output functions like `printf`.
 *
 *  - `return 0;`
 *    Notifies that the program ran successfully to the operating system.
 *
 *  - "\n"
 *    Inserts a newline so the next output appears on a new line.
 */
#include <stdio.h>

int main(void) {
  printf("Hello, World!\n");
  return 0;
}
