#include "command.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    char *line = NULL;
    size_t line_length = 0;
    Command parsed_command;

    while (1)
    {
        printf("> ");
        int bytes_read = getline(&line, &line_length, stdin);

        if (strcmp(line, "exit\n") == 0)
        {
            exit(0);
        }
        

        init_command(&parsed_command);
        parse_command(&parsed_command, line);

        int child_pid = fork();

        if (child_pid < 0)
        {
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        else if (child_pid == 0)
        {
            execvp(parsed_command.path, parsed_command.argv);
        }
        else
        {
            wait(&child_pid);
        }
    }
}