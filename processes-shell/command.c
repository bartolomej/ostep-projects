#include "command.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_command(Command *parsed_command)
{
    parsed_command->path = NULL;
    parsed_command->argc = 0;
    parsed_command->argv = malloc(MAX_PARAMETERS * sizeof(char *));
}

void parse_command(Command *parsed_command, const char *command)
{
    int start = 0, end = 0, index = 0, argc = -1;
    while (index < strlen(command))
    {
        // Pointer to the start of the current command argument.
        const char *arg = command + index;
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

            char *word = malloc(sizeof(char) * arg_length + 1);

            if (word == NULL)
            {
                fprintf(stderr, "Out of memory\n");
                exit(1);
            }

            strncpy(word, arg, arg_length);

            // First argument is the command executable path.
            if (argc == -1)
            {
                parsed_command->path = word;
            }
            else
            {
                parsed_command->argv[argc] = word;
            }

            argc++;
        }
    }

    parsed_command->argc = argc;
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