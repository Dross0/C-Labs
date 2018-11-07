#define SIZE_OF_ALPHABET 256
#define MAX_LEN_OF_SUBSTRING 17
#define LEN_OF_BUFFER 1000

#include <stdio.h>
#include <memory.h>
#include <string.h>


void set_alphabet(int *d, unsigned char *substring, int n) {
    int m = 0;
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
        d[i] = n;
    if (n == 1) return;
    for (int i = n - 2; i >= 0; i--) {
        m = (int)substring[i];
        if (d[m] == n) {
            d[m] = n - i - 1;
        }
    }
}

int tracing(FILE *out, int *d, unsigned char *str, unsigned char *pattern, int len_str, int len_substr, int ind, int index) {
    int cnt = 0;
    int last = len_substr-1, subindex = 0, sublast = 0;
    while (index < len_str) {
        sublast = last;
        subindex = index;
        cnt = 0;
        while (sublast >= 0 && subindex >= 0 && str[subindex] == pattern[sublast]) {
            fprintf(out, "%d ", ind + subindex + 1);
            subindex--;
            cnt++;
            sublast--;
        }
        if (!cnt) {
            fprintf(out, "%d ", ind + index + 1);
        } else if (sublast != -1) {
            fprintf(out, "%d ", ind + subindex + 1);
        }
        if (sublast != last) {
            index += d[pattern[last]];
        } else {
            index += d[str[index]];
        }
    }
    return index;
}


int main() {
    int d[SIZE_OF_ALPHABET];
    unsigned char str[LEN_OF_BUFFER+1] = {0}, last_str[MAX_LEN_OF_SUBSTRING] = {0};
    unsigned char substring[MAX_LEN_OF_SUBSTRING] = {0};
    gets(substring);
    int len_substr = (int) strlen(substring);
    set_alphabet(d, substring, len_substr);
    unsigned char c = 0;
    int i = 0, ind = 0, k = 0, index = -1;
    FILE *in = fopen("in.txt", "r");
    FILE *out = fopen("out.txt", "w");
    fseek(in, len_substr+2, SEEK_SET);
    c = fgetc(in);
    while (!feof(in)){
        str[i] = c;
        if (i >= LEN_OF_BUFFER) {
            index =  tracing(out, d, str, substring, LEN_OF_BUFFER, len_substr, ind, index==-1?len_substr - 1:index+len_substr-2) - LEN_OF_BUFFER;
            for (int j = LEN_OF_BUFFER + 2 - len_substr; j < LEN_OF_BUFFER + 1; j++)
                last_str[k++] = str[j];
            memset(str, '\0', LEN_OF_BUFFER);
            for (int m = --k; m >= 0; m--){
                str[m] = last_str[m];
            }
            ind += i + 2;
            ind-=len_substr;
            i = k;
            k = 0;
        }
        i++;
        c = fgetc(in);
    }
    tracing(out, d, str, substring, (int) strlen(str), len_substr, ind, ind==0?len_substr - 1:index+len_substr-2);
    return 0;
}