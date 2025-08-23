cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Aloha2D)
add_executable(Aloha2D
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/LuaUtilities.cpp
    ${CMAKE_SOURCE_DIR}/src/LuaDraw.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/lib/lua/include
    ${CMAKE_SOURCE_DIR}/lib/raylib/include
)

target_link_libraries(Aloha2D
    ${CMAKE_SOURCE_DIR}/lib/lua/liblua54.a
    ${CMAKE_SOURCE_DIR}/lib/raylib/lib/libraylib.a
)