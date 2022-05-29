cmake_minimum_required(VERSION 3.21)
project(ubi_tasks)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME ubi_tasks)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(SOURCES src/main.cpp
        src/crc32.cpp
        src/TasksRunner.cpp
        src/Crc32Task.cpp
           )

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE extern/include
        include)
target_link_directories(${PROJECT_NAME} PRIVATE extern/lib)
target_link_libraries(${PROJECT_NAME} opus opusenc)
