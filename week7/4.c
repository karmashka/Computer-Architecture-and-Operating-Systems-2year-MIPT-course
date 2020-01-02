//
// Created by karmashka on 10.11.2019.
//

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char file_name[256];
    char absolute_file_name[PATH_MAX + 1];
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
        if (S_ISLNK(s.st_mode)) {
            char* ptr;
            ptr = realpath(file_name, absolute_file_name);
            if (ptr == NULL) {
                continue;
            }
            printf("%s\n", absolute_file_name);
        } else if (S_ISREG(s.st_mode)) {
            char link[300] = "link_to_";
            strcat(link, file_name);
            int err = symlink(file_name, link);
            if (err) {
                continue;
            }
            printf("%s", link);
        }
    }

    return 0;
}