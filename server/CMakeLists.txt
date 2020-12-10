cmake_minimum_required(VERSION 3.11)

project(TCPserver VERSION 0.1
  DESCRIPTION "TCPserver"
  LANGUAGES C CXX)

find_package(Boost REQUIRED COMPONENTS system thread)
message(STATUS "Boost version: ${Boost_VERSION}")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
set(PROJECT_BUILD_DIR ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic")

option(USE_DEBUG "Enter debug mode" OFF)
if (USE_DEBUG)
  add_definitions(-DDEBUG)
endif()

# Code coverage
if (CMAKE_BUILD_TYPE MATCHES Debug)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  setup_target_for_coverage_gcovr_html(
    NAME coverage
    EXECUTABLE valgrind --leak-check=full --show-leak-kinds=all ctest -V
    BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
    EXCLUDE "${PROJECT_SOURCE_DIR}/build/*" 
    "${PROJECT_SOURCE_DIR}/tests/*")
endif()


file(GLOB_RECURSE lib_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)


add_library(${CMAKE_PROJECT_NAME}_lib SHARED ${lib_sources})

target_link_libraries(${CMAKE_PROJECT_NAME}_lib PUBLIC ${Boost_LIBRARIES})

target_include_directories(${CMAKE_PROJECT_NAME}_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main ${Boost_LIBRARIES} ${CMAKE_PROJECT_NAME}_lib)


enable_testing()

add_subdirectory(tests)
