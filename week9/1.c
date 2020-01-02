#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);

    for (int i = 1; i < N; ++i) {
        int pid = fork();

        if (pid == 0) {
            printf("%d ", i);
            fflush(stdout);
            return 0;
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        }
        if (pid < 0) {
            continue;
        }
    }

    printf("%d\n", N);
    fflush(stdout);
    return 0;
}