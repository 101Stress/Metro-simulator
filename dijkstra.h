#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define MAX_NODES 500
#define INFINITY 99999
#define TEMPS_PAR_STATION 90

typedef struct {
    int node_number;
    int is_terminus;
    char ligne[6];
    char node_name[60];
    int num_edges;
    int edges[MAX_NODES][2];//edges[i][0] = destination 
                            //edges[i][1] = weight
} Node;

const char* Colorligne(const char* line);
void dijkstra(Node nodes[], int num_nodes, int start_node, int end_node);
void display_way(Node nodes[], int num_nodes, int start_node, int end_node, int predecessors[]);

#endif
