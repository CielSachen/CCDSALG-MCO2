/*
 * Social Network uses graphs to represent relationships between users.
 * Copyright (C) 2025  Raphael Panaligan  Jek Degullado
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "social_network/io.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "social_network/traversal.h"

void parse_graph_from_file(const StringBuffer in_file_name, Graph *const graph) {
    FILE *file = fopen(in_file_name, "r");

    if (!file) {
        printf("File %s not found.", in_file_name);

        return;
    }

    StringBuffer in_buff;

    // Presumption: Assume that the input file contents are correct.
    fgets(in_buff, sizeof in_buff, file);  // NOLINT

    int vertex_cnt;

    sscanf(in_buff, "%d", &vertex_cnt);

    initialize_graph(graph, vertex_cnt);

    for (int i = 0; i < vertex_cnt; i++) {
        // Presumption: Assume that the input file contents are correct.
        fgets(in_buff, sizeof in_buff, file);  // NOLINT

        char *adjacent_vertex = strtok(in_buff, WHITESPACE_DELIMITER);
        Vertex vertex;

        strncpy(vertex, adjacent_vertex, MAX_VERTEX_LABEL_LENGTH);

        adjacent_vertex = strtok(NULL, WHITESPACE_DELIMITER);

        while (adjacent_vertex != NULL) {
            if (strncmp(adjacent_vertex, NULL_VERTEX_LABEL, MAX_VERTEX_LABEL_LENGTH) == 0) {
                if (!has_vertex(graph, vertex)) {
                    add_edge(graph, vertex, NULL);
                }

                break;
            }

            add_edge(graph, vertex, adjacent_vertex);

            adjacent_vertex = strtok(NULL, WHITESPACE_DELIMITER);
        }
    }

    fclose(file);

    return;
}

void create_output_file_1(const Graph *const graph, const char graph_name) {
    StringBuffer out_file_name;

    sprintf(out_file_name, "%c-SET.txt", graph_name);

    FILE *out_file = fopen(out_file_name, "w");

    if (!out_file) {
        printf("File %s not found.", out_file_name);

        return;
    }

    fprintf(out_file, "V(%c)={", graph_name);

    for (size_t i = 0; i < graph->vertex_count; i++) {
        fprintf(out_file, "%s", graph->adjacencies_by_vertex[i][0]);

        if (i < graph->vertex_count - 1) {
            fprintf(out_file, ",");
        }
    }

    fprintf(out_file, "}\n");

    fprintf(out_file, "E(%c)={", graph_name);

    size_t graph_edge_cnt = powl(graph->vertex_count, 2);
    GraphEdge graph_edges[graph_edge_cnt];

    get_edges(graph, graph_edges, &graph_edge_cnt);

    for (size_t i = 0; i < graph_edge_cnt; i++) {
        GraphEdge *graph_edge = &graph_edges[i];

        fprintf(out_file, "(%s,%s)", graph_edge->source, graph_edge->destination);

        if (i < graph_edge_cnt - 1) {
            fprintf(out_file, ",");
        }
    }

    fprintf(out_file, "}\n");

    fclose(out_file);
}

void create_output_file_2(const Graph *const graph, const char graph_name) {
    StringBuffer out_file_name;

    sprintf(out_file_name, "%c-DEGREE.txt", graph_name);

    FILE *out_file = fopen(out_file_name, "w");

    if (!out_file) {
        printf("File %s not found.", out_file_name);

        return;
    }

    for (size_t i = 0; i < graph->vertex_count; i++) {
        fprintf(out_file, "%*s %ld\n", -MAX_VERTEX_LABEL_LENGTH, graph->adjacencies_by_vertex[i][0],
                get_adjacency_count(graph->adjacencies_by_vertex[i]));
    }

    fclose(out_file);
}

void create_output_file_3(const Graph *const graph, const char graph_name) {
    StringBuffer out_file_name;

    sprintf(out_file_name, "%c-LIST.txt", graph_name);

    FILE *out_file = fopen(out_file_name, "w");

    if (!out_file) {
        printf("File %s not found.", out_file_name);

        return;
    }

    for (size_t i = 0; i < graph->vertex_count; i++) {
        for (size_t j = 0; j < graph->vertex_count; j++) {
            if (strlen(graph->adjacencies_by_vertex[i][j]) == 0) {
                break;
            }

            fprintf(out_file, "%s->", graph->adjacencies_by_vertex[i][j]);
        }

        fprintf(out_file, "\\\n");
    }

    fclose(out_file);
}

void create_output_file_4(const Graph *const graph, const char graph_name) {
    StringBuffer out_file_name;

    sprintf(out_file_name, "%c-MATRIX.txt", graph_name);

    FILE *out_file = fopen(out_file_name, "w");

    if (!out_file) {
        printf("File %s not found.", out_file_name);

        return;
    }

    fprintf(out_file, "%*s", MAX_VERTEX_LABEL_LENGTH, " ");

    for (size_t i = 0; i < graph->vertex_count; i++) {
        fprintf(out_file, " %s", graph->adjacencies_by_vertex[i][0]);
    }

    fprintf(out_file, "\n");

    for (size_t i = 0; i < graph->vertex_count; i++) {
        fprintf(out_file, "%*s", -MAX_VERTEX_LABEL_LENGTH, graph->adjacencies_by_vertex[i][0]);

        for (size_t j = 0; j < graph->vertex_count; j++) {
            fprintf(out_file, " %*d", -(int)strlen(graph->adjacencies_by_vertex[j][0]),
                    has_adjacency(graph->adjacencies_by_vertex[i], graph->adjacencies_by_vertex[j][0]));
        }

        fprintf(out_file, "\n");
    }

    fclose(out_file);
}

void create_output_file_5(const Graph *const graph, const char graph_name, const Vertex starting_vertex) {
    StringBuffer out_file_name;

    sprintf(out_file_name, "%c-BFS.txt", graph_name);

    FILE *out_file = fopen(out_file_name, "w");

    if (!out_file) {
        printf("File %s not found.", out_file_name);

        return;
    }

    Vertex traversed_vertices[graph->vertex_count];
    size_t traversed_vertex_cnt = 0;

    breadth_first_search(graph, starting_vertex, traversed_vertices, &traversed_vertex_cnt);

    for (size_t i = 0; i < traversed_vertex_cnt; i++) {
        fprintf(out_file, "%s", traversed_vertices[i]);

        fprintf(out_file, i < traversed_vertex_cnt - 1 ? " " : "\n");
    }

    fclose(out_file);
}
