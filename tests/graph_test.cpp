#include "social_network/graph.h"

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>

TEST(InitializeGraph, SetsAllIntegerFieldsToZero) {
    Graph graph;
    std::size_t vertex_cnt = 4;

    initialize_graph(&graph, vertex_cnt);

    EXPECT_EQ(graph.vertex_count, vertex_cnt);
    EXPECT_EQ(graph.adjacencies_length, 0);
}

TEST(InitializeGraph, SetsVerticesToEmptyStrings) {
    Graph graph;
    std::size_t vertex_cnt = 4;

    initialize_graph(&graph, vertex_cnt);

    for (std::size_t i = 0; i < MAX_GRAPH_VERTEX_COUNT; i++) {
        for (std::size_t j = 0; j < MAX_GRAPH_VERTEX_COUNT; j++) {
            EXPECT_TRUE(std::strlen(graph.adjacencies_by_vertex[i][j]) == 0);
        }
    }
}

TEST(CloneGraph, ClonesAllFields) {
    Graph graph;
    std::size_t vertex_cnt = 4;

    initialize_graph(&graph, vertex_cnt);

    add_adjacency(&graph, "Test1", "Test2");
    add_adjacency(&graph, "Test1", "Test3");
    add_adjacency(&graph, "Test2", "Test1");
    add_adjacency(&graph, "Test3", "Test1");
    add_adjacency(&graph, "Test4", NULL);

    Graph cloned_graph;

    clone_graph(&graph, &cloned_graph);

    EXPECT_EQ(cloned_graph.vertex_count, graph.vertex_count);
    EXPECT_EQ(cloned_graph.adjacencies_length, graph.adjacencies_length);

    for (std::size_t i = 0; i < graph.vertex_count; i++) {
        for (std::size_t j = 0; j < MAX_GRAPH_VERTEX_COUNT; j++) {
            EXPECT_TRUE(std::strncmp(graph.adjacencies_by_vertex[i][j], cloned_graph.adjacencies_by_vertex[i][j],
                                     MAX_VERTEX_LABEL_LENGTH) == 0);
        }
    }
}
