#include <stdlib.h>
#include <stdio.h>
#include <err.h>

enum Operator { CONCAT, PLUS, MINUS, MULT, DIV };

/*
 * If any operator contains -1 then we consider this state as terminated
 */
int has_next(int operators[])
{
	if (*operators == -1) {
		return 0;
	}
	return 1;
}

/*
 * Change the current operator on the next one.
 * If operator on the current position reached the last (DIV) value then we
 * reset current operator to the first (CONCAT) value and go to the previous
 * operator position and change it.
 * Example:
 * 1. [CONCAT, CONCAT]
 * 2. [CONCAT, PLUS]
 * ...
 * n. [CONCAT, DIV]
 * n+1. [PLUS, CONCAT]
 * n+2. [PLUS, PLUS]
 */
void next(int operators[], int operators_size)
{
	for (int i = operators_size - 1; i >= 0; i--) {
		if (operators[i] != DIV) {
			operators[i]++;
			return;
		}
		operators[i] = CONCAT;
	}

	/* Reset operators to the terminal END state. See has_next(int[]) */
	for (int i = 0; i < operators_size; i++) {
		operators[i] = -1;
	}
}

/*
 * Concatenates two digits. I.e. x=9 and y=9. The result is 99
 */
int concat(int x, int y)
{
	int pow = 10;
	while (y >= pow) {
		pow *= 10;
	}
	return x * pow + y;
}

int apply(int x, int y, enum Operator operator)
{
	switch (operator) {
	default:
		return concat(x, y);
	case PLUS:
		return x + y;
	case MINUS:
		return x - y;
	case MULT:
		return x * y;
	case DIV:
		return x / y;
	}
}

char printable_operator(int operator)
{
	switch (operator) {
	default:
		err(EXIT_FAILURE, "Unknown operator");
	case PLUS:
		return '+';
	case MINUS:
		return '-';
	case MULT:
		return '*';
	case DIV:
		return '/';
	}
}

void print_result(int result, int *nums, int nums_size, int *operators,
		  int operators_size)
{
	int n_ptr = 0, o_ptr = 0, e_ptr = 0;
	int expr_size = nums_size * 11 + operators_size + 1;
	char expr[expr_size];
	while (n_ptr < nums_size) {
		int num = nums[n_ptr++];
		e_ptr += snprintf(expr + e_ptr, expr_size - e_ptr, "%d", num);
		while (o_ptr < operators_size) {
			int operator= operators[o_ptr++];
			if (operator== CONCAT) {
				continue;
			}
			expr[e_ptr++] = printable_operator(operator);
			break;
		}
	}
	expr[e_ptr] = '\0';
	printf("Result: %d; Expression: %s\n", result, expr);
}

int main()
{
	int expected = 100;
	int nums[] = { 9, 9, 9, 9 };
	int nums_size = 4;
	int operators_size = nums_size - 1;
	int operators[operators_size];
	for (int i = 0; i < operators_size; i++) {
		operators[i] = CONCAT;
	}

	while (has_next(operators)) {
		int tmp_size = nums_size;
		int tmp[tmp_size];
		/* Initialize temp array. When initialized - it's a copy of nums */
		for (int i = 0; i < nums_size; i++) {
			tmp[i] = nums[i];
		}

		/* First apply all concatenations */
		int n_ptr = 0, o_ptr = 0;
		while (o_ptr < operators_size) {
			int operator= operators[o_ptr];
			if (operator== CONCAT) {
				tmp[n_ptr] = apply(tmp[n_ptr],
						   tmp[n_ptr + 1], operator);
				for (int j = n_ptr + 1; j < tmp_size - 1; j++) {
					tmp[j] = tmp[j + 1];
				}
				o_ptr++;
				tmp_size--;
			}
			o_ptr++, n_ptr++;
		}

		/* Calculate result applying operands to operators */
		n_ptr = 0, o_ptr = 0;
		int result = tmp[n_ptr++];
		while (o_ptr < operators_size) {
			int operator= operators[o_ptr++];
			if (operator== CONCAT) {
				continue;
			}
			result = apply(result, tmp[n_ptr++], operator);
		}

		if (result == expected) {
			print_result(result, tmp, tmp_size, operators,
				     operators_size);
			break;
		}
		next(operators, operators_size);
	}
	return EXIT_SUCCESS;
}
