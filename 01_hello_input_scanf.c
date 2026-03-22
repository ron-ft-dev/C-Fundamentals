#include <stdio.h>

/**
 * @file 01_hello_input_scanf.c
 * @brief Program demonstrating basic input and output in C.
 *
 * @description
 * Prompts the user for their name and prints a greeting.
 *
 * Steps:
 * 1) Compile:
 *    gcc 01_hello_input_scanf.c -o greet
 *
 * 2) Run:
 *    ./greet     (Linux / macOS)
 *    greet.exe   (Windows)
 *
 * @notes
 * - char name[50];
 *     Declares a character array that can store up to 49 characters
 *     plus a null terminator ('\0'), Arrays are talked about later (>_>).
 *
 * - scanf("%49s", name);
 *     Reads up to 49 non-whitespace characters from input.
 *     Stops early if a space, tab, or newline is encountered.
 *
 * - "%49s"
 *     Limits input size to prevent buffer overflow.
 *     One extra byte is reserved for the null terminator.
 *
 * @warning
 * - This program does NOT support names with spaces.
 *   Example: "Ronathon Jones" will only read "Ronathon".
 *   This is due to the nature of `scanf`.
 */

int main(void) {
    char name[50];

    printf("Enter your name: ");
    scanf("%49s", name);

    printf("Hello, %s!\n", name);
    return 0;
}
