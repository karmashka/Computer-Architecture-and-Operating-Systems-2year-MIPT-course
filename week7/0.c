#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

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

int write_in_files(int fd_read, int fd_digits, int fd_other)
{
    char buffer[4096];
    int read_bytes = read_retry(fd_read, buffer, 4096);
    while (read_bytes) {
        if (read_bytes < 0) {
            return 3;
        }
        for (int i = 0; i < read_bytes; ++i) {
            if (isdigit(buffer[i])) {
                int written_bytes = write(fd_digits, &buffer[i], 1);
                if (written_bytes < 0) {
                    return 3;
                }
            } else {
                int written_bytes = write(fd_other, &buffer[i], 1);
                if (written_bytes < 0) {
                    return 3;
                }
            }
        }
        read_bytes = read_retry(fd_read, buffer, 4096);
    }

    return 0;
}

int main(int argc, char* argv[])
{
    if (argc < 4) {
        return 3;
    }

    int fd_read = open(argv[1], O_RDONLY);
    if (fd_read == -1) {
        return 1;
    }

    int fd_digits = open(argv[2], O_WRONLY | O_CREAT, 0664);
    if (fd_digits == -1) {
        return 2;
    }

    int fd_other = open(argv[3], O_WRONLY | O_CREAT, 0664);
    if (fd_other == -1) {
        return 2;
    }

    int written = write_in_files(fd_read, fd_digits, fd_other);

    if (written == 3) {
        return 3;
    }

    if (close(fd_read)) {
        return 3;
    }

    if (close(fd_digits)) {
        return 3;
    }

    if (close(fd_other)) {
        return 3;
    }

    return 0;
}
