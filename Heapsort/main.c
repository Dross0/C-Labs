#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void add_element(int heap[], int x, int *heap_size) {
	int p = *heap_size;
	heap[*heap_size] = x;
	*heap_size = *heap_size + 1;
	while (heap[p] < heap[(p - 1) / 2] && p > 0) {
		swap(&heap[p], &heap[(p - 1) / 2]);
		p = (p-1) / 2;
	}	
}

int remove_from_heap(int heap[], int *heap_size) {
	int max_elem = heap[0];
	heap[0] = heap[*heap_size - 1];
	*heap_size = *heap_size - 1;
	int p = 0;
	int flag = 1;
	int min = 0;
	while ((p * 2) + 1 <= *heap_size && flag) {
		flag = 0;
		min = p * 2 + 1;
		if (min + 1 <= *heap_size && heap[min] > heap[min + 1])
			min++;
		if (heap[p] > heap[min]) {
			flag = 1;
			swap(&heap[p], &heap[min]);
			p = min;
		}		
	}
	return max_elem;
}


void make_heap(int heap[], int n, int *heap_size) {
	for (int i = 0; i < n; i++) {
		add_element(heap, heap[i], heap_size);
	}
}

void heap_sort(int heap[], int n, int *heap_size) {
	for (int i = 0; i < n; i++) {
		printf("%d ", remove_from_heap(heap, heap_size));
	}
}

int main() {
	int n = 0;
	scanf("%d", &n);
	int *heap = (int *)malloc(sizeof(int) * n);
	if (heap == NULL)
		return -1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &heap[i]);
	}
	int heap_size = 0;
	make_heap(heap, n, &heap_size);
	heap_sort(heap, n, &heap_size);
	free(heap);
	return 0;
}
