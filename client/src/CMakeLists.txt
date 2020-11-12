add_library(client STATIC application.cpp client.cpp request.cpp response.cpp socket.cpp)
target_include_directories(client PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_definitions(-Wall -Werror -Wpedantic)