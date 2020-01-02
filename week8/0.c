#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    char* filename = argv[1];
    char* string_to_search = argv[2];

    int fd = open(filename, O_RDONLY);
    size_t filesize = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    char* memory = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
    char* data = memory;
    int len = strlen(string_to_search);
    while (1) {
        char* ptr;
        if (filesize - (memory - data) + 1 <= len) {
            break;
        }
        if ((ptr = strstr(memory, string_to_search)) == NULL) {
            break;
        }
        memory = ptr + 1;
        printf("%ld\n", memory - data - 1);
    }

    int f = munmap(memory, filesize);
    if (f != 0) {
        return 1;
    }
    close(fd);
    return 0;
}