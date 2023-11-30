cmake_minimum_required(VERSION 3.10)

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND CMAKE_MODULE_PATH 
${PROJECT_ROOT_DIR}/cmake/modules/
)
include(global)

GFN_ENV_INIT()
#GFN_CLANG_TOOLCHAIN_SET()

project(DevKit VERSION 1.0.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

message(STATUS "Current project root dir '${PROJECT_ROOT_DIR}'.")

option(DEVKIT_ENABLE_TESTS "Enable tests build." ON)
if(DEVKIT_ENABLE_TESTS AND (EXISTS ${PROJECT_ROOT_DIR}/tests/CMakeLists.txt))
GFN_SET_TARGET_OUTDIR(${PROJECT_ROOT_DIR} "/bin/tests/" "libs" "objs")
add_subdirectory(${PROJECT_ROOT_DIR}/tests/)
endif()

option(DEVKIT_ENABLE_RUNTIMES "Enable runtimes build." ON)
if(DEVKIT_ENABLE_RUNTIMES AND (EXISTS ${PROJECT_ROOT_DIR}/runtimes/CMakeLists.txt))
GFN_SET_TARGET_OUTDIR(${PROJECT_ROOT_DIR} "/bin/runtimes/" "libs" "libs")
add_subdirectory(${PROJECT_ROOT_DIR}/runtimes/)
endif()

GFN_ENV_UNINIT()