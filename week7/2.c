//
// Created by karmashka on 09.11.2019.
//
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
    __uint64_t summ_bytes = 0;
    char file_name[256];
    struct stat s;

    while (1) {
        if (fgets(file_name, 256, stdin) == NULL) {
            break;
        }

        file_name[strlen(file_name) - 1] = 0;
        int st = lstat(file_name, &s);
        if (st < 0) {
            continue;
        }
        if (S_ISREG(s.st_mode)) {
            summ_bytes += s.st_size;
        }
    }

    printf("%lu\n", summ_bytes);

    return 0;
}
