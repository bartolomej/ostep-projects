#include "command.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    char* line = NULL;
    size_t line_length = 0;

    int bytes_read = getline(&line, &line_length, stdin);

    Command parsed_command;

    init_command(&parsed_command);
    parse_command(&parsed_command, line);

    printf("Command path: %s\n", parsed_command.path);
    printf("Command argc: %d\n", parsed_command.argc);

    for (int i = 0; i < MAX_PARAMETERS; i++)
    {
        printf("Argument %d: %s\n", i, parsed_command.argv[i]);
    }
}