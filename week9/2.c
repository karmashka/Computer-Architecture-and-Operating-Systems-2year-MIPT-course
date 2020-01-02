#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int my_read()
{
    int buffer;
    int count = 0;
    for (int i = 0; i < 4096; ++i) {
        buffer = getchar();
        if (buffer == EOF) {
            return count;
        } else if (!isspace(buffer)) {
            count++;
        } else if (isspace(buffer) && count == 0) {
            continue;
        } else {
            return count;
        }
    }
    return count;
}

int fork_caller()
{
    int pid = fork();
    if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    } else if (pid == 0) {
        int read = my_read();
        if (read == 0) {
            exit(0);
        } else {
            exit(fork_caller() + 1);
        }
    } else {
        perror("ERROR");
        exit(-1);
    }
}

int main()
{
    int pid = fork();

    if (pid == 0) {
        return fork_caller();
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        printf("%d\n", WEXITSTATUS(status));
    } else {
        exit(-1);
    }
    return 0;
}
