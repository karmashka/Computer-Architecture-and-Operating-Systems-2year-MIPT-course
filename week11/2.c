#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

sig_atomic_t PID;
sig_atomic_t ret_value = -1;

void handler(int sig)
{
    char time[] = "timeout\n";
    write(STDOUT_FILENO, time, sizeof(time) - 1);
    kill(PID, SIGTERM);
    ret_value = 2;
}

int main(int argc, char** argv)
{
    int seconds = atoi(argv[1]);

    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, NULL);

    int pid = fork();
    if (pid == 0) {
        execvp(argv[2], &argv[2]);
    } else if (pid > 0) {
        PID = pid;
        alarm(seconds);

        int status;
        waitpid(pid, &status, 0);
        if (ret_value != 2) {
            if (WIFEXITED(status)) {
                ret_value = 0;
                printf("ok\n");
            } else if (WIFSIGNALED(status)) {
                ret_value = 1;
                printf("signaled\n");
            }
        }
        fflush(stdout);
        return ret_value;
    }
}