#include "command.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    char command[] = " ls -l -h -R";
    Command parsed_command;

    init_command(&parsed_command);
    parse_command(&parsed_command, command);

    printf("Command path: %s\n", parsed_command.path);
    printf("Command argc: %d\n", parsed_command.argc);

    for (int i = 0; i < MAX_PARAMETERS; i++)
    {
        printf("Argument %d: %s\n", i, parsed_command.argv[i]);
    }
}