#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    if (argc < 3) {
        fprintf(stderr, "argc < 3");
        return -1;
    }
    char* filename = argv[1];
    long n = strtol(argv[2], NULL, 10);

    int f = mkfifo(filename, 0664);
    if (f == -1) {
        perror("mkfifo(): ");
        return -1;
    }
    int proc_id;
    scanf("%d", &proc_id);
    kill(proc_id, SIGHUP);

    f = open(filename, O_WRONLY);
    if (f == -1) {
        perror("open():");
        return -1;
    }

    sigaction(SIGPIPE, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);

    int i;
    for (i = 0; i <= n; ++i) {
        char buffer[16];
        int len = sprintf(buffer, "%d ", i);
        if (i == n) {
            buffer[--len] = '\0';
        }
        if (write(f, buffer, len) < 0) {
            if (errno == EPIPE)
                break;
            perror("write(): ");
            return -1;
        }
    }
    printf("%d\n", i);
    close(f);
    return 0;
}