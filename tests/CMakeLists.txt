FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

enable_testing()

add_executable(graph_test graph_test.cpp)
target_link_libraries(graph_test
  PRIVATE graph
  PUBLIC GTest::gtest_main
)
gtest_discover_tests(graph_test)

add_executable(queue_test queue_test.cpp)
target_link_libraries(queue_test
  PRIVATE graph
  PUBLIC GTest::gtest_main
)
gtest_discover_tests(queue_test)
