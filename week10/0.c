#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static volatile sig_atomic_t counter = 0;

static void handler(int signum)
{
    if (signum == SIGINT) {
        counter++;
    }
}

int main()
{
    sigaction(
        SIGTERM,
        &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART},
        NULL);
    sigaction(
        SIGINT,
        &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART},
        NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    int old_counter = counter;
    while (1) {
        pause();
        if (old_counter == counter) {
            break;
        }
        old_counter = counter;
    }
    printf("%d\n", counter);

    return 0;
}