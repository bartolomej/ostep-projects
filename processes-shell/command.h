#define MAX_PARAMETERS 4

typedef struct
{
    // Pointer to the command executable path.
    char *path;
    // Number of command arguments.
    int argc;
    // Pointer to the arguments array.
    char **argv;
} Command;

void parse_command(Command *parsed_command, const char *program);

void init_command(Command *parsed_command);

int get_next_word_length(const char *array);