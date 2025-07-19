add_library(graph SHARED graph.c)
target_include_directories(graph
  PUBLIC ${HEADER_DIR})

add_library(graph_io SHARED io.c)
target_include_directories(graph
  PUBLIC ${HEADER_DIR})
target_link_libraries(graph_io
                      PRIVATE graph)
