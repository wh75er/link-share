include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

FetchContent_MakeAvailable(googletest)

set(LIBS ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)

file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/*.cpp")

foreach(file ${tests})
  set(name)

  get_filename_component(name ${file} NAME_WE)

  add_executable("${name}_tests"
    ${sources}
    ${file})

  target_link_libraries("${name}_tests" ${LIBS})

  target_include_directories("${name}_tests" ${CMAKE_SOURCE_DIR}/include)

  add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()
