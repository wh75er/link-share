add_library(http_client http_client.cpp)
add_library(parser parser.cpp)
add_library(create_new_page create_new_page.cpp)

target_include_directories(http_client PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(parser PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(create_new_page PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_definitions(-Wall -Werror -Wpedantic -lssl -lcrypto)

