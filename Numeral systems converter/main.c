#include <stdio.h>
#include <string.h>
#include "lib.h"

#define MAX_SIZE 50


void array_filling(int arr[], int filler, int i, int n) {
	for (i; i < n; i++) {
		arr[i] = filler;
	}
}

void int_decimal_to_base(long long number, int int_arr[], int base_to) {
	int i = 0;
	if (number == 0) 
		int_arr[i++] = 0;
	while (number > 0) {
		int_arr[i++] = number % base_to;
		number /= base_to;
	}
	array_filling(int_arr, -1, i, MAX_SIZE);
}


void float_decimal_to_base(double number, int float_arr[], int base_to) {
	int int_part = 0, i = 0;
	while (number > 0 && i <= 44) {
		number *= base_to;
		int_part = (int)number;
		number -= int_part;
		float_arr[i++] = int_part;
	}
	array_filling(float_arr, -1, i, MAX_SIZE);
}


void print_number(int int_arr[], int float_arr[], int n) {
	char symbol = 0;
	for (int i = 0; i < n; i++)
		if (int_arr[i] >= 0) {
			symbol = int_to_char(int_arr[i]);
			printf("%c", symbol);
		}
	printf(".");
	for (int i = 0; i < n; i++)
		if (float_arr[i] >= 0) {
			symbol = int_to_char(float_arr[i]);
			printf("%c", symbol);
		}
	printf("\n");
}


void print_error() {
	printf("bad input\n");
}


int main() {
	char str[MAX_SIZE] = { 0 };
	int base_from, base_to, fl[MAX_SIZE], in[MAX_SIZE];
	scanf("%d %d %s", &base_from, &base_to, str);
	int str_size = strlen(str);
	memset(in, -1, MAX_SIZE);
	memset(fl, -1, MAX_SIZE);
	int int_amount = get_int_and_float_arrays(str, in, fl, str_size);
	int float_amount = str_size - int_amount - 1;
	int error_int = string_to_number(in, int_amount);
	int error_float = string_to_number(fl, float_amount);

	if (error_int || error_float || 
		!check_bases(in, fl, int_amount, float_amount, base_from, base_to)) 
	{
		print_error();
		return 0;
	}

	long long int_decimal = to_decimal(in, int_amount, base_from, 1);
	double float_decimal = to_decimal(fl, str_size - int_amount - 1, base_from, 0);
	int_decimal_to_base(int_decimal, in, base_to);
	rev(in, MAX_SIZE);
	float_decimal_to_base(float_decimal, fl, base_to);
	print_number(in, fl, MAX_SIZE);
	return 0;
}