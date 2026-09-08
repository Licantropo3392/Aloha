cmake_minimum_required(VERSION 4.2)
set(CMAKE_CXX_STANDARD 20)

project(Aloha)

include(FetchContent)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist CACHE PATH "Install path" FORCE)
endif()

if(NINTENDO_WIIU)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/wiiu)
else()
    set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/pc)
endif()

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/Shader.cpp
        ${CMAKE_SOURCE_DIR}/src/Shader.h
        ${CMAKE_SOURCE_DIR}/src/tests/Camera.h
        ${CMAKE_SOURCE_DIR}/src/MVP.h
        ${CMAKE_SOURCE_DIR}/src/VertexBufferObject.cpp
        ${CMAKE_SOURCE_DIR}/src/VertexBufferObject.h
        ${CMAKE_SOURCE_DIR}/src/ElementBufferObject.cpp
        ${CMAKE_SOURCE_DIR}/src/ElementBufferObject.h
        ${CMAKE_SOURCE_DIR}/src/VertexArrayObject.cpp
        ${CMAKE_SOURCE_DIR}/src/VertexArrayObject.h
        ${CMAKE_SOURCE_DIR}/src/VertexBufferLayout.h
        ${CMAKE_SOURCE_DIR}/src/UniformBufferObject.cpp
        ${CMAKE_SOURCE_DIR}/src/UniformBufferObject.h
        ${CMAKE_SOURCE_DIR}/src/glDebug.h
        ${CMAKE_SOURCE_DIR}/src/Renderer.cpp
        ${CMAKE_SOURCE_DIR}/src/Renderer.h
        ${CMAKE_SOURCE_DIR}/src/Window.cpp
        ${CMAKE_SOURCE_DIR}/src/Window.h
        ${CMAKE_SOURCE_DIR}/third_party/stb_image/stb_image.cpp
        ${CMAKE_SOURCE_DIR}/src/Texture.cpp
        ${CMAKE_SOURCE_DIR}/src/Texture.h
        src/ImGuiLayer.cpp
        src/ImGuiLayer.h
        src/Test.h
        src/tests/ClearColor.cpp
        src/tests/ClearColor.h
        src/Test.cpp
        src/tests/Boxes.cpp
        src/tests/Boxes.h
        src/tests/Phong.cpp
        src/tests/Phong.h
)

FetchContent_Declare(
        glm
        GIT_REPOSITORY  https://github.com/g-truc/glm.git
        GIT_TAG 	    1.0.3
)
FetchContent_MakeAvailable(glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY	https://github.com/ocornut/imgui.git
        GIT_TAG 	    v1.92.9b-docking
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp

        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

if(UNIX)
    target_link_libraries(imgui PUBLIC
            glfw
            fontconfig
    )
elseif(WIN32)
    target_link_libraries(imgui PUBLIC
        glfw
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE imgui)

FetchContent_Declare(
        Tracy
        GIT_REPOSITORY  https://github.com/wolfpld/tracy.git
        GIT_TAG         v0.14.1
)
FetchContent_MakeAvailable(Tracy)
target_link_libraries(${PROJECT_NAME} PRIVATE Tracy::TracyClient)

set(TRACY_ENABLE ON CACHE BOOL "Tracy Profiler" FORCE)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

if(NINTENDO_WIIU)
    target_compile_definitions(${PROJECT_NAME} PUBLIC __WIIU__)
    wut_create_rpx(${PROJECT_NAME})

    wut_create_wuhb(${PROJECT_NAME}
            CONTENT     ${CMAKE_SOURCE_DIR}/assets
            NAME        "TEST"
            SHORTNAME   "TEST"
            AUTHOR      "TEST"
            # ICON
            # TVSPLASH
            # DRCSPLASH
    )
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC __PC__)

    target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/glad/src/glad.c)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/glad/include)

    FetchContent_Declare(
            glfw
            GIT_REPOSITORY	https://github.com/glfw/glfw.git
            GIT_TAG 	3.5.1
    )
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    # set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(glfw)

    target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

    if(MINGW)
        target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
    endif()
endif()

if(NINTENDO_WIIU)
    install(
            FILES   "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rpx"
                    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.wuhb"
            DESTINATION "."
    )
else()
    install(
            TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION "."
    )

    install(
            DIRECTORY "${CMAKE_SOURCE_DIR}/assets"
            DESTINATION "."
    )
endif()

if(WIN32)
    add_custom_target(run_install ALL
            COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --config $<CONFIG>
            DEPENDS ${PROJECT_NAME}
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES
            VS_DEBUGGER_COMMAND ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.exe
            VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
    )
endif()