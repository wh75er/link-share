add_executable(main main.cpp)
include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(client STATIC utils.cpp client.cpp view.cpp socket.cpp link.cpp room.cpp userinfo.cpp)
target_include_directories(client PUBLIC "${PROJECT_SOURCE_DIR}/include")

find_package(Boost REQUIRED COMPONENTS system thread)
message(STATUS "Boost version: ${Boost_VERSION}")
target_link_libraries(main PUBLIC ${Boost_LIBRARIES} PUBLIC client)

add_definitions(-Wall -Werror -Wpedantic)
