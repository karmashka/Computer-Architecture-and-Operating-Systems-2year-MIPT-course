#include <signal.h>
#include <stdlib.h>
#include <string.h>

void handler(int sig, siginfo_t* siginfo, void* skip)
{
    if (siginfo->si_value.sival_int == 0) {
        exit(0);
    }

    siginfo->si_value.sival_int--;
    sigqueue(siginfo->si_pid, SIGRTMIN, siginfo->si_value);
}

int main(int argc, char* argv[])
{
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, NULL);
    sigdelset(&mask, SIGRTMIN);

    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGRTMIN, &sa, NULL);

    while (1) {
        sigsuspend(&mask);
    }
}