cmake_minimum_required(VERSION 3.22)

project(FirstWindow)

# set command specifies project-wide variables or options.
# set(PROJECT_DIR ${CMAKE_SOURCE_DIR}) keeps the path to the folder where the project is located
set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_SOURCES
            ${PROJECT_SOURCE_DIR}/main.cpp 
            ${PROJECT_SOURCE_DIR}/glad.c )

include_directories(${PROJECT_INCLUDE_DIR})

find_package(glfw3 3.2 REQUIRED)

find_package(glm REQUIRED)
 
include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw)