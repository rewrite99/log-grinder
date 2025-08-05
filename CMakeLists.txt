cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME MyProject)
project(${TARGET_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${TARGET_NAME}
    src/main.cpp
    src/monitor_log.cpp
    src/timer.cpp
    src/draw.cpp
)

target_include_directories(${TARGET_NAME} PRIVATE
    include
)

target_link_directories(${TARGET_NAME} PRIVATE
    
)

find_package(fmt REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE
    fmt::fmt
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${TARGET_NAME} PRIVATE
        -Wall
        -Weffc++
        -Wextra
        -Wconversion
        -Wsign-conversion
        -Werror
    )
elseif (MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE
        /W4 /WX
    )
endif()
