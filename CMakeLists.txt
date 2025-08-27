cmake_minimum_required(VERSION 3.13) # Catnip richiede >= 3.13

project(Aloha2D LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/LuaUtilities.cpp
    ${CMAKE_SOURCE_DIR}/src/LuaDraw.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/include)

find_package(PkgConfig REQUIRED)

pkg_check_modules(LUA QUIET IMPORTED_TARGET lua5.1)
if (NOT LUA_FOUND) # Fedora breaks compatibility
    pkg_check_modules(LUA QUIET IMPORTED_TARGET lua-5.1)
endif()

if (LUA_FOUND)
    message(STATUS "LUA_INCLUDE_DIRS: ${LUA_INCLUDE_DIRS}")
    message(STATUS "LUA_LIBRARIES: ${LUA_LIBRARIES}")

    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::LUA)
else ()
    message(STATUS "Lua 5.1 not found. Compiling Lua from source as a static library.")

    add_library(LUA STATIC
        ${CMAKE_SOURCE_DIR}/lib/lua/lapi.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lauxlib.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lbaselib.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lcode.c
        ${CMAKE_SOURCE_DIR}/lib/lua/ldebug.c
        ${CMAKE_SOURCE_DIR}/lib/lua/ldblib.c
        ${CMAKE_SOURCE_DIR}/lib/lua/ldo.c
        ${CMAKE_SOURCE_DIR}/lib/lua/ldump.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lfunc.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lgc.c
        ${CMAKE_SOURCE_DIR}/lib/lua/linit.c
        ${CMAKE_SOURCE_DIR}/lib/lua/liolib.c
        ${CMAKE_SOURCE_DIR}/lib/lua/llex.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lmathlib.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lmem.c
        ${CMAKE_SOURCE_DIR}/lib/lua/loadlib.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lobject.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lopcodes.c
        ${CMAKE_SOURCE_DIR}/lib/lua/loslib.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lparser.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lstate.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lstring.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lstrlib.c
        ${CMAKE_SOURCE_DIR}/lib/lua/ltable.c
        ${CMAKE_SOURCE_DIR}/lib/lua/ltablib.c
        ${CMAKE_SOURCE_DIR}/lib/lua/ltm.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lua.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lundump.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lvm.c
        ${CMAKE_SOURCE_DIR}/lib/lua/lzio.c
    )

    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/lua/include)
    target_link_libraries(${PROJECT_NAME} PRIVATE LUA)
endif()

if(NINTENDO_3DS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        __CONSOLE__="3DS" __OS__="Horizon"
    )

    # Generate a SMDH file for the executable
    ctr_generate_smdh(${PROJECT_NAME}.smdh
        NAME        "${PROJECT_NAME}"
        # DESCRIPTION "LÖVE for 3DS • ${APP_VERSION}"
        # AUTHOR      "${APP_AUTHOR}"
        # ICON        ${APP_ICON}
    )

    # Specify that the executable is a 3DSX file
    ctr_create_3dsx(${PROJECT_NAME}
        SMDH  ${PROJECT_NAME}.smdh
        ROMFS ${CMAKE_SOURCE_DIR}/romfs
    )

    # target_include_directories(${PROJECT_NAME} PRIVATE ${DEVKITPRO}/libctru/include)
    # target_link_directories(${PROJECT_NAME} PRIVATE ${DEVKITPRO}/libctru/lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE citro2d citro3d)
else()
    pkg_check_modules(RAYLIB QUIET IMPORTED_TARGET raylib)

    if(NOT RAYLIB_FOUND)
        message(FATAL_ERROR "Raylib not found. Please install the development package.")
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::RAYLIB)
endif()
