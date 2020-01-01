#include <stdio.h>
#include <stdlib.h>
int main(int ac, char** av) {
    float number1;
    int N = 42;
    char number2[N];
    scanf("%f %s", &number1, number2);
    long calculated = strtol(number2, NULL, 16) + strtol(av[1], NULL, 27);
    float answer = number1 + (float)calculated;
    printf("%.3f\n", answer);
    return 0;
}