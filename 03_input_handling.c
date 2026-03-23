/**
 * @file 03_input_handling.c
 * @brief Full demonstration of safe input handling in C using fgets and strtol
 *
 * @description
 * Reads a first name, last name, and age from the console.
 * String input is read with fgets, then the age is parsed with strtol.
 *
 * @steps
 *  1) Compile:
 *    gcc 03_input_handling.c -o youare
 *
 *  2) Run:
 *    ./youare   -> Linux & macOS
 *    youare.exe -> Windows
 *
 * @note
 *  - fgets reads text safely into a fixed-sized buffer.
 *  - strtol converts a string to a long int.
 *  - parse_stop points to the first character that was not parsed.
 *  - errno is check after strtol to detect overflow or underflow.
 *
 * @warning
 * If the user enters more characters than the buffer, this program:
 *  - Flushes the buffer.
 *  - Keeps the truncated text.
 *
 * strtol only parses the numeric portion at the start of a string:
 *  - "67oof" only parses 67 from the string.
 */

 /* Include headers for predefined functions. */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <errno.h>
 #include <stdbool.h>

 /* Preprocessor constants used to avoid magic numbers. */
 #define MAX_LENGTH_NAME 50
 #define MAX_LENGTH_AGE 16

 #define MAX_VALUE_AGE 200
 #define MIN_VALUE_AGE 0

 #define MAX_ERROR_MESSAGE 128

 #define NUMERICAL_BASE 10

 /* Prompt preprocessor constants for prompt_line function. */
 #define PROMPT_SUCCESS 1
 #define PROMPT_EOF     0
 #define PROMPT_ERROR  -1

 /* Parse error preprocessor constant */
 #define PARSE_ERROR -1

/* Forward declarations of utility functions. */

/* Truncate the string to the maximum amount of characters */
void truncate_input(char* buffer, size_t buffer_length, int max_length);

/* Prompt the user for input and validate it. */
int prompt_line(char* buffer, size_t buffer_size, const char* prompt);

/* Parse the numeric value of age from the age buffer. */
long int parse_age(char* buffer);

/* The program entry point. */
int main(void) {
  /* Fixed-size buffers for read user input. */
  char buffer_name_first[MAX_LENGTH_NAME] = {0};
  char buffer_name_last [MAX_LENGTH_NAME] = {0};
  char buffer_age[MAX_LENGTH_AGE] = {0};
  int result = 0;
  long int age = 0;

  /* Prompt the user and read input into the buffers, handling prompt return errors */
  result = prompt_line(buffer_name_first, sizeof(buffer_name_first), "Enter your first name: ");
  if (result != PROMPT_SUCCESS) {
    return result;
  }

  result = prompt_line(buffer_name_last, sizeof(buffer_name_last), "Enter your last name: ");
  if (result != PROMPT_SUCCESS)
    return result;

  result = prompt_line(buffer_age, sizeof(buffer_age), "Enter your age: ");
  if (result != PROMPT_SUCCESS)
    return result;

  /* Parse age */
  age = parse_age(buffer_age);
  if (age == PARSE_ERROR) {
    return EXIT_FAILURE;
  }
  printf("Hi %s %s, You are %ld years old.\n", buffer_name_first, buffer_name_last, age);
  return EXIT_SUCCESS;
}

/**
 *  This function is doing multiple things:
 *
 * @note:
 *  - buffer_length is length of the string in the provided buffer.
 *  - fgets reads up to (max_length - 1) leaving space for the null terminator '\0'.
 *
 * If the buffer_length is equal to 49 then fgets read exactly the maximum characters.
 * However, this could also be exactly 49 characters follow by a newline.
 *
 * If the last character in the buffer is not a newline, then fgets stopped reading because
 * the buffer was full, not because the end of the line was reached.
 *
 * getchar will then consume the next characters in stdin until a newline or the end of the
 * line is reached. This happens because of the while loop condition.
 *
 */
void truncate_input(char* buffer, size_t buffer_length, int max_length) {
  if (buffer_length == (max_length - 1) && buffer[buffer_length - 1] != '\n') {
    int character = 0;
    printf("Too many characters entered. Truncating to %d characters.\n", max_length);
    while ((character = getchar()) != '\n' && character != EOF);
  }
}

/* Implementation of prompt line function declared earlier. */
int prompt_line(char* buffer, size_t buffer_size, const char* prompt) {
  char* read_result = NULL;

  /* Provided prompt was empty. */
  if (prompt == NULL || prompt[0] == '\0') {
    printf("[FAIL] User prompt cannot be empty.\n");
    return PROMPT_ERROR;
  }

  /* Prompt the user to enter input. */
  printf("%s", prompt);
  read_result = fgets(buffer, buffer_size, stdin);

  /* fgets returned NULL (EOF or input error). */
  if (read_result == NULL) {
    bool is_program_exit = feof(stdin);
    char error_message [MAX_ERROR_MESSAGE];

    /* The user signalled to exit the program (Ctrl-D or Ctrl-Z). */
    if (is_program_exit) {
      printf("[INFO] Input ended early. Exiting...\n");
      return PROMPT_EOF;
    }

    /* A genuine error was encountered, format message, and relay error with errno. */
    snprintf(error_message, sizeof(error_message), "[FAIL] Could not read into buffer.\n[PROMPT]%s", prompt);
    perror(error_message);
    return PROMPT_ERROR;
  }

  /* Truncate the input and remove trailing newlines. */
  truncate_input(buffer, strlen(buffer), buffer_size);
  buffer[strcspn(buffer, "\n")] = '\0';

  /* Reject all input if empty. */
  if (buffer[0] == '\0') {
    printf("[FAIL] Input cannot be empty.\n");
    return PROMPT_ERROR;
  }
  return PROMPT_SUCCESS;
}

long int parse_age(char* buffer) {
  char* parse_stop = NULL;
  long int age = 0;
  errno = 0;
  age = strtol(buffer, &parse_stop, NUMERICAL_BASE);

  /* No digits were entered. */
  if (parse_stop == buffer) {
    printf("No digits were found.\n");
    return PARSE_ERROR;
  }

  /* errno is set to ERANGE if the value overflowed or underflowed. */
  if (errno == ERANGE) {
    printf("Age is out of range for type long int.\n");
    return PARSE_ERROR;
  }

  /* Reject extra trailing characters after the numeric input. */
  if (*parse_stop != '\0') {
    printf("Invalid character: '%c'.\n", *parse_stop);
    return PARSE_ERROR;
  }

  /* Reject age outside of range */
  if (age < MIN_VALUE_AGE || age > MAX_VALUE_AGE) {
    printf("Age cannot be less than %d or greater than %d.\n", MIN_VALUE_AGE, MAX_VALUE_AGE);
    return PARSE_ERROR;
  }
  /* Parsing succeeded, return age value. */
  return age;
}
