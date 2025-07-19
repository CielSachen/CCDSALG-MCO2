#ifndef SOCIAL_NETWORK_IO_H_
#define SOCIAL_NETWORK_IO_H_

#include "graph.h"

#define INPUT_BUFFER_SIZE 32

#define WHITESPACE_DELIMITER " \f\n\r\t\v"

#define NULL_VERTEX_LABEL "-1"

Graph *parse_graph_from_file(const char input_file_name[]);

#endif  // SOCIAL_NETWORK_IO_H_
