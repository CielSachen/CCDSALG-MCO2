add_executable(social_network main.c utils.c utils.h)
target_include_directories(social_network
  PRIVATE ${HEADER_DIR})
target_link_libraries(social_network
                      PRIVATE graph
                      PRIVATE graph_io)

