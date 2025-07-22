#ifndef SOCIAL_NETWORK_IO_H_
#define SOCIAL_NETWORK_IO_H_

#include "graph.h"

#define BUFFER_SIZE 32

#define WHITESPACE_DELIMITER " \f\n\r\t\v"

#define NULL_VERTEX_LABEL "-1"

typedef char StringBuffer[BUFFER_SIZE + 1];

void parse_graph_from_file(const char input_file_name[], Graph *const graph);

void create_output_file_1(const Graph *const graph, const char graph_name);

void create_output_file_2(const Graph *const graph, const char graph_name);

void create_output_file_3(const Graph *const graph, const char graph_name);

void create_output_file_4(const Graph *const graph, const char graph_name);

#endif  // SOCIAL_NETWORK_IO_H_
