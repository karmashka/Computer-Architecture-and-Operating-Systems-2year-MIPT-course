#include <stdio.h>
#include <string.h>

int skip_nulles(char *word) {
    int len = 0;
    int i = 2;
    while (word[i] == '0')  {
        i++;
    }
    for (; i < strlen(word); ++i) len++;
    if (len == 0) return 1;
    return len;
}

int main(int ac, char** av) {
    for (int i = 1; i < ac; ++i) {
        int len = skip_nulles(av[i]);
        int result = len  % 2 + (len) / 2;
        printf("%d\n", result);
    }
}
