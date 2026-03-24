#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

 /* Prompt preprocessor constants for prompt_line function. */
#define PROMPT_SUCCESS 1
#define PROMPT_EOF     0
#define PROMPT_ERROR  -1

#define MAX_ERROR_MESSAGE 128

/* Truncate the string to the maximum amount of characters */
void truncate_input(char* buffer, size_t buffer_length, int max_length);

/* Prompt the user for input and validate it. */
int prompt_line(char* buffer, size_t buffer_size, const char* prompt);

/* Program entry point */
int main(void) {

  return EXIT_SUCCESS;
}

/* REUSED - See 03_input_handling for details. */

void truncate_input(char* buffer, size_t buffer_length, int max_length) {
  if (buffer_length == (max_length - 1) && buffer[buffer_length - 1] != '\n') {
    int character = 0;
    printf("Too many characters entered. Truncating to %d characters.\n", max_length);
    while ((character = getchar()) != '\n' && character != EOF);
  }
}

int prompt_line(char* buffer, size_t buffer_size, const char* prompt) {
  char* read_result = NULL;
  if (prompt == NULL || prompt[0] == '\0') {
    printf("[FAIL] User prompt cannot be empty.\n");
    return PROMPT_ERROR;
  }
  printf("%s", prompt);
  read_result = fgets(buffer, buffer_size, stdin);
  if (read_result == NULL) {
    bool is_program_exit = feof(stdin);
    char error_message [MAX_ERROR_MESSAGE];
    if (is_program_exit) {
      printf("[INFO] Input ended early. Exiting...\n");
      return PROMPT_EOF;
    }
    snprintf(error_message, sizeof(error_message), "[FAIL] Could not read into buffer.\n[PROMPT]%s", prompt);
    perror(error_message);
    return PROMPT_ERROR;
  }
  truncate_input(buffer, strlen(buffer), buffer_size);
  buffer[strcspn(buffer, "\n")] = '\0';
  if (buffer[0] == '\0') {
    printf("[FAIL] Input cannot be empty.\n");
    return PROMPT_ERROR;
  }
  return PROMPT_SUCCESS;
}
