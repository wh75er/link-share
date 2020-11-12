add_library(client STATIC application.src client.cpp request.cpp response.cpp socket.src)
target_include_directories(client PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_definitions(-Wall -Werror -Wpedantic)