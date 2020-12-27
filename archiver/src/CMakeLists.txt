set(CMAKE_CXX_FLAGS "-std=c++17 -std=gnu++17 -lstdc++fs")

message("Variable is : ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(parser STATIC parser.cpp)
target_include_directories(parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../inc")

add_library(http_socket STATIC http_socket.cpp)
target_include_directories(http_socket PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../inc")

add_library(https_socket STATIC https_socket.cpp)
target_include_directories(https_socket PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../inc")

add_library(create_new_page STATIC create_new_page.cpp)
target_include_directories(create_new_page PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../inc")

target_link_libraries(create_new_page PUBLIC https_socket parser)

target_link_libraries(https_socket http_socket OpenSSL::SSL OpenSSL::Crypto)

#add_executable(main main.cpp)

#target_link_libraries(main PUBLIC create_new_page)
