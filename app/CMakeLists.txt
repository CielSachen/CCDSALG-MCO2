add_executable(social_network main.c utils.c utils.h)
target_link_libraries(social_network
  PRIVATE graph
  PRIVATE graph_io
)

add_executable(social_network_bonus 28-BONUS.c utils.c utils.h)
target_link_libraries(social_network_bonus
  PRIVATE graph
  PRIVATE graph_io
)
