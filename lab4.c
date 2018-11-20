#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>

#define MAX_SIZE 11

void swap(char *a, char *b){
	char t = *a;
	*a = *b;
	*b = t;
}


int find_min_index(char str[], int *min, int start, int str_len){
	int min_index = 11;
	for (int i = start; i < str_len; i++){
		if (str[i] - '0' < *min && str[i] > str[start - 1]){
			*min = str[i] - '0';
			min_index = i;
		}
	}
	return min_index;
}

char *find_max(char str[]){
	int i = 0, j = 0;
	int arr[MAX_SIZE] = {0};
	int str_len = strlen(str);
	char *res = (char *) malloc(sizeof(char) * MAX_SIZE);
	memset(res, '\0', MAX_SIZE);
	for (i; i < str_len; i++){
		if (!isdigit(str[i]))
			return res;
		arr[str[i] - '0']++;
	}
	for (i = MAX_SIZE-1; i >= 0; i--){
		if (arr[i] == 1)
			res[j++] = (char)(i + '0');
		else if (arr[i] > 1){
			res[0] = '\0';
			return res;
		}
	}
	return res;
}

void sort(char arr[], int len, int start) {
    for (int i = start; i < len - 1; i++) {
        for (int j = start + 1; j < len; j++) {
            if (arr[i] > arr[j])
                swap(&arr[i], &arr[j]);
        }
    }
}


void algorithm(char str[], char max_str[], int n){
	char s[MAX_SIZE] = {0};
	strcpy(s, str);
	int i = 0, j = 0;
	int str_len = strlen(s);
	while (j < n && strcmp(s, max_str) != 0){
		i = str_len - 1;
		while (i > 0 && s[i] < s[i-1])
			i--;
		if (i == 0)
			break;
		int min = 10;
		int min_index = find_min_index(s, &min, i, str_len);
		swap(&s[i - 1], &s[min == 10 ? i : min_index]);
		sort(s, str_len, i);
		printf("%s\n", s);
		j++;
	}
}

int main(){
	int n = 0;
	char str[MAX_SIZE] = {0};
	scanf("%s%d", str, &n);
	char *max = find_max(str);
	if (strlen(max)){
		algorithm(str, max, n);
	}
	else
		printf("bad input");
	free(max);
	return 0;
}