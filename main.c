#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define SIZE_OF_BUFFER 3331
#define PATTERN_SIZE 17

long int powers_of_three[PATTERN_SIZE] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683,
							59049, 177147, 531441, 1594323, 4782969, 14348907,
							43046721, 129140163};

int get_hash(unsigned char str[], int start, int end) {
	int hash = 0; 
	for (int i = start; i < end; i++) {
		hash += (str[i] % 3) * powers_of_three[i-start]; 
	}
	return hash;
}

int check(unsigned char str[], unsigned char pattern[], int start, int end, int ind) {
	int j = 0;
	for (start; start < end; start++) {
		printf("%d ", ind + start + 1);
		if (pattern[j] != str[start])
			return 1;
		j++;
	}
}

void find_sub_str(unsigned char str[], unsigned char pattern[], int pattern_hash, int pattern_size, int str_size, int ind){
	for (int i = 0; i < str_size - pattern_size + 1; i++) {
				int sub_hash = get_hash(str, i, i + pattern_size);
				if (sub_hash == pattern_hash) 
					check(str, pattern, i, i + pattern_size, ind);
	}
}

int main() {
	unsigned char pattern[PATTERN_SIZE] = { 0 };
	unsigned char str[SIZE_OF_BUFFER + 1] = { 0 };
	gets(pattern);
	int str_size = 0;
	int ind = 0;
	int pattern_size = strlen(pattern);
	int pattern_hash = get_hash(pattern, 0, pattern_size);
	printf("%d ", pattern_hash);
	while ((str_size = fread(str, 1, SIZE_OF_BUFFER, stdin)) != 0) {
		find_sub_str(str, pattern, pattern_hash, pattern_size, str_size, ind);
		memset(str, '\0', str_size);
		ind += SIZE_OF_BUFFER;		
	}
	return 0;
}