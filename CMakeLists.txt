cmake_minimum_required(VERSION 4.0)

project(MidiFile CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} PUBLIC
  FILE_SET HEADERS
    BASE_DIRS
      MidiFile
)
