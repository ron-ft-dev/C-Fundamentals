/**
 * @file 02_hello_input_fgets.c
 * @brief Program demonstrating safe string input using fgets.
 *
 * @description
 * Prompts the user for their name and captures it using fgets,
 * then prints a greeting.
 *
 * @steps
 *  1) Compile:
 *    gcc 02_hello_input_fgets.c -o greet
 *
 *  2) Run:
 *    ./greet     (Linux / macOS)
 *    greet.exe   (Windows)
 *
 * @notes
 * - fgets(name, sizeof(name), stdin);
 *    Reads up to sizeof(name) - 1 characters or until a newline ('\n') is encountered.
 *    Always null-terminates the string.
 *
 * - Unlike scanf("%s", name):
 *    Supports spaces (e.g., "Ronathon Jones")
 *    Safer against buffer overflow
 *
 * @warning
 * - Newline behavior:
 *    fgets stores the newline character ('\n') if there is room in the buffer.
 *
 *    Example:
 *      Input:  Ronathon
 *      Stored: "Ronathon\n\0"
 *
 * - If the input exactly fills the buffer, the newline is NOT stored
 *   and remains in stdin, which may affect future input operations.
 *
 * - Because '\n' may be part of the string, it can affect:
 *    Printing
 *    String comparison
 *    File output
 *    Concatenation
 *
 * @example
 *  Without removing newline:
 *    Hello, Ronathon
 *    !
 *
 *  With removal:
 *    Hello, Ronathon!
 *
 * @solution
 *  Remove the newline explicitly:
 *
 *  name[strcspn(name, "\n")] = '\0';
 *
 *  This:
 *    Finds '\n'
 *    Replaces it with '\0'
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char name[50];

    printf("Please enter your name: ");
    fgets(name, sizeof(name), stdin);

    // Explicitly remove trailing newline if present
    name[strcspn(name, "\n")] = '\0';

    printf("Hello, %s!\n", name);
    return 0;
}
