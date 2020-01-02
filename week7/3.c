//
// Created by karmashka on 11.11.2019.
//

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

struct stat s;

int read_retry(int fd_read, void* data, int size)
{
    void* cdata = data;
    while (1) {
        int read_bytes = read(fd_read, cdata, size);
        if (read_bytes == 0) {
            return cdata - data;
        }
        if (read_bytes < 0) {
            if (errno == EAGAIN || errno == EINTR) {
                continue;
            } else {
                return -1;
            }
        }
        cdata += read_bytes;
        size -= read_bytes;
        if (size == 0) {
            return cdata - data;
        }
    }
}

bool is_elf(int fd_read)
{
    lseek(fd_read, 0, SEEK_SET);
    char first_symbol;
    int read_bytes = read_retry(fd_read, &first_symbol, 1);
    if (read_bytes < 0) {
        return false;
    }
    if (first_symbol == 127) {
        char next_symbols[4];
        int read_bytes = read_retry(fd_read, next_symbols, 3);
        if (read_bytes < 3) {
            return false;
        }
        if (strcmp(next_symbols, "ELF") == 0) {
            return true;
        }
    }
    return false;
}

bool is_executable(char* file)
{
    if (stat(file, &s) < 0)
        return false;
    return (
        (s.st_mode & S_IXOTH) || (s.st_mode & S_IXUSR) ||
        (s.st_mode & S_IXGRP));
}

bool is_shebang(int fd_read)
{
    char start_symbol[3];
    lseek(fd_read, 0, SEEK_SET);
    int read_bytes = read_retry(fd_read, start_symbol, 2);
    if (read_bytes < 2) {
        return false;
    }

    if (strcmp(start_symbol, "#!") == 0) {
        char buffer[256];
        int i = 0;
        while (1) {
            if (read_retry(fd_read, buffer + i, 1) == 0 || buffer[i] == '\n') {
                buffer[i] = 0;
                break;
            }
            ++i;
        }

        while (i > 0 && isspace(buffer[i])) {
            buffer[i] = '\0';
            i--;
        }
        i = 0;
        while (i < strlen(buffer) && isspace(buffer[i])) {
            i++;
        }
        if (is_executable(buffer + i)) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    char file_name[256];

    while (1) {
        if (fgets(file_name, 256, stdin) == NULL) {
            break;
        }
        file_name[strlen(file_name) - 1] = 0; // \n fix
        if (is_executable(file_name)) {
            int fd_read = open(file_name, O_RDONLY | O_NOFOLLOW);
            if (fd_read == -1) {
                return 1;
            }

            if (!is_elf(fd_read) && !is_shebang(fd_read)) {
                printf("%s\n", file_name);
            }
            if (close(fd_read) == -1) {
                return -1;
            }
        }
    }
    return 0;
}