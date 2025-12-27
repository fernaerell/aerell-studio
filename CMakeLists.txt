cmake_minimum_required(VERSION 4.0.0)

project(
    "Aerell Studio"
    VERSION 0.0.0
    LANGUAGES C CXX
)

# CCACHE
find_program(CCACHE_PROGRAM "ccache")
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
endif()

# Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Aerell Studio
set("AERELL_STUDIO" "aerell-studio")

file(
    GLOB_RECURSE
    "AERELL_STUDIO_SRC_FILES"
    "${CMAKE_CURRENT_LIST_DIR}/src/aerell_studio/*.cpp"
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