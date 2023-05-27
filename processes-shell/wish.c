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
    char **argv;
} Command;

int max_parameters = 4;

void parse_command(Command *parsed_command, const char *program);
void init_command(Command *parsed_command);
int get_next_word_length(const char *array);

int main(int argc, char *argv[])
{
    char command[] = " ls -l -h -R";
    Command parsed_command;

    init_command(&parsed_command);
    parse_command(&parsed_command, command);

    printf("Command path: %s\n", parsed_command.path);
    printf("Command argc: %d\n", parsed_command.argc);

    for (int i = 0; i < max_parameters; i++)
    {
        printf("Argument %d: %s\n", i, parsed_command.argv[i]);
    }
}

void init_command(Command *parsed_command)
{
    parsed_command->path = NULL;
    parsed_command->argc = 0;
    parsed_command->argv = malloc(max_parameters * sizeof(char *));
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

            if (word == 0)
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