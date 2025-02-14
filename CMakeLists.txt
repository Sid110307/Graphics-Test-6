cmake_minimum_required(VERSION 3.20)
project(GraphicsTest6)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    set(CMAKE_CXX_FLAGS "/W4 /EHsc")
else ()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(graphicsTest6
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/shape.cpp
)
target_link_libraries(graphicsTest6 PUBLIC gdiplus)
