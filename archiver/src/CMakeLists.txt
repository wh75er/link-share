find_package(OpenSSL REQUIRED)


add_library(http_client STATIC http_client.cpp)
target_include_directories(http_client PUBLIC "${PROJECT_SOURCE_DIR}/inc")

add_library(parser STATIC parser.cpp)
target_include_directories(parser PUBLIC "${PROJECT_SOURCE_DIR}/inc")

add_library(create_new_page STATIC create_new_page.cpp)
target_include_directories(create_new_page PUBLIC "${PROJECT_SOURCE_DIR}/inc")

#add_definitions(-Wall -Werror -Wpedantic )

#add_definitions(-Wreturn-type)


add_executable(main main.cpp)

target_link_libraries(main PUBLIC http_client parser create_new_page OpenSSL::SSL OpenSSL::Crypto)
