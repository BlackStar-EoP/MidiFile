cmake_minimum_required(VERSION 4.0)

project(MidiFile CXX)

if(PROJECT_IS_TOP_LEVEL)
  add_definitions(-g2 -Wall -Wextra -Werror)
endif()

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} PUBLIC
  FILE_SET HEADERS
    BASE_DIRS
      MidiFile
)

add_executable(${PROJECT_NAME}Test EXCLUDE_FROM_ALL
  main.cpp
)

target_link_libraries(${PROJECT_NAME}Test
  PRIVATE
    ${PROJECT_NAME}
)
