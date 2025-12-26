cmake_minimum_required(VERSION 4.2)

project(
    "Aerell Studio"
    VERSION 0.0.0
    LANGUAGES C CXX
)

# C Standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type (Debug or Release)" FORCE)
endif()

# Set sanitizer flags
set(SANITIZER_FLAGS "-fsanitize=address -fsanitize=undefined -fsanitize-address-use-after-scope")

# Set debug flags
set(DEBUG_FLAGS "-g -O0 -Wall -Werror -Wextra -fno-omit-frame-pointer ${SANITIZER_FLAGS}")

# Set release flags
set(RELEASE_FLAGS "-static -O3 -march=native -mtune=native -flto -funroll-loops -fomit-frame-pointer -ffast-math -finline-functions -fdata-sections -ffunction-sections -Os -DNDEBUG -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -g0")

# Flags for Debug
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_FLAGS}")

# Flags for Release
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${RELEASE_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${RELEASE_FLAGS}")

# Linker flags Release - strip and garbage collection
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s -Wl,--gc-sections -Wl,--strip-all -Wl,--as-needed")

# Optimasi interprocedural (LTO)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

# CCACHE
find_program(CCACHE_PROGRAM "ccache")
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
endif()

# Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Aerell Studio
set("AERELL_STUDIO" "astudio")

file(
    GLOB_RECURSE
    "AERELL_STUDIO_SRC_FILES"
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
)

add_executable(
    ${AERELL_STUDIO}
    ${AERELL_STUDIO_SRC_FILES}
)

target_include_directories(
    ${AERELL_STUDIO}
    PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_link_libraries(
    ${AERELL_STUDIO}
    PRIVATE
    "Qt6::Widgets"
)