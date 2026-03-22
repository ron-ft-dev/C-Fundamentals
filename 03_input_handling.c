#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file 03_input_handling.c
 * @brief Demonstrates safer input handling in C using fgets and strtol.
 *
 * @description
 * Reads a full name and age from the console.
 * String input is read with fgets, then numeric input is parsed with strtol.
 *
 * @steps
 *  1) Compile:
 *     gcc 03_input_handling.c -o youare
 *
 *  2) Run:
 *     ./youare   -> Linux & macOS
 *     youare.exe -> Windows
 *
 * @notes
 * - fgets(name, sizeof(name), stdin)
 *   Reads a full line of input, including spaces, up to sizeof(name) - 1
 *   characters and always null-terminates the string if successful.
 *
 * - name[strcspn(name, "\n")] = '\0';
 *   Removes the trailing newline character if one was stored by fgets.
 *
 * - strtol(age_buffer, &age_buffer_end, 10)
 *   Converts a string to a long int using base 10.
 *   age_buffer_end points to the first character that was not parsed.
 *
 * @warning
 * - If the user enters more characters than the array can hold, the remaining
 *   characters stay in the input buffer and may affect later reads.
 *
 * - strtol only parses the numeric portion at the start of the string.
 *   Example:
 *     "25abc" parses as 25 unless the remaining characters are validated.
 *
 * - Doesn't handle:
 *   - whether the age is negative
 *   - whether the age is impossibly large
 *   - whether the input was truncated before reaching '\n'
 */

int main(void) {
  char name[50];
  char age_buffer[16];
  char *age_buffer_end;
  long int age;

  /* Read, validate, & clean name string from console */
  printf("Please enter your name: ");
  if (fgets(name, sizeof(name), stdin) == NULL) {
    printf("Failed to read name.\n");
    return 1;
  }
  name[strcspn(name, "\n")] = '\0';

  /* Read, validate, & clean age string from console */
  printf("Please enter your age: ");
  if (fgets(age_buffer, sizeof(age_buffer), stdin) == NULL) {
    printf("Failed to read age.\n");
    return 1;
  }
  age_buffer[strcspn(age_buffer, "\n")] = '\0';


  /* Parse integer from age string, 10 is for parsing base 10 values */
  age = strtol(age_buffer, &age_buffer_end, 10);
  if (age_buffer_end == age_buffer) {
    printf("No digits were found.\n");
    return 1; // Signals that program was unsuccessful to OS
  }

  if (*age_buffer_end != '\0') {
    printf("Invalid character: '%c'.\n", *age_buffer_end);
    return 1;
  }

  printf("Hi, %s. You are %ld years old.\n", name, age);
  return 0;
}
