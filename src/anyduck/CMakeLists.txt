add_library(anyduck STATIC "")

target_sources(
  anyduck
  PRIVATE
  anyduck.cpp)

include(GNUInstallDirs)

target_include_directories(anyduck PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_LOWER_PROJECT_NAME}>  # <prefix>/include/anyduck
  )

install(
  TARGETS anyduck
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
add_executable(anyduck_test "")

target_sources(
  anyduck_test
  PRIVATE
  anyduck.t.cpp)

target_link_libraries(anyduck_test anyduck)
target_link_libraries(anyduck_test gtest)
target_link_libraries(anyduck_test gtest_main)

include(GoogleTest)
gtest_discover_tests(anyduck_test)
