file(GLOB entries *)
foreach(entry ${entries})
 if((NOT (IS_DIRECTORY ${entry})) OR (NOT (EXISTS ${entry}/CMakeLists.txt)))
  continue()
 endif()
 get_filename_component(entry_name ${entry} NAME_WE)

 if((NOT entry_name) OR (NOT (IS_DIRECTORY ${entry})) OR (NOT (EXISTS ${entry}/CMakeLists.txt)))
  continue()
 endif()

 get_filename_component(parent_dir ${entry} DIRECTORY)
 get_filename_component(parent_dir_name ${parent_dir} NAME_WE)
 string(TOLOWER ${entry_name} lower_entry_name)

 #message(STATUS "Enable runtime - ${entry_name} and ${entry}")

 add_subdirectory(${entry})
 set_target_properties(${entry_name} PROPERTIES FOLDER ${parent_dir_name})

endforeach(entry)
