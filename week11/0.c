#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/signalfd.h>
#include <unistd.h>

void print_line(int file_d)
{
    char c;
    int read_res = read(file_d, &c, 1);
    while (read_res > 0) {
        putchar(c);
        if (c == '\n') {
            break;
        }
        read_res = read(file_d, &c, 1);
    }

    fflush(stdout);
}

int main(int argc, char* argv[])
{
    sigset_t block_mask;
    sigset_t need_mask; // сигналы, которые нам нужны
    int files[argc];

    for (int i = 1; i < argc; ++i) {
        files[i - 1] = open(argv[i], O_RDONLY);
    }

    sigfillset(&block_mask);
    sigprocmask(SIG_BLOCK, &block_mask, NULL);
    sigemptyset(&need_mask);

    for (int i = 0; i < argc; ++i) {
        sigaddset(&need_mask, SIGRTMIN + i);
    }

    int sigfd = signalfd(-1, &need_mask, 0);
    struct signalfd_siginfo siginfo;

    while (1) {
        read(sigfd, &siginfo, sizeof(siginfo));
        int num_line = siginfo.ssi_signo - SIGRTMIN;
        if (num_line == 0) {
            break;
        } else {
            print_line(files[num_line - 1]);
        }
    }

    for (int i = 1; i < argc; ++i) {
        close(files[i - 1]);
    }

    return 0;
}