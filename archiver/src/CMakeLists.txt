set(CMAKE_CXX_FLAGS "-std=c++17 -std=gnu++17 -lstdc++fs")

add_library(http_client STATIC http_client.cpp)
target_include_directories(http_client PUBLIC "${PROJECT_SOURCE_DIR}/inc")

add_library(parser STATIC parser.cpp)
target_include_directories(parser PUBLIC "${PROJECT_SOURCE_DIR}/inc")

add_library(create_new_page STATIC create_new_page.cpp)
target_include_directories(create_new_page PUBLIC "${PROJECT_SOURCE_DIR}/inc")

target_link_libraries(create_new_page parser http_client OpenSSL::SSL OpenSSL::Crypto)

#add_definitions(-Wall -Werror -Wpedantic )

add_definitions(-Wreturn-type)


add_executable(main main.cpp)

target_link_libraries(main PUBLIC create_new_page)
