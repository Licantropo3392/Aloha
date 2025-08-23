cmake_minimum_required(VERSION 3.13) # Catnip richiede >= 3.13

project(Aloha2D LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/LuaUtilities.cpp
    ${CMAKE_SOURCE_DIR}/src/LuaDraw.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include
)

if(NOT __3DS__ AND NOT __SWITCH__)
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/lua/include
        ${CMAKE_SOURCE_DIR}/lib/raylib/include
    )

    target_link_libraries(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/lib/lua/liblua54.a
        ${CMAKE_SOURCE_DIR}/lib/raylib/lib/libraylib.a
    )
endif()

if(__3DS__)
    target_include_directories(${PROJECT_NAME} PRIVATE ${DEVKITPRO}/libctru/include)
    target_link_directories(${PROJECT_NAME} PRIVATE ${DEVKITPRO}/libctru/lib)
    target_link_libraries(${PROJECT_NAME} ctru)
endif()

if(__SWITCH__)
    message(STATUS "Compilazione per Switch")
    target_include_directories(${PROJECT_NAME} PRIVATE ${DEVKITPRO}/libnx/include)
    target_link_directories(${PROJECT_NAME} PRIVATE ${DEVKITPRO}/libnx/lib)
    target_link_libraries(${PROJECT_NAME} nx)
endif()
