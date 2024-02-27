/**
 * @file main.c
 * @brief project lead
 * @version 1.0 15/02.2024
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.h"

void displayArt() {

    printf("\n");
    printf("ooo        ooooo               .                                     o8o                                oooo                .                      \n");
    printf("`88.       .888'             .o8                                     `\"\'                                `888              .o8                      \n");
    printf(" 888b     d'888   .ooooo.  .o888oo oooo d8b  .ooooo.        .oooo.o oooo  ooo. .oo.  .oo.   oooo  oooo   888   .oooo.   .o888oo  .ooooo.  oooo d8b \n");
    printf(" 8 Y88. .P  888  d88' `88b   888   `888\"\"8P d88' `88b      d88(  \"8 `888  `888P\"Y88bP\"Y88b  `888  `888   888  `P  )88b    888   d88' `88b `888\"\"8P \n");
    printf(" 8  `888'   888  888ooo888   888    888     888   888      `\"Y88b.   888   888   888   888   888   888   888   .oP\"888    888   888   888  888     \n");
    printf(" 8    Y     888  888    .o   888 .  888     888   888      o.  )88b  888   888   888   888   888   888   888  d8(  888    888 . 888   888  888     \n");
    printf("o8o        o888o `Y8bod8P'   \"888\" d888b    `Y8bod8P'      8\"\"888P' o888o o888o o888o o888o  `V88V\"V8P' o888o `Y888\"\"8o   \"888\" `Y8bod8P' d888b    \n");
    printf("\n");

}

void displayTextMenu() {
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  Bienvenue sur mon projet d'implémentation de l'algorithme de Dijkstra sur le métro de Paris.  ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
}

void read_file(const char *filename, const char *filename2, Node nodes[], int *num_nodes) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur dans la lecture de fichier %s\n", filename);
        exit(1);
    }

    int node_number;
    char ligne[6];
    int is_terminus;
    char node_name[60];
    int edge1, edge2, weight;
    int max_node_number = 0;


    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%d;%[^;];%d;%s", &node_number, ligne, &is_terminus, node_name) == 4) {
            nodes[*num_nodes].node_number = node_number;
            strcpy(nodes[*num_nodes].ligne, ligne);
            nodes[*num_nodes].is_terminus = is_terminus;
            strcpy(nodes[*num_nodes].node_name, node_name);
            nodes[*num_nodes].num_edges = 0;
            if (node_number > max_node_number) {
                max_node_number = node_number;
            }
            //printf("%s %d %s\n", nodes[*num_nodes].node_name, nodes[*num_nodes].node_number, nodes[*num_nodes].ligne);
            (*num_nodes)++;
        }
        else {
            printf("Error reading line: %s\n", line);
        }
    }

    fclose(file);

    for (int i = 0; i < max_node_number; i++) {
        nodes[i].num_edges = 0;
    }
    
    file = fopen(filename2, "r");
    if (file == NULL) {
        printf("Erreur dans la lecture de fichier %s\n", filename2);
        exit(1); 
    }

    // Read the edges
    while (fscanf(file, "%d;%d;%d", &edge1, &edge2, &weight) == 3) {
        if (edge1 <= max_node_number && edge2 <= max_node_number) {
            int node_index = edge1;
            int node_index2 = edge2;
            if (nodes[node_index].num_edges < MAX_NODES && nodes[node_index2].num_edges < MAX_NODES) {
                
                weight = (weight == 0) ? 1 : 1;

                nodes[node_index].edges[nodes[node_index].num_edges][0] = edge2;
                nodes[node_index].edges[nodes[node_index].num_edges][1] = weight;
                nodes[node_index].num_edges++;

                nodes[node_index2].edges[nodes[node_index2].num_edges][0] = edge1;
                nodes[node_index2].edges[nodes[node_index2].num_edges][1] = weight;
                nodes[node_index2].num_edges++;
                
            } else {
                printf("Erreur dans la lecture de fichier\n");
                break;
            }
        } else {
            printf("Invalide lien entre station: %d %d\n", edge1, edge2);
        }
    }

    fclose(file);
}


int main() {
    displayArt();
    displayTextMenu();

    Node nodes[MAX_NODES];
    int num_nodes = 0;
    read_file("stations.csv","relation.csv", nodes, &num_nodes);

    

    char start_node_name[50], end_node_name[50];
    int start_node = -1, end_node = -1;

    // Scan user inputs
    printf("\nStation de départ : "); 
    scanf("%s", start_node_name);
    printf("Station d'arrivée : ");
    scanf("%s", end_node_name);

    for (int i = 0; i < num_nodes; i++) {
        if (strcmp(nodes[i].node_name, start_node_name) == 0) start_node = nodes[i].node_number ;
        if (strcmp(nodes[i].node_name, end_node_name) == 0) end_node = nodes[i].node_number ;
    }

    if (start_node == -1){
            printf("Nom de station de départ invalide.\n");
            return 0;
    }

    if (end_node == -1){
            printf("Nom de station d'arrivée invalide.\n");
            return 0;
    }
    /*
    printf("Liste Station :\n");
    for (int i = 0; i < num_nodes; i++) {
        if (i==end_node || i==start_node ){
        printf("%d: %s ", nodes[i].node_number, nodes[i].node_name);
        for (int j = 0; j < nodes[i].num_edges; j++) {
            printf("(%d, %d) ", nodes[i].edges[j][0], nodes[i].edges[j][1]);
        }
        printf("\n");
        }
    }*/

    dijkstra(nodes, num_nodes, start_node, end_node);

    return 0;
}
