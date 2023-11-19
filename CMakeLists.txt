cmake_minimum_required(VERSION 3.10)

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND CMAKE_MODULE_PATH 
${PROJECT_ROOT_DIR}/cmake/modules/
)

include(global)
GFN_TOOLCHAIN_SET()

project(DevKit VERSION 1.0.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

message(STATUS "Current project root dir '${PROJECT_ROOT_DIR}'.")

OPTION(DEVKIT_BUILD_TESTS OFF)

if(DEVKIT_BUILD_TESTS AND (EXISTS ${PROJECT_ROOT_DIR}/tests/CMakeLists.txt))
GLOBAL_BUILD_OUTDIR("bin" "bin/tests/" "objs")
add_subdirectory(${PROJECT_ROOT_DIR}/tests/)
GLOBAL_BUILD_OUTDIR("")
#message(STATUS "Enable build tests.")
endif()