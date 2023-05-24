#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    // Pointer to the command executable path.
    char *path;
    // Number of command arguments.
    int argc;
    // Pointer to the arguments array.
    char *argv[];
} Command;

void parse_command(Command parsed_command, const char *program);
int get_next_word_length(const char *array);

int main(int argc, char *argv[])
{
    char command[] = " ls ";
    Command parsed_command;

    int max_command_length = 10;
    parsed_command.path = malloc(sizeof(char) * max_command_length + 1);

    parse_command(parsed_command, command);

    printf("Command path: %s\n", parsed_command.path);
    printf("Command argc: %d\n", parsed_command.argc);
}

void parse_command(Command parsed_command, const char *command)
{
    int start = 0, end = 0, index = 0, argc = 0;
    while (index < strlen(command))
    {
        // Pointer to the start of the current command argument.
        const char *arg = command + start;
        switch (arg[0])
        {
        case ' ':
            index++;
            start = index;
            break;
        default:
            index = index + get_next_word_length(arg);
            end = index;
            // Argument character length.
            int arg_length = end - start;

            // First argument is the command executable path.
            if (argc == 0)
            {
                strncpy(parsed_command.path, arg, arg_length);
            }

            argc++;
        }
    }

    parsed_command.argc = argc;
}

int get_next_word_length(const char *array)
{
    int word_length = 0;
    while (word_length < strlen(array))
    {
        if (array[word_length] == ' ')
        {
            break;
        }

        word_length++;
    }
    return word_length;
}