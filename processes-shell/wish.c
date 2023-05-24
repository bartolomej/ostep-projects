#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *path;
} Command;


void parse_command(Command parsed_command, const char *program);
int get_next_word_length(const char *array);

int main()
{
    char program[] = " ls ";
    Command parsed_command;

    int max_command_length = 10;
    parsed_command.path = malloc(sizeof(char) * max_command_length + 1);

    parse_command(parsed_command, program);
    printf("Command path: %s", parsed_command.path);
}

void parse_command(Command parsed_command, const char *command)
{
    int start = 0, end = 0, index = 0;
    while (index < strlen(command))
    {
        char current_char = command[index];
        switch (current_char)
        {
        case ' ':
            index++;
            start = index;
            break;
        default:
            index = index + get_next_word_length(&current_char);
            end = index;
            strncpy(parsed_command.path, command + start, end - start);
        }
    }
}

int get_next_word_length(const char *array) {
    int index = 0;
    while (index < strlen(array)) {
        if (array[index] == ' ')
        {
           break;
        }

        index++;
    }
    return index;
}