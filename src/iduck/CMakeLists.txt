add_library(iduck STATIC "")

target_sources(
  iduck
  PRIVATE
  iduck.cpp)

include(GNUInstallDirs)

target_include_directories(iduck PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_LOWER_PROJECT_NAME}>  # <prefix>/include/iduck
  )

install(
  TARGETS iduck
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
add_executable(iduck_test "")

target_sources(
  iduck_test
  PRIVATE
  iduck_test.m.cpp
  iduck.t.cpp
  iduck_hiddenduck.cpp)

target_link_libraries(iduck_test iduck)
target_link_libraries(iduck_test Catch2WithMain)


#find_package(Catch2 REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(iduck_test)

## Benchmarks
add_executable(iduck_benchmark "")
target_sources(
  iduck_benchmark
  PRIVATE
  iduck.b.cpp
  iduck_hiddenduck.cpp
  )
target_link_libraries(iduck_benchmark iduck)
target_link_libraries(iduck_benchmark benchmark)
add_test(benchmark iduck_benchmark --benchmark_min_time=0.01)
