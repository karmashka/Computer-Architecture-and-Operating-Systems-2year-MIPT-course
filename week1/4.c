#include <stdint.h>
#include <stdio.h>
#include <ctype.h>

void add_symbol(uint64_t *last_set, char symbol) {
    if (isdigit(symbol)) {
        *last_set |= 1ull << (62 - (symbol - '0')) ;
    } else if (isupper(symbol)) {
        *last_set |= 1ull << (52 - (symbol - 'A'));
    } else if (islower(symbol)) {
        *last_set |= 1ull << (26 - (symbol - 'a'));
    }
}

void set_intersection(uint64_t last_set, uint64_t *result_set) {
    *result_set &= last_set;
}

void set_union (uint64_t last_set, uint64_t *result_set) {
    *result_set |= last_set;
}

void set_full(uint64_t *result_set) {
    *result_set = ~(*result_set);
}

void set_difference(uint64_t last_set, uint64_t *curr_set) {
    *curr_set ^= last_set;
}

int main() {
    uint64_t result_set = 0, last_set = 0;
    while (1) {
        char symbol = 0;
        symbol = getchar();
        if (symbol == EOF) {
            break;
        } else if (symbol == '|') {
            set_union(last_set, &result_set);
            last_set = 0;
        } else if (symbol == '~') {
            set_full(&result_set);
            last_set = 0;
        } else if (symbol == '^') {
            set_difference(last_set, &result_set);
            last_set = 0;
        } else if (symbol == '&') {
            set_intersection(last_set, &result_set);
            last_set = 0;
        } else if (isalpha(symbol) || isdigit(symbol)) {
            add_symbol(&last_set, symbol);
        }
    }

    for (int i = 62; i > 0; --i) {
        if (((result_set >> i) & 1) && i > 52) {
            printf("%c", '0' - i + 62);
        } else if (((result_set >> i) & 1) && i > 26) {
            printf("%c", 'A' + 52 - i);
        } else if (((result_set >> i) & 1)) {
            printf("%c", 'a' + 26 - i);
        }
    }
    return 0;
}