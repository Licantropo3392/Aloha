cmake_minimum_required(VERSION 3.31)

project(Aloha LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ALOHA_PLATFORM "PC" CACHE STRING "Target platform (PC or WIIU)")
set_property(CACHE ALOHA_PLATFORM PROPERTY STRINGS PC WIIU)
set(ALOHA_GRAPHICS_API "OPENGL" CACHE STRING "Graphics API (OPENGL or GX2)")
set_property(CACHE ALOHA_GRAPHICS_API PROPERTY STRINGS OPENGL GX2)

string(TOUPPER "${ALOHA_PLATFORM}" ALOHA_PLATFORM)
string(TOUPPER "${ALOHA_GRAPHICS_API}" ALOHA_GRAPHICS_API)

if(ALOHA_PLATFORM STREQUAL "WIIU")
    if(NOT ALOHA_GRAPHICS_API STREQUAL "GX2")
        message(FATAL_ERROR "Wii U supports GX2 only; received ${ALOHA_GRAPHICS_API}.")
    endif()
    message(FATAL_ERROR
        "The Wii U/GX2 target is not implemented yet. Its platform and graphics "
        "backend sources must be added before this target can be enabled.")
elseif(ALOHA_PLATFORM STREQUAL "PC")
    if(NOT ALOHA_GRAPHICS_API STREQUAL "OPENGL")
        message(FATAL_ERROR "The PC target currently supports OpenGL only; received ${ALOHA_GRAPHICS_API}.")
    endif()
else()
    message(FATAL_ERROR
        "Unsupported target platform: ${ALOHA_PLATFORM}. Supported platforms: PC, WIIU.")
endif()

string(TOLOWER "${ALOHA_PLATFORM}" ALOHA_PLATFORM_INSTALL_DIR)
set(ALOHA_DEFAULT_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist")
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT OR CMAKE_INSTALL_PREFIX STREQUAL ALOHA_DEFAULT_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist/${ALOHA_PLATFORM_INSTALL_DIR}" CACHE PATH "Install path" FORCE)
endif()

include(FetchContent)

option(ALOHA_ENABLE_TRACY "Build Aloha with Tracy profiling support" ON)
if(ALOHA_ENABLE_TRACY)
    set(TRACY_ENABLE ON CACHE BOOL "Enable Tracy profiling" FORCE)
    FetchContent_Declare(
        Tracy
        EXCLUDE_FROM_ALL
        GIT_REPOSITORY https://github.com/wolfpld/tracy.git
        GIT_TAG v0.14.1
    )
    FetchContent_MakeAvailable(Tracy)
endif()

set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.5.1
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.9b-docking
)
FetchContent_MakeAvailable(imgui)

add_library(aloha_imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)
target_include_directories(aloha_imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
set(ALOHA_COMMON_SOURCES
    src/main.cpp
    src/Test.cpp
    src/tests/ClearColor.cpp
    src/tests/Boxes.cpp
    src/tests/Phong.cpp
    third_party/stb_image/stb_image.cpp
)

set(ALOHA_PLATFORM_SOURCES)
set(ALOHA_GRAPHICS_BACKEND_SOURCES)
set(ALOHA_GRAPHICS_DEPENDENCIES)
set(ALOHA_PLATFORM_INCLUDE_DIRECTORIES)

if(ALOHA_PLATFORM STREQUAL "PC" AND ALOHA_GRAPHICS_API STREQUAL "OPENGL")
    list(APPEND ALOHA_PLATFORM_SOURCES
        src/Window.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    )
    list(APPEND ALOHA_GRAPHICS_BACKEND_SOURCES
        src/platform/pc/opengl/Renderer.cpp
        src/platform/pc/opengl/Shader.cpp
        src/platform/pc/opengl/Texture.cpp
        src/platform/pc/opengl/VertexArrayObject.cpp
        src/platform/pc/opengl/VertexBufferObject.cpp
        src/platform/pc/opengl/ElementBufferObject.cpp
        src/platform/pc/opengl/UniformBufferObject.cpp
        src/platform/pc/opengl/GLObjects.h
        src/platform/pc/opengl/ImGuiLayer.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        third_party/glad/src/glad.c
    )
    list(APPEND ALOHA_GRAPHICS_DEPENDENCIES glfw)
    list(APPEND ALOHA_PLATFORM_INCLUDE_DIRECTORIES
        third_party/glad/include
        src/platform/pc/opengl
    )
    target_link_libraries(aloha_imgui PUBLIC glfw)

    if(UNIX AND NOT APPLE)
        target_link_libraries(aloha_imgui PUBLIC fontconfig)
    endif()
endif()

add_executable(Aloha
    ${ALOHA_COMMON_SOURCES}
    ${ALOHA_PLATFORM_SOURCES}
    ${ALOHA_GRAPHICS_BACKEND_SOURCES}
)

target_include_directories(Aloha PRIVATE
    src
    third_party
    ${ALOHA_PLATFORM_INCLUDE_DIRECTORIES}
)
target_compile_definitions(Aloha PRIVATE
    GLFW_INCLUDE_NONE
    ALOHA_PLATFORM_PC=1
    ALOHA_GRAPHICS_OPENGL=1
)
target_link_libraries(Aloha PRIVATE
    glm::glm
    aloha_imgui
    ${ALOHA_GRAPHICS_DEPENDENCIES}
)

if(ALOHA_ENABLE_TRACY)
    target_link_libraries(Aloha PRIVATE Tracy::TracyClient)
endif()

if(MINGW)
    target_link_options(Aloha PRIVATE -static)
endif()

if(ALOHA_PLATFORM STREQUAL "WIIU")
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/Aloha.rpx"
        "${CMAKE_CURRENT_BINARY_DIR}/Aloha.wuhb"
        DESTINATION .
    )
else()
    install(TARGETS Aloha
        RUNTIME DESTINATION .
    )
endif()
install(DIRECTORY assets
    DESTINATION .
)

add_custom_target(run_install ALL
    COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --config $<CONFIG>
    DEPENDS Aloha
)

if(WIN32)
    set_target_properties(Aloha PROPERTIES
        VS_DEBUGGER_COMMAND "${CMAKE_INSTALL_PREFIX}/Aloha.exe"
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}"
    )
endif()

message(STATUS "Aloha target: ${ALOHA_PLATFORM}/${ALOHA_GRAPHICS_API}")
