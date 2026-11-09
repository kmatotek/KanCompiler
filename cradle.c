#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char TAB = '\t';

// lookahead char
char look;

// Read new character form input stream
void get_char(void) {
    look = fgetc(stdin);
}

// Report an error (custom naming convention)
void kan_error(const char *msg) {
    printf("\n");
    printf("\aError: %s\n", msg);
}

// Report error and halt/exit (custom naming convention)
void kan_abort(const char *msg) {
    kan_error(msg);
    exit(EXIT_FAILURE);
}

// Report what was expected

void expected(const char *msg) {

    // Ask snprintf how many characters it needs
    int length = snprintf(NULL, 0, "%s Expected", msg);

    // Allocate an array of the exact size needed (+1 for the '\0')
    char buffer[length + 1];

    snprintf(buffer, sizeof(buffer), "%s Expected", msg);
    // snprintf format (WHERE to save, MAX SIZE allowed, format, WHAT to insert)
    // snprintf prints the text directly into a string variable (a memory buffer)

    kan_abort(buffer);

}

// Match a specific input character
void match(char c) {
    if (look == c) {
        get_char();
    } else {
        const char str_c[4] = {'\'', c, '\'', '\0'};
        expected(str_c);
    }
}

// Recognize alpha char
bool is_alpha(char c) {
    return isalpha((unsigned char)c);
}

// Recognize a decimal digit
bool is_digit(char c) {
    return isdigit((unsigned char)c);
}

// get an Identifier
char get_name(void) {
    if (!is_alpha(look)) {
        expected("Name");
    }

    char name = toupper((unsigned char)look);
    get_char();
    return name;
}

// get a number
char get_num(void) {
   if (!is_digit(look)) {
       expected("Integer");
   }

    char num = look;
    get_char();
    return num;
}

// Output a string with Tab
void emit(const char *s) {
    printf("%c%s", TAB, s);
}

// Output a String with Tab and CRLF
void emit_ln(const char *s) {
    emit(s);
    printf("\r\n");
}

void init(void) {
    get_char();
}

int main(void) {
    init();

    // Parse the input stream
    char var_name = get_name();
    match('=');
    char value = get_num();

    // Format output values into strings with null terminators
    char label_var[2] = {var_name, '\0'};
    char label_val[2] = {value, '\0'};

    // Print results
    emit("variable: ");
    emit_ln(label_var);

    emit("value: ");
    emit_ln(label_val);

    return 0;
}

