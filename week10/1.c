#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static volatile sig_atomic_t exited = 0;
static volatile sig_atomic_t input = 0;

static void handler(int signum)
{
    if (signum == SIGTERM) {
        exited = 1;
    } else if (signum == SIGUSR1) {
        input++;
    } else if (signum == SIGUSR2) {
        input *= -1;
    }
}

int main()
{
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    sigaction(
        SIGTERM,
        &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART},
        NULL);
    sigaction(
        SIGUSR1,
        &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART},
        NULL);
    sigaction(
        SIGUSR2,
        &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART},
        NULL);

    sigemptyset(&mask);

    scanf("%d", &input);
    printf("%d\n", getpid());
    fflush(stdout);

    while (!exited) {
        sigsuspend(&mask);
        if (!exited) {
            printf("%d\n", input);
            fflush(stdout);
        }
    }
    return 0;
}