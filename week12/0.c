#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char file[4096];
    fgets(file, sizeof(file), stdin);

    char* end;
    end = strchr(file, '\n');
    if (end != NULL) {
        *end = '\0';
    }

    int f = 0;
    while (file[f]) {
        if (!isspace(file[f])) {
            break;
        }
        f++;
    }
    if (!file[f]) {
        return 0;
    }
    char program[4096];
    sprintf(program, "print(%s)", file);
    execlp("python3", "python3", "-c", program, NULL);
    perror("exec():");
    return -1;
}