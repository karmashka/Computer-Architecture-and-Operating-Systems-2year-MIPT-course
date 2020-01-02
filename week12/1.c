#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    char file[4096];
    fgets(file, sizeof(file), stdin);

    char* end;
    end = strchr(file, '\n');
    if (end != NULL) {
        *end = '\0';
    }

    int f = 0;
    while (file[f]) {
        if (!isspace(file[f])) {
            break;
        }
        f++;
    }
    if (!file[f]) {
        return 0;
    }
    int fd = open("my_c_code.c", O_CREAT | O_WRONLY, 0664);
    if (fd < 0) {
        perror("oopsie");
        return -1;
    }
    dprintf(
        fd,
        "#include <stdio.h>\n\nint main()\n{\n    printf(\"%%d\", (%s));\n}",
        file);

    if (close(fd) == -1) {
        perror("oooooooooops");
        return -1;
    }
    int pid = fork();
    if (pid == 0) {
        execlp("gcc", "gcc", "my_c_code.c", "-o", "a.out", NULL);
    } else if (pid > 0) {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("oops");
            return -1;
        }
        execlp("./a.out", "./a.out", NULL);
    }
    perror("oops");
    return -1;
}
