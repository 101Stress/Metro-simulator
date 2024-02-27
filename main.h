#ifndef MAIN_H
#define MAIN_H

#define MAX_NODES 100

typedef struct {
    int node_number;
    char node_name[50];
    int edges[MAX_NODES][2]; // Assuming at most 100 edges per node
    int num_edges;
} Node;

void read_file(const char *filename, Node nodes[], int *num_nodes);

#endif
