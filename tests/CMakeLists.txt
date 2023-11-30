function(CreateTest INPUT_PROJECT_SRC_FILE INPUT_PROJECT_NAME)
  message(STATUS "${INPUT_PROJECT_SRC_FILE} and ${INPUT_PROJECT_NAME}")
  project(${INPUT_PROJECT_NAME})
	set(SOURCES ${INPUT_PROJECT_SRC_FILE})
	add_executable(${INPUT_PROJECT_NAME} ${SOURCES})
endfunction(CreateTest INPUT_PROJECT_DIR)


file(GLOB entries *)
foreach(entry ${entries})

  get_filename_component(entry_name ${entry} NAME_WE)
  if(entry_name)
    string(TOLOWER ${entry_name} lower_entry_name)
  endif()
  get_filename_component(parent_dir ${entry} DIRECTORY)
  get_filename_component(parent_dir_name ${parent_dir} NAME_WE)
  get_filename_component(entry_ext "${entry}" EXT)
  if(entry_ext)
    string(TOLOWER ${entry_ext} lower_entry_ext)
  endif()
  if(IS_DIRECTORY ${entry})
    if(NOT (EXISTS ${entry}/CMakeLists.txt))
      continue()
    endif()

    if("${lower_entry_name}" STREQUAL "abc123")

    else()
      add_subdirectory(${entry})
      set_target_properties(${entry_name} PROPERTIES FOLDER ${parent_dir_name})
    endif()
  elseif("${lower_entry_ext}" MATCHES "^(.cc|.cpp|.c)$")
    if("${lower_entry_name}" STREQUAL "xxx")
     message(STATUS "Signal source file - '${entry_name}'.")
     continue()
    endif()

    CreateTest(${entry} ${entry_name})
    set_target_properties(${entry_name} PROPERTIES FOLDER ${parent_dir_name})

    if("${lower_entry_name}" STREQUAL "test_stl")
      target_include_directories(${entry_name} 
      PRIVATE
      ${PROJECT_ROOT_DIR}/runtimes/stl/include
      )
      target_link_directories(${entry_name}
      PRIVATE
      ${PROJECT_ROOT_DIR}/bin/runtimes/stl/${CMAKE_SYSTEM_NAME}/lib
      )
    elseif("${lower_entry_name}" STREQUAL "test_libuv")
      target_include_directories(${entry_name} 
      PRIVATE
      ${PROJECT_ROOT_DIR}/third_party/libuv/include
      )
      target_link_directories(${entry_name}
      PRIVATE
      ${PROJECT_ROOT_DIR}/bin/third_party/libuv/${CMAKE_SYSTEM_NAME}/lib
      )
    elseif("${lower_entry_name}" STREQUAL "test_clang")
      target_include_directories(${entry_name} 
      PRIVATE
      ${PROJECT_ROOT_DIR}/third_party/libuv/include
      )
      target_link_directories(${entry_name}
      PRIVATE
      ${PROJECT_ROOT_DIR}/bin/third_party/libuv/${CMAKE_SYSTEM_NAME}/lib
      )
    endif()


  endif()                                                  

endforeach()