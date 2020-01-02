#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

struct Item {
    int value;
    uint32_t next_pointer;
};

int main(int argc, char** argv)
{
    char* filename = argv[1];

    int fd = open(filename, O_RDONLY);
    size_t filesize = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    char* memory = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);

    if (filesize < 8) {
        close(fd);
        return 0;
    }
    struct Item it = *(struct Item*)memory;
    while (1) {
        printf("%d\n", it.value);
        if (it.next_pointer == 0)
            break;
        it = *(struct Item*)(memory + it.next_pointer);
    }
    int f = munmap(memory, filesize);
    if (f != 0) {
        return 1;
    }
    close(fd);
    return 0;
}