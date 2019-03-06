if(NOT COMMAND find_host_program)
	macro(find_host_program)
		find_program(${ARGN})
	endmacro()
endif()

#------------Define function Read file------------
macro( readSettingFile KEY DEFAULT_RESULT STRING_RESULT_OUT)

	unset(STRING_RESULT)
	# Read the file
	file( READ "${CMAKE_SOURCE_DIR}/buildconfig.txt" LIB_PATH_STR )

	# Set the variable "Esc" to the ASCII value 27 - basically something
	# which is unlikely to conflict with anything in the file contents.
	string(ASCII 27 Esc)

	# Turn the contents into a list of strings, each ending with an Esc.
	# This allows us to preserve blank lines in the file since CMake
	# automatically prunes empty list items during a foreach loop.
	string(REGEX REPLACE "\n" "${Esc};" LIB_PATH_LINES "${LIB_PATH_STR}")

	foreach(LINE ${LIB_PATH_LINES})
		if("${LINE}" MATCHES "${KEY}")
			#remove the key, leave the content untouch
			string(REPLACE "${KEY}" "" STRING_RESULT ${LINE})
			# Swap the appended Esc character back out in favour of a line feed
			string(REGEX REPLACE "${Esc}" "" STRING_RESULT ${STRING_RESULT})
		endif()
	endforeach()

	if("${STRING_RESULT}" STREQUAL "")
		set( STRING_RESULT ${DEFAULT_RESULT} )
	endif()


	#message( STATIC "---GTA Sa-----" "[${STRING_RESULT}]" )
endmacro()