cmake_minimum_required(VERSION 3.11)

project(link-share VERSION 0.1
  DESCRIPTION "link-share"
  LANGUAGES C CXX)

set(SCRAPER_INCLUDE_DIR
        ${PROJECT_SOURCE_DIR}/archiver/inc/
        )

add_subdirectory(archiver)
add_subdirectory(server)
