#include <stdio.h>

/**
 * @file 01_hello_input_scanf.c
 * @brief Program demonstrating basic input and output in C using scanf.
 *
 * @description
 * Prompts the user for their name and prints a greeting.
 *
 * Steps
 *  1) Compile:
 *     gcc 01_hello_input_scanf.c -o greet
 *
 *  2) Run:
 *     ./greet     (Linux / macOS)
 *     greet.exe   (Windows)
 *
 * @notes
 * - char name[50];
 *   Declares a character array that can store up to 49 characters
 *   plus a null terminator ('\0'). Arrays are covered in more detail later.
 *
 * - scanf("%49s", name);
 *   Reads up to 49 non-whitespace characters from input into the array.
 *   Stops early if a space, tab, or newline is encountered.
 *
 * - "%49s"
 *   Limits the number of characters read to prevent buffer overflow.
 *   One byte is reserved for the null terminator.
 *
 * @warning
 * - This program does not support names with spaces.
 *   Example: "Ronathon Jones" will only read "Ronathon".
 *
 * - scanf leaves the trailing newline character in the input buffer.
 *   This can affect subsequent input operations if not handled.
 */

int main(void) {
  char name[50];

  printf("Enter your name: ");
  scanf("%49s", name);

  printf("Hello, %s!\n", name);
  return 0;
}
