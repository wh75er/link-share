add_executable(main main.cpp)
include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(client STATIC model.cpp client.cpp requestManager.cpp requestHandler.cpp presenter.cpp view.cpp socket.cpp link.cpp room.cpp userinfo.cpp)
target_include_directories(client PUBLIC "${PROJECT_SOURCE_DIR}/include")


target_link_libraries(main PUBLIC client)

add_definitions(-Wall -Werror -Wpedantic)