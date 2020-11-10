set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)

################################
# GTest
################################

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include_directories("${PROJECT_SOURCE_DIR}/inc")

file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")

add_definitions(-Wall -Werror -Wpedantic)

foreach(file ${tests})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests"
    ${sources}
    ${file}
    "${PROJECT_SOURCE_DIR}/test/main.cpp")
  target_link_libraries("${name}_tests" gtest gtest_main)
  add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()

add_definitions(-fprofile-arcs -ftest-coverage)

add_custom_target(gcov
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test
)
add_custom_command(TARGET gcov
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/gcoverage
)

add_custom_target(lcov
    COMMAND mkdir -p lcoverage
    )
add_custom_command(TARGET lcov
    COMMAND cd ${CMAKE_BINARY_DIR}/test
    COMMAND lcov --capture --directory ${CMAKE_BINARY_DIR}/test/CMakeFiles/ --output-file lcoverage/main_coverage.info
    COMMAND lcov --remove lcoverage/main_coverage.info '/usr/*' --output-file lcoverage/main_coverage.info
    COMMAND lcov --remove lcoverage/main_coverage.info '${CMAKE_BINARY_DIR}/_deps/*' --output-file lcoverage/main_coverage.info
    COMMAND genhtml lcoverage/main_coverage.info --output-directory lcoverage
)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES gcoverage)

target_link_libraries(gtest_main -fprofile-arcs)