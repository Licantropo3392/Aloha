cmake_minimum_required(VERSION 3.13) # Catnip requires >= 3.13

project(Aloha LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} STATIC)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(NINTENDO_3DS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC __3DS__)
    target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/platform-citro3d.cpp)
    target_link_libraries(${PROJECT_NAME} PUBLIC citro2d citro3d)
else()
    target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/platform_raylib.cpp)
    find_package(raylib REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
endif()
