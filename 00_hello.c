#include <stdio.h>

/**
 * @file 00_hello.c
 * @brief Introductory C program for demonstrating basic output.
 *
 * @description
 * Prints "Hello, World!" to the console.
 *
 * Steps
 *  1) Compile:
 *     gcc 00_hello.c -o hello
 *
 *  2) Run:
 *     ./hello   -> Linux & macOS
 *     hello.exe -> Windows
 *
 * @notes
 * - To change the output binary name:
 *   gcc 00_hello.c -o hello.exe
 *
 * - #include <stdio.h>
 *   Provides access to standard input and output functions such as printf.
 *
 * - return 0;
 *   Indicates successful program execution to the operating system.
 *
 * - "\n"
 *   Inserts a newline so the next output appears on a new line.
 */

// Entry point of the program. Execution starts here.
int main(void) {
  printf("Hello, World!\n");
  return 0;
}
