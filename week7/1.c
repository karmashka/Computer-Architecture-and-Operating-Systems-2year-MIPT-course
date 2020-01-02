//
// Created by karmashka on 09.11.2019.
//

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

struct Item {
    int value;
    uint32_t next_pointer;
};

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

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return 1;
    }
    int fd_read = open(argv[1], O_RDONLY);
    if (fd_read == -1) {
        return 1;
    }

    struct Item it;
    int read_bytes = read_retry(fd_read, &it, 8);

    while (read_bytes == 8 && it.next_pointer != 0) {
        printf("%d ", it.value);

        if (lseek(fd_read, it.next_pointer, SEEK_SET) == -1) {
            return -1;
        }
        read_bytes = read_retry(fd_read, &it, 8);
    }

    if (read_bytes == 8) {
        printf("%d ", it.value);
    }

    return 0;
}
