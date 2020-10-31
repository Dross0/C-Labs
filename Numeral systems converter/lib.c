#include "lib.h"
#include <math.h>

void rev(int arr[], int n) {
	int temp = 0;
	for (int i = 0; i < n / 2; i++) {
		temp = arr[i];
		arr[i] = arr[n - i - 1];
		arr[n - i - 1] = temp;
	}
}

int string_to_number(int arr[], int n) {
	char c = 0;
	for (int i = 0; i < n; i++) {
		c = arr[i];
		if (c >= 'a' && c <= 'f')
			arr[i] = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			arr[i] = c - 'A' + 10;
		else if (c >= '0' && c <= '9')
			arr[i] = c - '0';
		else
			return 1;
	}
	return 0;
}

double to_decimal(int arr[], int n, int base_from, int is_int) {
	double decimal = 0;
	for (int i = 0; i < n; i++) {
		decimal += arr[i] * pow(base_from, is_int ? (n - i - 1) : (-i - 1));
	}
	return decimal;
}

char int_to_char(int number) {
	if (number >= 10)
		return (char)(number + 'A' - 10);
	return (char)(number + '0');
}

int get_int_and_float_arrays(char *str, int integer_arr[], int float_arr[], int n) {
	int dot_amount = 0, j = 0, int_amount = 0, float_amount = 0;
	for (int i = 0; i < n; i++) {
		if (str[i] == '.') {
			dot_amount++;
			j = 0;
		}
		else
			if (dot_amount) {
				float_arr[j++] = str[i];
				float_amount++;
			}
			else {
				integer_arr[j++] = str[i];
				int_amount++;
			}
	}
	if (dot_amount > 1 || int_amount == 0 || (dot_amount != 0 && float_amount == 0)){
		return -1;
	}
	return int_amount;
}

int check_bases(int in[], int fl[], int in_len, int fl_len,
	int base_from, int base_to) {

	if (base_from < 2 || base_from > 16 || base_to < 2 || base_to > 16) {
		return 0;
	}

	for (int i = 0; i < in_len; i++) {
		if (in[i] >= base_from)
			return 0;
	}
	for (int i = 0; i < fl_len; i++) {
		if (in[i] >= base_from)
			return 0;
	}
	return 1;
}