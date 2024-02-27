#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "dijkstra.h"

// Define color
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_YEL   "\x1B[33m"
#define COLOR_MAG   "\x1B[35m"
#define COLOR_CYN   "\x1B[36m"
#define COLOR_WHT   "\x1B[37m"
#define COLOR_RESET "\033[0m"

void dijkstra(Node nodes[], int num_nodes, int start_node, int end_node) {
    int distances[MAX_NODES];
    int predecessors[MAX_NODES];
    bool visited[MAX_NODES];

    for (int i = 0; i < num_nodes; i++) {
        distances[i] = (i == start_node) ? 0 : INFINITY; // default value
        predecessors[i] = -1;
        visited[i] = false;
    }

    // The Dijkstra's algorithm
    for (int count = 0; count < num_nodes - 1; count++) {

        int min_distance = INT_MAX;
        int min_index = -1;
        for (int v = 0; v < num_nodes; v++) {
            if (!visited[v] && distances[v] < min_distance) {
                min_distance = distances[v];
                min_index = v;
                //printf("%d %d",min_index,min_distance);
            }
            
        }


        visited[min_index] = true;

        for (int j = 0; j < nodes[min_index].num_edges; j++) {
            int neighbor = nodes[min_index].edges[j][0];
            int weight = nodes[min_index].edges[j][1];
            //printf("%s %s\n",nodes[min_index].node_name,nodes[neighbor].node_name);

            if (!visited[neighbor] && distances[min_index] != INT_MAX && distances[min_index] + weight < distances[neighbor]) {
                distances[neighbor] = distances[min_index] + weight; // weight if the value is good
                predecessors[neighbor] = min_index;
            }
        }
    }


    printf("Le nombre minimum de station de %s vers %s est %d.\n", nodes[start_node].node_name, nodes[end_node].node_name, distances[end_node]);
    display_way(nodes, num_nodes, start_node, end_node, predecessors);
}

void display_way(Node nodes[], int num_nodes, int start_node, int end_node, int predecessors[]) {
    // Try to find if there is a way
    if (predecessors[end_node] == -1) {
        printf("Pas de chemin de %s vers %s.\n", nodes[start_node].node_name, nodes[end_node].node_name);
        return;
    }

    // List each predecessor to build the path
    int path[MAX_NODES];
    int path_length = 0;
    int current_node = end_node;
    while (current_node != -1) {
        path[path_length++] = current_node;
        current_node = predecessors[current_node];
    }

    printf("Les stations sont :\n");
    
    for (int i = path_length - 1; i >= 0; i--) {
        char ligne[6];
        strcpy( ligne, nodes[path[i]].ligne);
        printf("%s %s",Colorligne(ligne), nodes[path[i]].node_name);
        if (i > 0) {
            printf("\n");
        }
    }
    printf("\n");
}

const char* Colorligne(const char* line) {
    static char ligne[100] = "";

    if (strcmp(line, "1") == 0){
        strcpy(ligne, COLOR_YEL);
        strcat(ligne, "Metro 1 :");
    }
    else if (strcmp(line, "2") == 0){
        strcpy(ligne, COLOR_BLUE);
        strcat(ligne, "Metro 2 :");
    }
    else if (strcmp(line, "3") == 0){
        strcpy(ligne, COLOR_GREEN);
        strcat(ligne, "Metro 3 :");
    }
    else if (strcmp(line, "4") == 0){
        strcpy(ligne, COLOR_MAG);
        strcat(ligne, "Metro 4 :");
    }
    else if (strcmp(line, "5") == 0){
        strcpy(ligne, COLOR_YEL);
        strcat(ligne, "Metro 5 :");
    }
    else if (strcmp(line, "6") == 0){
        strcpy(ligne, COLOR_GREEN);
        strcat(ligne, "Metro 6 :");
    }
    else if (strcmp(line, "7") == 0 || strcmp(line, "7b") == 0 ){
        strcpy(ligne, COLOR_MAG);
        strcat(ligne, "Metro 7 :");
    }
    else if (strcmp(line, "8") == 0){
        strcpy(ligne, COLOR_MAG);
        strcat(ligne, "Metro 8 :");
    }
    else if (strcmp(line, "9") == 0){
        strcpy(ligne, COLOR_GREEN);
        strcat(ligne, "Metro 9 :");
    }
    else if (strcmp(line, "10") == 0){
        strcpy(ligne, COLOR_YEL);
        strcat(ligne, "Metro 10 :");
    }
    else if (strcmp(line, "11") == 0){
        strcat(ligne, "Metro 11 :");
    }
    else if (strcmp(line, "12") == 0){
        strcpy(ligne, COLOR_GREEN);
        strcat(ligne, "Metro 12 :");
    }
    else if (strcmp(line, "13") == 0){
        strcpy(ligne, COLOR_BLUE);
        strcat(ligne, "Metro 13 :");
    }
    else if (strcmp(line, "14") == 0){
        strcpy(ligne, COLOR_MAG);
        strcat(ligne, "Metro 14 :");
    }
    else if (strcmp(line, ligne) != 0 ){
        strcpy(ligne, line);
    }
    strcat(ligne, COLOR_RESET);
    
  return ligne;
}

