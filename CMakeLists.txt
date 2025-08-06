cmake_minimum_required(VERSION 3.16)

set(APP_NAME log_grinder)
project(${APP_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${APP_NAME}
    src/main.cpp
    src/moneylog.cpp
    src/timer.cpp
    src/draw.cpp
)

target_include_directories(${APP_NAME} PRIVATE
    include
)

target_link_directories(${APP_NAME} PRIVATE
    
)

find_package(fmt REQUIRED)
target_link_libraries(${APP_NAME} PRIVATE
    fmt::fmt
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${APP_NAME} PRIVATE
        -Wall
        -Weffc++
        -Wextra
        -Wconversion
        -Wsign-conversion
        -Werror
    )
elseif (MSVC)
    target_compile_options(${APP_NAME} PRIVATE
        /W4 /WX
    )
endif()
