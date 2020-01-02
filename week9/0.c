//
// Created by karmashka on 23.11.2019.
//

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int counter = 1;
    while (1) {
        int pid = fork();
        if (pid < 0) {
            printf("%d\n", counter);
            return 0;
        }
        if (pid != 0) {
            int status;
            waitpid(pid, &status, 0);
            break;
        }
    }
    return 0;
}