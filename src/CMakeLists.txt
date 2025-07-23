set(project_include_dir "${PROJECT_SOURCE_DIR}/include")
set(project_header_dir "${project_include_dir}/social_network")

add_library(graph STATIC
  graph.c
  "${project_header_dir}/graph.h"
  traversal.c
  "${project_header_dir}/traversal.h"
  queue.c
  "${project_header_dir}/queue.h")
target_include_directories(graph
  PUBLIC ${project_include_dir}
)

add_library(graph_io STATIC io.c "${project_header_dir}/io.h")
target_include_directories(graph
  PUBLIC ${project_include_dir}
)
target_link_libraries(graph_io
  PRIVATE graph
)

file(GLOB header_files CONFIGURE_DEPENDS "${project_header_dir}/*.h")

source_group(
  TREE ${project_include_dir}
  PREFIX "Header Files"
  FILES ${header_files}
)
