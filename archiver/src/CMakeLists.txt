set(CMAKE_CXX_FLAGS "-std=c++17 -std=gnu++17 -lstdc++fs")

#add_library(http_client STATIC http_client.cpp)
#target_include_directories(http_client PUBLIC "${PROJECT_SOURCE_DIR}/inc")

#add_library(parser STATIC parser.cpp)
#target_include_directories(parser PUBLIC "${PROJECT_SOURCE_DIR}/inc")

#add_library(create_new_page STATIC create_new_page.cpp)
#target_include_directories(create_new_page PUBLIC "${PROJECT_SOURCE_DIR}/inc")

add_library(http_socket STATIC http_socket.cpp)
target_include_directories(http_socket PUBLIC "${PROJECT_SOURCE_DIR}/inc")

add_library(https_socket STATIC https_socket.cpp)
target_include_directories(https_socket PUBLIC "${PROJECT_SOURCE_DIR}/inc")

target_link_libraries(https_socket http_socket OpenSSL::SSL OpenSSL::Crypto)


#target_link_libraries(create_new_page parser http_client OpenSSL::SSL OpenSSL::Crypto)

#add_definitions(-Wall -Werror -Wpedantic )

#add_definitions(-Wreturn-type)


#add_executable(my_main my_main.cpp)

#target_link_libraries(my_main PUBLIC https_socket)
