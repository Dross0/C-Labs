#include <stdio.h>
#include <stdlib.h>

#include "context.h"

uint **create_graph(int vertices);
void dijkstra(uint *graph[], uint start, int end, int vertices);
void fillLensAndParents(int vertices, int start, uint * lengths, int * parents, uint * graph[], bit* set);
void printLens(int vertices, int start, uint * lengths);
void printPath(int start, int end, const uint * lengths, uint * graph[], const int * parents);
int findMin(const bit *set, const uint *lengths, int vertices);
void check_edge(Edge edge, int vertices);
void check_input(int vertices, int edges, int start, int end);
void check_input_2(int edges, int lines);
void error(char *msg);



int main() {
    uint vertices, edges, start, end;
    FILE *input = fopen("in.txt", "r");
    if (fscanf(input, "%d%d%d%d", &vertices, &start, &end, &edges) != 4) {
        error("bad number of lines");
    }
    start--;
    end--;
    check_input(vertices, edges, start, end);
    uint **graph = create_graph(vertices);
    int lines = 0;
    Edge tmp;
    while (!feof(input) && fscanf(input, "%d%d%d", &tmp.left, &tmp.right, &tmp.weight) == 3) {
        check_edge(tmp, vertices);
        graph[tmp.left - 1][tmp.right - 1] = tmp.weight;
        graph[tmp.right - 1][tmp.left - 1] = tmp.weight;
        lines++;
    }
    check_input_2(edges, lines);
    dijkstra(graph, start, end, vertices);
    fclose(input);
    return 0;
}

uint **create_graph(int vertices) {
    uint **graph = (uint **) malloc(sizeof(uint *) * vertices);
    for (int i = 0; i < vertices; i++) {
        graph[i] = (uint *) malloc(sizeof(uint) * vertices);
        for (int j = 0; j < vertices; j++) {
            graph[i][j] = NO_PATH;
        }
    }
    return graph;
}

void dijkstra(uint *graph[], uint start, int end, int vertices) {
    bit *set = calloc((size_t) vertices, 1);
    set[start] = 1;
    int *parents = malloc(sizeof(uint) * vertices);
    uint *lengths = malloc(sizeof(uint) * vertices);
    fillLensAndParents(vertices, start, lengths, parents, graph, set);
    printLens(vertices, start, lengths);
    printPath(start, end, lengths, graph, parents);
}

void fillLensAndParents(int vertices, int start, uint * lengths, int * parents, uint * graph[], bit* set){
    for (int i = 0; i < vertices; i++) {
        lengths[i] = graph[start][i];
        parents[i] = lengths[i] == NO_PATH ? NO_PATH : start;
    }
    for (int i = 0; i < vertices - 1; i++) {
        int vertex = findMin(set, lengths, vertices);
        if (vertex == -1) continue;
        set[vertex] = 1;
        for (int j = 0; j < vertices; j++) {
            if (lengths[j] > lengths[vertex] + graph[vertex][j]) {
                parents[j] = vertex;
                lengths[j] = lengths[vertex] + graph[vertex][j];
            }
            if (lengths[j] == NO_PATH && lengths[vertex] != NO_PATH && graph[vertex][j] != NO_PATH) {
                lengths[j] = INT_MAX_PLUS;
                parents[j] = vertex;
            }
        }
    }
}

void printLens(int vertices, int start, uint * lengths){
    for (int i = 0; i < vertices; i++) {
        if (i != start) {
            if (lengths[i] <= INT_MAX)
                printf("%u ", lengths[i]);
            else
                printf(lengths[i] == NO_PATH ? "oo " : "INT_MAX+ ");
        } else {
            printf("0 ");
        }
    }
    printf("\n");
}

void printPath(int start, int end, const uint * lengths, uint * graph[], const int * parents){
    if (start == end) {
        printf("%d", start + 1);
    } else if (lengths[end] == NO_PATH)
        printf("no path");
    else {
        if (graph[0][1] == graph[1][2] && graph[1][2] == graph[2][3] &&
            graph[2][3] == graph[3][0] && graph[3][0] == INT_MAX && end != 1) {
            printf("overflow");
        } else {
            printf("%d ", end + 1);
            do {
                printf("%d ", parents[end] + 1);
                end = parents[end];
            } while (end != start);
        }
    }
}


int findMin(const bit *set, const uint *lengths, int vertices) {
    int min = NO_PATH, iMin = -1;
    for (int i = 0; i < vertices; i++) {
        if (!set[i] && lengths[i] < min) {
            min = lengths[i];
            iMin = i;
        }
    }
    return iMin;
}

void check_input(int vertices, int edges, int start, int end) {
    if (vertices < 0 || vertices > 5000) {
        error("bad number of vertices");
    }
    if (edges < 0 || edges > vertices * ((vertices + 1) / 2)) {
        error("bad number of edges");
    }
    if (start < 0 || start > vertices || end < 0 || end > vertices) {
        error("bad vertex");
    }
}

void check_edge(Edge edge, int vertices) {
    if (edge.left < 1 || edge.left > vertices || edge.right < 1 || edge.right > vertices) {
        error("bad vertex");
    }
    if (edge.weight < 0 || edge.weight > INT_MAX) {
        error("bad length");
    }
}

void check_input_2(int edges, int lines) {
    if (edges != lines) {
        error("bad number of lines");
    }
}

void error(char *msg) {
    printf("%s", msg);
    exit(0);
}