#include <stdio.h>

int check_tail (int symbol) {
	if ((symbol >> 7) == 1 && ((symbol >> 6) & 1) == 0) {
		return 0;
	}
	return 1;
}

int classify (int symbol) {
	if (((symbol >> 7) & 1) == 0) {
		return 0;
	}
	int i = 7;
	while (((symbol >> i) & 1) == 1 && i > 0) {
		i--;
	}
	if (i < 0 || i == 6) {
		return -1;
	}
	return 7 - i - 1;
}

int main () {
	int number_of_access = 0;
	int number_of_fail = 0;
	while (1) {
		int symbol;
		symbol = getchar ();
		if (symbol == EOF) {
			break;
		}
		int tail_size = classify (symbol);
		if (tail_size == -1) {
			printf ("%d %d\n", number_of_access, number_of_fail);
			return 1;
		} else if (tail_size == 0) {
			number_of_access++;
		} else {
			for (int i = 0; i < tail_size; ++i) {
				int next_symbol;
				next_symbol = getchar ();
				if (check_tail (next_symbol)) {
					printf ("%d %d\n", number_of_access,
						number_of_fail);
					return 1;
				}
			}
			number_of_fail++;
		}
	}

	printf ("%d %d\n", number_of_access, number_of_fail);
	return 0;
}
