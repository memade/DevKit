file(GLOB entries *)
foreach(entry ${entries})
	if(NOT(IS_DIRECTORY ${entry}) OR (NOT(EXISTS ${entry}/CMakeLists.txt)))
  continue()
 endif()

 get_filename_component(entry_project_name ${entry} NAME_WE)
 get_filename_component(parent_dir ${entry} DIRECTORY)
 get_filename_component(parent_dir_name ${parent_dir} NAME_WE)

 string(TOLOWER ${entry_project_name} lower_entry_project_name)

 if("${lower_entry_project_name}" STREQUAL "abc123")

 else()
  add_subdirectory(${entry})
  set_target_properties(${entry_project_name} PROPERTIES FOLDER ${parent_dir_name})
  #message(STATUS "${entry_name} and ${parent_dir_name}")
 endif()

endforeach()