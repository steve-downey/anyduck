add_library(tepsduck STATIC "")

target_sources(
  tepsduck
  PRIVATE
  tepsduck.cpp)

include(GNUInstallDirs)

target_include_directories(tepsduck PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_LOWER_PROJECT_NAME}>  # <prefix>/include/tepsduck
  )

install(
  TARGETS tepsduck
  EXPORT ${TARGETS_EXPORT_NAME}
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

string(TOLOWER ${CMAKE_PROJECT_NAME} CMAKE_LOWER_PROJECT_NAME)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_LOWER_PROJECT_NAME}
  FILES_MATCHING PATTERN "*.h"
  )


## Tests
add_executable(tepsduck_test "")

target_sources(
  tepsduck_test
  PRIVATE
  tepsduck_test.m.cpp
  tepsduck.t.cpp
  tepsduck_hiddenduck.cpp)

target_link_libraries(tepsduck_test tepsduck)
target_link_libraries(tepsduck_test Catch2)


find_package(Catch2 REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Catch2_SOURCE_DIR}/contrib)
include(CTest)
include(Catch)
catch_discover_tests(tepsduck_test)

## Benchmarks
add_executable(tepsduck_benchmark "")
target_sources(
  tepsduck_benchmark
  PRIVATE
  tepsduck.b.cpp
  tepsduck_hiddenduck.cpp
  )
target_link_libraries(tepsduck_benchmark tepsduck)
target_link_libraries(tepsduck_benchmark benchmark)
add_test(benchmark tepsduck_benchmark --benchmark_min_time=0.01)
