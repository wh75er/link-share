add_library(http_client SHARED http_client.cpp)
target_include_directories(http_client PUBLIC "${PROJECT_SOURCE_DIR}/inc")

add_library(parser SHARED parser.cpp)
target_include_directories(parser PUBLIC "${PROJECT_SOURCE_DIR}/inc")

add_library(create_new_page SHARED create_new_page.cpp)
target_include_directories(create_new_page PUBLIC "${PROJECT_SOURCE_DIR}/inc")

add_definitions(-Wall -Werror -Wpedantic -lssl -lcrypto)

