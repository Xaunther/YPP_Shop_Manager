cmake_minimum_required(VERSION 3.22)

# Check if doxygen is installed
find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
	message(FATAL_ERROR "Doxygen not found. Install it or turn BUILD_DOCUMENTATION off.")
endif()

# Set input and output files
set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
set(CONTENT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/content)

# Use full path to refer to the code dependencies
list(TRANSFORM YPP_SM_EXTERNAL_HEADERS PREPEND ${YPP_SM_DIR}/ OUTPUT_VARIABLE FULL_PATH_YPP_SM_EXTERNAL_HEADERS)

# Add command that generates the doxygen documentation
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/html/index.html
	COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating documentation with Doxygen"
	DEPENDS ${FULL_PATH_YPP_SM_EXTERNAL_HEADERS} ${DOXYGEN_IN}
	VERBATIM)

# Add custom target
add_custom_target(doc_doxygen ALL
	DEPENDS ${YPP_SM_DIR}/doc/html/index.html
)

# Configure doxyfile
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
add_custom_target(Config_doc ALL
		COMMAND ${CMAKE_COMMAND} -D SRC=${DOXYGEN_IN}
		-D DST=${DOXYGEN_OUT}
		-D GIT_EXECUTABLE=${GIT_EXECUTABLE}
		-D PROJECT_NAME=${PROJECT_NAME}
		-D VERSION_FILE=${VERSION_FILE}
		-D YPP_SM_DIR=${YPP_SM_DIR}
		-D YPP_SM_INCLUDE_DIR=${YPP_SM_INCLUDE_DIR}
		-D DOC_PATH=${CMAKE_CURRENT_SOURCE_DIR}
		-D CONTENT_PATH=${CONTENT_PATH}
		-P ${YPP_SM_DIR}/GenerateVersionHeader.cmake
		DEPENDS PrintBuild
		)
add_dependencies(doc_doxygen Config_doc)
