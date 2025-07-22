#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "social_network/io.h"

int main(void) {
    // THIS WILL SIMPLY PRINT OUT THE CREATED ADJACENCY LIST TO VERIFY IF IT'S CORRECT
    const char test_files[4][BUFFER_SIZE] = {"../specs/input-files/A.txt", "../specs/input-files/G.txt",
                                             "../specs/input-files/Y.txt", "../specs/input-files/Z.txt"};

    for (size_t i = 0; i < 4; i++) {
        const char *const file_path = test_files[i];

        Graph graph;
        const char graph_name = test_files[i][21];

        parse_graph_from_file(file_path, &graph);

        {
            Graph sorted_graph;

            clone(&graph, &sorted_graph);

            sort_adjacencies(&sorted_graph);

            create_output_file_1(&sorted_graph, graph_name);

            create_output_file_2(&sorted_graph, graph_name);
        }

        create_output_file_3(&graph, graph_name);

        create_output_file_4(&graph, graph_name);
    }

    return 0;
}
