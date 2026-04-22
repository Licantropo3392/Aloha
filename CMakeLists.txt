cmake_minimum_required(VERSION 3.13) # Catnip requires >= 3.13

project(Aloha LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} STATIC
    ${PROJECT_SOURCE_DIR}/src/platform_raylib.cpp
    ${PROJECT_SOURCE_DIR}/src/platform-citro3d.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

find_package(raylib REQUIRED)

if(RAYLIB_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
else()
    message(ERROR "Raylib not found. Please install Raylib.")
endif()
